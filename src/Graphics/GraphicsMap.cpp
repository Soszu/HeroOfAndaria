#include "Graphics/GraphicsFactory.h"
#include "Graphics/GraphicsMap.h"
#include "System/Paths.h"

/**
 * \class GraphicsMap
 */

GraphicsMap::GraphicsMap(Map *map)
	: map_(map)
{
	initMap();
	initMapActions();
	initView();
	initLayout();
}

GraphicsMap::~GraphicsMap()
{
	delete mapView_;
}

bool GraphicsMap::canMakeMove(const Movable *object, const QPoint &vector) const
{
	GraphicsObject *graphicsObject = GraphicsFactory::get(object);
	auto collisions = graphicsObject->collisions(vector);

	for (GraphicsObject *x : collisions)
		if (!map_->canCollide(object, x->object()))
			return false;
	return true;
}

void GraphicsMap::keyPressEvent(QKeyEvent *event)
{
	if (event->isAutoRepeat())
		return;
	if (!KeyboardManager::hasKeyFunction(event->key()))
		return QWidget::keyPressEvent(event);

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
			return QWidget::keyPressEvent(event);
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
	if (event->isAutoRepeat())
		return;
	if (!KeyboardManager::hasKeyFunction(event->key()))
		return QWidget::keyReleaseEvent(event);

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

void GraphicsMap::initMap()
{
	for (Object *obj : map_->objects())
		if (obj->isMovable())
			((Movable *)obj)->setMovementManager(this);

	connect(map_, &Map::objectAdded, this, &GraphicsMap::onObjectAdded);
}

void GraphicsMap::initMapActions()
{
	mapActions_.horizontalDirection = HOA::KeyFunction::None;
	mapActions_.verticalDirection   = HOA::KeyFunction::None;
}

void GraphicsMap::initView()
{
	mapView_ = new MapView(map_);
	connect(mapView_, &MapView::collided, this, &GraphicsMap::onCollision);
}

void GraphicsMap::initLayout()
{}

static int mapActionToValue(HOA::KeyFunction mapAction)
{
	switch (mapAction) {
		case HOA::KeyFunction::None:
			return 1;
		case HOA::KeyFunction::MoveForward:
		case HOA::KeyFunction::MoveLeft:
			return 0;
		case HOA::KeyFunction::MoveBackwards:
		case HOA::KeyFunction::MoveRight:
			return 2;
		default:
			return -1;
	}
}

HOA::Direction GraphicsMap::mapActionDirection() const
{
	int vertical   = mapActionToValue(mapActions_.verticalDirection);
	int horizontal = mapActionToValue(mapActions_.horizontalDirection);

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

void GraphicsMap::onObjectAdded()
{
	Object *object = map_->newestObject();

	if (object->isMovable())
		((Movable *)object)->setMovementManager(this);
}

/**
 * \class MapView
 */

MapView::MapView(Map *map)
	: QGraphicsView(), map_(map), tileScene_(new TileScene(map))
{
	initMap();
	initWindow();
	initGraphicsObjects();
	initScene();
	initCursor();
	initView();
	initPanels();
}

MapView::~MapView()
{}

void MapView::initMap()
{
	connect(map_, &Map::objectAdded, this, &MapView::onObjectAdded);
}

void MapView::initWindow()
{
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFrameStyle(QFrame::NoFrame);
}

void MapView::initScene()
{
	setScene(tileScene_);
	QGraphicsView::centerOn(mapFromScene(map_->player()->position()));
}

void MapView::initGraphicsObjects()
{
	tileScene_->clear();
	for (Object *object : map_->objects())
		addGraphicsObject(GraphicsFactory::get(object));
	map_->player();
}

void MapView::initCursor()
{
	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &MapView::updateCursor);
	timer->start();
}

void MapView::initView()
{
	//TODO scaling && resolution (from menu/settings -> mainwindow)
	scale(1.2, 1.2);
}

void MapView::initPanels()
{
	BottomPanel *bottomPanel = new BottomPanel(this);
	SidePanel *sidePanel = new SidePanel(this);

	// connecting panels
	connect(bottomPanel, &BottomPanel::inventoryPressed, sidePanel, &SidePanel::onInventoryClicked);
	connect(bottomPanel, &BottomPanel::skillsPressed, sidePanel, &SidePanel::onSkillsClicked);
	connect(bottomPanel, &BottomPanel::questsPressed, sidePanel, &SidePanel::onQuestsClicked);
}

void MapView::addGraphicsObject(GraphicsObject *graphicsObject)
{
	connect(graphicsObject, &GraphicsObject::collided, this, &MapView::collided);

	int zValue;
	switch (graphicsObject->object()->objectType()) {
		case HOA::ObjectType::Human:
		case HOA::ObjectType::Creature:
			zValue = 2;
			break;
		case HOA::ObjectType::Item:
			zValue = 3;
			break;
		case HOA::ObjectType::Town:
			zValue = 1;
			break;
		default:;
	}

	graphicsObject->setZValue(zValue);

	tileScene_->addItem(graphicsObject);
}

void MapView::updateCursor()
{
	QPointF cursorPosition_ = mapToScene(cursor().pos());
	map_->player()->setRotation(cursorPosition_.toPoint());
}

void MapView::onObjectAdded()
{
	addGraphicsObject(GraphicsFactory::get(map_->newestObject()));
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
QPixmap TileScene::newTile(const Tile &tile) const
{
	//TODO data manager
	static QPixmap fullPixmap(Data::Images::TileGrass);

	//TODO throw some global rand please
	static bool initialized = false;
	if (!initialized) {
		initialized = true;
		qsrand(0);
	}

	return fullPixmap.copy(
		qrand() % (fullPixmap.width() / map_->tileSize()) * map_->tileSize(),
		qrand() % (fullPixmap.height() / map_->tileSize()) * map_->tileSize(),
		map_->tileSize(),
		map_->tileSize()
	);
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
	                   newTile(tile));

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
