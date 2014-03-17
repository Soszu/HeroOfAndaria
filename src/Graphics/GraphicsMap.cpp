#include "Graphics/GraphicsFactory.h"
#include "Graphics/GraphicsMap.h"

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

	//TODO scaling
	//scale(1.2, 1.2);
}

void GraphicsMap::updateCursor()
{
	cursorPosition_ = mapToScene(cursor().pos()).toPoint();
	map_->player()->setRotation(cursorPosition_);
}

void GraphicsMap::addGraphicsObject(GraphicsObject *object)
{
	tileScene_.addItem(object);
}

void GraphicsMap::keyPressEvent(QKeyEvent *event)
{
	if (!keyToMapAction_.contains(event->key()))
		return QGraphicsView::keyPressEvent(event);

	HOA::MapAction action = keyToMapAction_[event->key()];

	switch (action) {

	/** Movement */
	case HOA::MapAction::Up:
	case HOA::MapAction::Down:
		mapActions_.verticalDirection = action;
		break;
	case HOA::MapAction::Left:
	case HOA::MapAction::Right:
		mapActions_.horizontalDirection = action;
		break;

	/** Windows */
	case HOA::MapAction::Menu:
		emit menuActivated();
		//TODO pause
		break;

	default:
		Q_ASSERT(false);
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
	if (!keyToMapAction_.contains(event->key()))
		return QGraphicsView::keyReleaseEvent(event);

	HOA::MapAction action = keyToMapAction_[event->key()];

	switch (action) {

	/** Movement */
		case HOA::MapAction::Up:
		case HOA::MapAction::Down:
			mapActions_.verticalDirection = HOA::MapAction::None;
			break;
		case HOA::MapAction::Left:
		case HOA::MapAction::Right:
			mapActions_.horizontalDirection = HOA::MapAction::None;
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
	mapActions_.horizontalDirection = HOA::MapAction::None;
	mapActions_.verticalDirection   = HOA::MapAction::None;
}

void GraphicsMap::initMap()
{
	connect(map_, &Map::objectAdded, this, &GraphicsMap::onObjectAdded);
}

HOA::Direction GraphicsMap::mapActionDirection() const
{
	int vertical   = ((int)mapActions_.verticalDirection + 1) / 2;
	int horizontal = (int)mapActions_.horizontalDirection / 2;

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

//TODO modifiable by options in menu
QHash <int, HOA::MapAction> GraphicsMap::keyToMapAction_ {
	{Qt::Key_W,      HOA::MapAction::Up},
	{Qt::Key_S,      HOA::MapAction::Down},
	{Qt::Key_A,      HOA::MapAction::Left},
	{Qt::Key_D,      HOA::MapAction::Right},
	{Qt::Key_Escape, HOA::MapAction::Menu},
};

/**
 * \class TileScene
 */

TileScene::TileScene(Map *map)
	: map_(map)
{
	QGraphicsScene::setSceneRect({0., 0., (qreal)map_->width(), (qreal)map_->height()});
}

TileScene::~TileScene()
{
	qDeleteAll(tiles_);
}

void TileScene::initBackground()
{
	tiles_.clear();
	for (const Tile &tile : map_->tiles())
		addTile(newTile(tile));
}

//TODO prepare some samples for tiles + generating tiles (?)

const QPixmap * TileScene::newTile(const Tile &tile) const
{
	//TODO
	//static const QPixmap samplePixmap("../../data/tiles/grass.png");
	//return &samplePixmap;
	return new const QPixmap(Data::Image::TileGrass);
}

/** From Qt documentation */

QRectF TileScene::rectForTile(int x, int y) const
{
	// Return the rectangle for the tile at position (x, y).
	return QRectF(x * BIG_TILE_SIZE, y * BIG_TILE_SIZE, BIG_TILE_SIZE, BIG_TILE_SIZE);
}

void TileScene::addTile(const QPixmap *pixmap)
{
	tiles_.append(pixmap);
	if (bigTiles_.last().second == BIG_TILE_MULTIPLIER)
		bigTiles_.append({
			QPixmap(BIG_TILE_SIZE,
		                BIG_TILE_SIZE),
			0});

	int currentNumber = bigTiles_.last().second;

	QPainter painter(&bigTiles_.last().first);
	painter.drawPixmap(QPoint(currentNumber % BIG_TILE_MULTIPLIER * TILE_SIZE,
	                          currentNumber / BIG_TILE_MULTIPLIER * TILE_SIZE),
	                   *pixmap);

	bigTiles_.last().second++;
}

void TileScene::setTile(int x, int y, const QPixmap *pixmap)
{
	// Sets or replaces the tile at position (x, y) with pixmap.
	if (x >= 0 && x < map_->width() && y >= 0 && y < map_->height()) {
		tiles_[x + y * map_->width()] = pixmap;
		invalidate(rectForTile(x, y), QGraphicsScene::BackgroundLayer);
	}
}

void TileScene::drawBackground(QPainter *painter, const QRectF &exposed)
{
	int height = map_->height() / BIG_TILE_MULTIPLIER;
	int width  = map_->width() / BIG_TILE_MULTIPLIER;

	static const QPixmap samplePixmap(Data::Image::TileGrass);
	QPixmap bigSamplePixmap(BIG_TILE_SIZE, BIG_TILE_SIZE);
	QPainter bigTilePainter(&bigSamplePixmap);
	for (int y = 0; y < BIG_TILE_MULTIPLIER; ++y)
		for (int x = 0; x < BIG_TILE_MULTIPLIER; ++x)
			bigTilePainter.drawPixmap(QPoint(x * TILE_SIZE, y * TILE_SIZE), samplePixmap);

	// Draws all tiles that intersect the exposed area.
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			//TODO optimize this further. And find that damn segfault. And this funny effect.
			QRectF rect = rectForTile(x, y);
			if (exposed.intersects(rect))
				painter->drawPixmap(rect.topLeft(), bigSamplePixmap);//bigTiles_[x + width * y].first);
		}
	}
}
