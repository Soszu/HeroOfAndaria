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
	initView();
	initLayout();
}

GraphicsMap::~GraphicsMap()
{
	delete mapView_;
}

bool GraphicsMap::canMakeMove(const Movable *object, const QPoint &vector) const
{
	static const int BORDER_SIZE = 20;

	QPoint finalPosition = object->position() + vector;
	if (finalPosition.x() < BORDER_SIZE || finalPosition.y() < BORDER_SIZE
	    || finalPosition.x() > map_->width() * Grid::tileSize() - BORDER_SIZE
	    || finalPosition.y() > map_->height() * Grid::tileSize() - BORDER_SIZE)
		return false;

	GraphicsObject *graphicsObject = GraphicsFactory::get(object);
	auto collisions = graphicsObject->collisions(vector);

	for (GraphicsObject *x : collisions)
		if (!map_->canCollide(object, x->object()))
			return false;
	return true;
}

static int keyFunctionToDirectionValue(HOA::KeyFunction mapAction)
{
	switch (mapAction) {
		case HOA::KeyFunction::None:
			return 1;
		case HOA::KeyFunction::MoveForward:
		case HOA::KeyFunction::MoveLeft:
		case HOA::KeyFunction::CameraUp:
		case HOA::KeyFunction::CameraLeft:
			return 0;
		case HOA::KeyFunction::MoveBackwards:
		case HOA::KeyFunction::MoveRight:
		case HOA::KeyFunction::CameraDown:
		case HOA::KeyFunction::CameraRight:
			return 2;
		default:
			return 1;
	}
}

HOA::Direction GraphicsMap::keysToDirection(HOA::KeyFunction horizontalDirection,
                                            HOA::KeyFunction verticalDirection)
{
	int vertical   = keyFunctionToDirectionValue(verticalDirection);
	int horizontal = keyFunctionToDirectionValue(horizontalDirection);

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

void GraphicsMap::keyPressEvent(QKeyEvent *event)
{
	if (event->isAutoRepeat())
		return;
	if (!KeyboardManager::hasKeyFunction(event->key()))
		return QWidget::keyPressEvent(event);

	HOA::KeyFunction action = KeyboardManager::keyFunction(event->key());

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

	/** Camera */
		case HOA::KeyFunction::CameraUp:
		case HOA::KeyFunction::CameraDown:
			mapView_->setCameraVerticalAction(action);
			break;

		case HOA::KeyFunction::CameraLeft:
		case HOA::KeyFunction::CameraRight:
			mapView_->setCameraHorizontalAction(action);
			break;

	/** Windows */
		case HOA::KeyFunction::Menu:
			emit menuActivated();
			//TODO pause (global timer?), stop any scrolling, scaling
			break;

		default:;
	}

	//TODO player control could be implemented using some sort of AI-like control panel.
	// This would eliminate inconsistency between player character and CPU.
	map_->player()->move(keysToDirection(mapActions_.horizontalDirection, mapActions_.verticalDirection));
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

	/** Camera */
		case HOA::KeyFunction::CameraUp:
		case HOA::KeyFunction::CameraDown:
			mapView_->setCameraVerticalAction(HOA::KeyFunction::None);
			break;

		case HOA::KeyFunction::CameraLeft:
		case HOA::KeyFunction::CameraRight:
			mapView_->setCameraHorizontalAction(HOA::KeyFunction::None);
			break;

		default:;
	}

	map_->player()->move(keysToDirection(mapActions_.horizontalDirection, mapActions_.verticalDirection));
}

void GraphicsMap::wheelEvent(QWheelEvent *event)
{
	mapView_->zoom(event->delta());
}

void GraphicsMap::initMap()
{
	for (Object *obj : map_->objects())
		if (obj->isMovable())
			((Movable *)obj)->setMovementManager(this);

	connect(map_, &Map::objectAdded, this, &GraphicsMap::onObjectAdded);
}

void GraphicsMap::initView()
{
	mapActions_.horizontalDirection = HOA::KeyFunction::None;
	mapActions_.verticalDirection   = HOA::KeyFunction::None;

	mapView_ = new MapView(map_);
	connect(mapView_, &MapView::collided, this, &GraphicsMap::onCollision);
}

void GraphicsMap::initLayout()
{}

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

void MapView::setCameraHorizontalAction(HOA::KeyFunction action)
{
	cameraActions_.horizontalDirection = action;
	checkScrolling();
}

void MapView::setCameraVerticalAction(HOA::KeyFunction action)
{
	cameraActions_.verticalDirection = action;
	checkScrolling();
}

int MapView::scrollSpeed()
{
	//TODO options in menu
	static const int SCROLL_SPEED = 70;
	return SCROLL_SPEED;
}

void MapView::zoom(int delta)
{
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

	static constexpr qreal SCALE_FACTOR = 1.15;
	if (delta > 0)
		scale(SCALE_FACTOR, SCALE_FACTOR);
	else
		scale(1.0 / SCALE_FACTOR, 1.0 / SCALE_FACTOR);
}

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
// 	scale(1.2, 1.2);
	scale(2, 2);

	cameraActions_.verticalDirection   = HOA::KeyFunction::None;
	cameraActions_.horizontalDirection = HOA::KeyFunction::None;

	connect(map_->player(), &Object::positionSet, this, &MapView::onPlayerMoved);
	connect(&scrollTimer_, &QTimer::timeout, this, &MapView::onScroll);
}

void MapView::initPanels()
{
	BottomPanel *bottomPanel = new BottomPanel(map_->player(), this);
	SidePanel *sidePanel = new SidePanel(this);

	// connecting panels
	connect(bottomPanel, &BottomPanel::inventoryPressed, sidePanel, &SidePanel::onInventoryClicked);
	connect(bottomPanel, &BottomPanel::skillsPressed,    sidePanel, &SidePanel::onSkillsClicked);
	connect(bottomPanel, &BottomPanel::questsPressed,    sidePanel, &SidePanel::onQuestsClicked);
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

void MapView::checkScrolling()
{
	scrollDirection_ = GraphicsMap::keysToDirection(cameraActions_.horizontalDirection,
	                                                cameraActions_.verticalDirection);
	if (scrollDirection_ == HOA::Direction::None)
		scrollTimer_.stop();
	else
		scrollTimer_.start(50);
}

void MapView::scroll(const QPoint &change)
{
	horizontalScrollBar()->setValue(change.x());
	verticalScrollBar()->setValue(change.y());
}

QPoint MapView::scrollPosition() const
{
	return {horizontalScrollBar()->value(), verticalScrollBar()->value()};
}

void MapView::keyPressEvent(QKeyEvent *event)
{
	event->ignore();
}

void MapView::keyReleaseEvent(QKeyEvent *event)
{
	event->ignore();
}

void MapView::wheelEvent(QWheelEvent *event)
{
	event->ignore();
}

void MapView::updateCursor()
{
	QPointF cursorPosition_ = mapToScene(cursor().pos());
	map_->player()->setRotation(cursorPosition_.toPoint());
}

void MapView::onScroll()
{
	static const int SCROLL_SLANT_SPEED = int(scrollSpeed() / sqrt(2));
	int x = scrollPosition().x();
	int y = scrollPosition().y();

	switch (scrollDirection_) {
		case HOA::Direction::Front:      scroll({x, y - scrollSpeed()}); break;
		case HOA::Direction::LeftFront:  scroll({x - SCROLL_SLANT_SPEED, y - SCROLL_SLANT_SPEED}); break;
		case HOA::Direction::Left:       scroll({x - scrollSpeed(), y}); break;
		case HOA::Direction::LeftRear:   scroll({x - SCROLL_SLANT_SPEED, y + SCROLL_SLANT_SPEED}); break;
		case HOA::Direction::Rear:       scroll({x, y + scrollSpeed()}); break;
		case HOA::Direction::RightRear:  scroll({x + SCROLL_SLANT_SPEED, y + SCROLL_SLANT_SPEED}); break;
		case HOA::Direction::Right:      scroll({x + scrollSpeed(), y}); break;
		case HOA::Direction::RightFront: scroll({x + SCROLL_SLANT_SPEED, y - SCROLL_SLANT_SPEED}); break;
		default:;
	}
}

void MapView::onObjectAdded()
{
	addGraphicsObject(GraphicsFactory::get(map_->newestObject()));
}

void MapView::onPlayerMoved()
{
	GraphicsObject *graphicsPlayer = GraphicsFactory::get(map_->player());
	centerOn(graphicsPlayer);
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
