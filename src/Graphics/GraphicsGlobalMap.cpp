#include "Graphics/GraphicsFactory.h"
#include "Graphics/GraphicsGlobalMap.h"
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
}

void GraphicsGlobalMap::initLayout()
{
	/** Map layout */

	mapWidget_ = new QWidget();

	QHBoxLayout *mapLayout = new QHBoxLayout;
	mapLayout->addWidget(mapView_);
	//TODO mapLayout->addWidget(sideBar_);
	mapWidget_->setLayout(mapLayout);

	QStackedWidget::insertWidget(MAP_INDEX, mapWidget_);

	/** Town layout */

	townWidget_ = new QWidget(this);
	QHBoxLayout *townLayout = new QHBoxLayout;
	townWidget_->setLayout(townLayout);

	QStackedWidget::insertWidget(TOWN_INDEX, townWidget_);

	setCurrentIndex(MAP_INDEX);
}

void GraphicsGlobalMap::keyPressEvent(QKeyEvent *event)
{
	//TODO with special keyboard settings
	if (event->key() == KeyboardManager::primaryKey(HOA::KeyFunction::EnterLocation))
		tryEnterTown();
	GraphicsMap::keyPressEvent(event);
}

void GraphicsGlobalMap::tryEnterTown()
{
	auto towns = ((GlobalMap *)map_)->towns();
	for (Town *town : towns)
		if (GraphicsFactory::get(town)->collidesWithItem(GraphicsFactory::get(map_->player())))
			return ((GlobalMap *)map_)->enterTown(town);
}

void GraphicsGlobalMap::onTownEntered()
{
	const Town *currentTown = ((GlobalMap *)map_)->currentTown();
	GraphicsTown *graphicsTown = static_cast<GraphicsTownObject *>(GraphicsFactory::get(currentTown))->graphicsTown();
	townWidget_->layout()->addWidget(graphicsTown);
	QStackedWidget::setCurrentIndex(TOWN_INDEX);
}

void GraphicsGlobalMap::onTownExited()
{
	QStackedWidget::setCurrentIndex(MAP_INDEX);
	townWidget_->layout()->removeItem(townWidget_->layout()->itemAt(0));
}