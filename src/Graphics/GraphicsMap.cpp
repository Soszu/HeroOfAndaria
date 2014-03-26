#include "Graphics/GraphicsFactory.h"
#include "Graphics/GraphicsMap.h"
#include "System/Paths.h"

/**
 * \class GraphicsMap
 */

GraphicsMap::GraphicsMap(Map *map)
	: map_(map), tileScene_(map)
{
	initWindow();
	initGraphicsObjects();
	initScene();
	initMapActions();
	initMap();

	//TODO scaling && resolution (from menu/settings -> mainwindow)
	scale(1.2, 1.2);
}

void GraphicsMap::updateCursor()
{
	cursorPosition_ = mapToScene(cursor().pos()).toPoint();
	map_->player()->setRotation(cursorPosition_);
}

bool GraphicsMap::canMakeMove(const Movable *object, const QPoint &vector) const
{
	GraphicsObject *graphicsObject = GraphicsFactory::get(object);
	return graphicsObject->collisions(vector).isEmpty();
}

void GraphicsMap::addGraphicsObject(GraphicsObject *graphicsObject)
{
	connect(graphicsObject, &GraphicsObject::collided, this, &GraphicsMap::onCollision);

	Object *object = graphicsObject->object();

	if (object->isMovable())
		((Movable *)object)->setMovementManager(this);
	tileScene_.addItem(graphicsObject);
}

void GraphicsMap::keyPressEvent(QKeyEvent *event)
{
	if (!KeyboardManager::hasKeyFunction(event->key()))
		return QGraphicsView::keyPressEvent(event);

	HOA::KeyFunction action = KeyboardManager::keyFunction(event->key());

	//TODO modifiers

	switch (action) {

	/** Movement */
		case HOA::KeyFunction::MoveForward:
		case HOA::KeyFunction::MoveBackwards:
			mapActions_.verticalDirection = action;
			break;
		case HOA::KeyFunction::MoveLeft:
		case HOA::KeyFunction::MoveRight:
			mapActions_.horizontalDirection = action;
			break;

	/** Windows */
		case HOA::KeyFunction::Menu:
			emit menuActivated();
			//TODO pause (global timer?)
			break;

		default:
			return QGraphicsView::keyPressEvent(event);
	}

	//TODO player control could be implemented using some sort of AI-like control panel.
	// This would eliminate inconsistency between player character and CPU.
	map_->player()->move(mapActionDirection());

	//TODO centerOn player.
	//QGraphicsView::centerOn(mapFromScene(map_->player()->position()));
	/*QGraphicsView::setSceneRect(map_->player()->position().x() - QGraphicsView::width() / 2,
	                            map_->player()->position().y() - QGraphicsView::width() / 2,
	                            QGraphicsView::width(),
	                            QGraphicsView::height());*/
}

void GraphicsMap::keyReleaseEvent(QKeyEvent *event)
{
	if (!KeyboardManager::hasKeyFunction(event->key()))
		return QGraphicsView::keyReleaseEvent(event);

	HOA::KeyFunction action = KeyboardManager::keyFunction(event->key());

	switch (action) {

	/** Movement */
		case HOA::KeyFunction::MoveForward:
		case HOA::KeyFunction::MoveBackwards:
			mapActions_.verticalDirection = HOA::KeyFunction::None;
			break;
		case HOA::KeyFunction::MoveLeft:
		case HOA::KeyFunction::MoveRight:
			mapActions_.horizontalDirection = HOA::KeyFunction::None;
			break;

		default:
			Q_ASSERT(false);
	}

	map_->player()->move(mapActionDirection());
}

void GraphicsMap::onObjectAdded()
{
	addGraphicsObject(GraphicsFactory::get(map_->newestObject()));
}

void GraphicsMap::initWindow()
{
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFrameStyle(QFrame::NoFrame);
}

void GraphicsMap::initScene()
{
	setScene(&tileScene_);
	QGraphicsView::centerOn(mapFromScene(map_->player()->position()));
}

void GraphicsMap::initGraphicsObjects()
{
	tileScene_.clear();
	for (Object *object : map_->objects())
		addGraphicsObject(GraphicsFactory::get(object));
	map_->player();
}

void GraphicsMap::initMapActions()
{
	mapActions_.horizontalDirection = HOA::KeyFunction::None;
	mapActions_.verticalDirection   = HOA::KeyFunction::None;
}

void GraphicsMap::initMap()
{
	connect(map_, &Map::objectAdded, this, &GraphicsMap::onObjectAdded);
}

HOA::Direction GraphicsMap::mapActionDirection() const
{
	int vertical   = (int)(mapActions_.verticalDirection == HOA::KeyFunction::None)
	                 + (int)(mapActions_.verticalDirection == HOA::KeyFunction::MoveRight) * 2;
	int horizontal = (int)(mapActions_.horizontalDirection == HOA::KeyFunction::None)
	                 + (int)(mapActions_.horizontalDirection == HOA::KeyFunction::MoveBackwards) * 2;

	switch (vertical + 3 * horizontal) {
		case 0:  return HOA::Direction::LeftFront;
		case 1:  return HOA::Direction::Left;
		case 2:  return HOA::Direction::LeftRear;
		case 3:  return HOA::Direction::Front;
		case 4:  return HOA::Direction::None;
		case 5:  return HOA::Direction::Rear;
		case 6:  return HOA::Direction::RightFront;
		case 7:  return HOA::Direction::Right;
		case 8:  return HOA::Direction::RightRear;
		default: Q_ASSERT(false);
	}
	return HOA::Direction::None;
}

void GraphicsMap::onCollision()
{
	//TODO Will be useful. Yes. Trigger the relevant function in Map and here you go.
	//GraphicsObject *object = static_cast<GraphicsObject *>(sender());
	//QVector <GraphicsObject *> collisions = objectA->collisions();
}

/**
 * \class TileScene
 */

TileScene::TileScene(Map *map)
	: map_(map)
{
	QGraphicsScene::setSceneRect({
		0.,
		0.,
		(qreal)map_->width()  * Grid::tileSize(),
		(qreal)map_->height() * Grid::tileSize()
	});

	initBackground();
}

TileScene::~TileScene()
{}

int TileScene::bigTileMultiplier()
{
	static const int BIG_TILE_MULTIPLIER = 2;
	return BIG_TILE_MULTIPLIER;
}

int TileScene::bigTileSize()
{
	return bigTileMultiplier() * Grid::tileSize();
}

void TileScene::initBackground()
{
	bigTiles_.clear();
	for (const Tile &tile : map_->tiles())
		addTile(tile);
}

//TODO prepare some samples for tiles + generating tiles (?)
//TODO Change the function signature. New big tile for specific tile set, or something. // DataManager
const QPixmap * TileScene::newTile(const Tile &tile) const
{
	//TODO
	static const QPixmap samplePixmap(Data::Images::TileGrass);
	return &samplePixmap;
}

/** From Qt documentation */

QRectF TileScene::rectForTile(int x, int y) const
{
	// Return the rectangle for the tile at position (x, y).
	return QRectF(x * bigTileSize(),
	              y * bigTileSize(),
	              bigTileSize(),
	              bigTileSize());
}

void TileScene::addTile(const Tile &tile)
{
	static const QPixmap pixmap(Data::Images::TileGrass);

	if (bigTiles_.isEmpty() || bigTiles_.last().second == bigTileMultiplier() * bigTileMultiplier()) {
		bigTiles_.append({
			QPixmap(bigTileSize(),
		                bigTileSize()),
			0});
		bigTiles_.last().first.fill(Qt::black);
	}

	int currentNumber = bigTiles_.last().second;

	QPainter painter(&bigTiles_.last().first);
	painter.drawPixmap(QPoint(currentNumber % bigTileMultiplier() * Grid::tileSize(),
	                          currentNumber / bigTileMultiplier() * Grid::tileSize()),
	                   pixmap);

	bigTiles_.last().second++;

	if (bigTiles_.last().second == bigTileMultiplier() * bigTileMultiplier()) {
		int lastIndex = bigTiles_.size() - 1;
		invalidate(rectForTile(lastIndex % map_->width(), lastIndex / map_->width()),
		           QGraphicsScene::BackgroundLayer);
	}
}

void TileScene::drawBackground(QPainter *painter, const QRectF &exposed)
{
	int height = map_->height() / bigTileMultiplier();
	int width  = map_->width()  / bigTileMultiplier();

	/** Draws all tiles that intersect the exposed area. */
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			//TODO optimize this further.
			QRectF rect = rectForTile(x, y);
			if (exposed.intersects(rect))
				painter->drawPixmap(rect.topLeft(), bigTiles_[x + width * y].first);
		}
	}
}
