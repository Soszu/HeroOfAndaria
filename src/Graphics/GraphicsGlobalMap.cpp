#include "Graphics/GraphicsFactory.h"
#include "Graphics/GraphicsGlobalMap.h"
#include "Graphics/GraphicsLocalMap.h"
#include "Graphics/GraphicsTown.h"

GraphicsGlobalMap::GraphicsGlobalMap(GlobalMap *map)
	: GraphicsMap(map)
{
	initMap();
	initLayout();
}

void GraphicsGlobalMap::initMap()
{
	connect((GlobalMap *)map_, &GlobalMap::townEntered, this, &GraphicsGlobalMap::onTownEntered);
	connect((GlobalMap *)map_, &GlobalMap::townExited,  this, &GraphicsGlobalMap::onTownExited);

	connect((GlobalMap *)map_, &GlobalMap::locationEntered, this, &GraphicsGlobalMap::onLocationEntered);
	connect((GlobalMap *)map_, &GlobalMap::locationExited,  this, &GraphicsGlobalMap::onLocationExited);
}

void GraphicsGlobalMap::initLayout()
{
	/** Map layout */

	mapWidget_ = new QWidget();

	QHBoxLayout *mapLayout = new QHBoxLayout;
	mapLayout->addWidget(mapView_);
	mapWidget_->setLayout(mapLayout);

	QStackedWidget::insertWidget(MAP_INDEX, mapWidget_);

	/** Town layout */

	townWidget_ = new QWidget(this);
	QHBoxLayout *townLayout = new QHBoxLayout;
	townWidget_->setLayout(townLayout);

	QStackedWidget::insertWidget(TOWN_INDEX, townWidget_);

	/** Location layout */

	locationWidget_ = new QWidget();
	QHBoxLayout *locationLayout = new QHBoxLayout;
	locationWidget_->setLayout(locationLayout);

	QStackedWidget::insertWidget(LOCATION_INDEX, locationWidget_);


	setCurrentIndex(MAP_INDEX);
}

void GraphicsGlobalMap::keyPressEvent(QKeyEvent *event)
{
	//TODO with special keyboard settings
	if (event->key() == KeyboardManager::primaryKey(HOA::KeyFunction::EnterLocation)) {
		tryEnterTown();
		tryEnterLocation();
		event->accept();
	} else {
		GraphicsMap::keyPressEvent(event);
	}
}

void GraphicsGlobalMap::tryEnterTown()
{
	auto towns = ((GlobalMap *)map_)->towns();
	for (Town *town : towns)
		if (GraphicsFactory::get(town)->collidesWithItem(GraphicsFactory::get(map_->player())))
			return ((GlobalMap *)map_)->enterTown(town);
}

void GraphicsGlobalMap::tryEnterLocation()
{
	auto locations = ((GlobalMap *)map_)->locations();
	for (Location *location : locations)
		if (GraphicsFactory::get(location)->collidesWithItem(GraphicsFactory::get(map_->player())))
			return ((GlobalMap *)map_)->enterLocation(location);
}

void GraphicsGlobalMap::onTownEntered()
{
	const Town *currentTown = ((GlobalMap *)map_)->currentTown();
	GraphicsTown *graphicsTown =
		static_cast<GraphicsTownObject *>(GraphicsFactory::get(currentTown))->graphicsTown();
	townWidget_->layout()->addWidget(graphicsTown);
	QStackedWidget::setCurrentIndex(TOWN_INDEX);
}

void GraphicsGlobalMap::onTownExited()
{
	QStackedWidget::setCurrentIndex(MAP_INDEX);
	townWidget_->layout()->removeItem(townWidget_->layout()->itemAt(0));
}

void GraphicsGlobalMap::onLocationEntered()
{
	const Location *currentLocation = ((GlobalMap *)map_)->currentLocation();
	locationPosition_ = currentLocation->position();
	GraphicsLocalMap *graphicsLocalMap =
		static_cast<GraphicsLocalMap *>(GraphicsFactory::get(currentLocation->localMap()));
	locationWidget_->layout()->addWidget(graphicsLocalMap);
	QStackedWidget::setCurrentIndex(LOCATION_INDEX);
}

void GraphicsGlobalMap::onLocationExited()
{
	QStackedWidget::setCurrentIndex(MAP_INDEX);
	locationWidget_->layout()->removeItem(locationWidget_->layout()->itemAt(0));
	map_->player()->setPosition(locationPosition_);
	mapView_->reinit();
}
