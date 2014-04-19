#include "Graphics/GraphicsLocalMap.h"
#include "System/DataManager.h"

/**
 * \class GraphicsLocalMap
 */

GraphicsLocalMap::GraphicsLocalMap(LocalMap *map) :
	GraphicsMap(map)
{
	initMap();
	initLayout();
}

void GraphicsLocalMap::initMap()
{
	//All necessary connects will be here
}

void GraphicsLocalMap::initLayout()
{
	addWidget(mapView_);
	setCurrentIndex(0);
}

void GraphicsLocalMap::keyPressEvent(QKeyEvent *event)
{
	//Don't put it into KeyboardManager
	if (event->key() == Qt::Key_Space) {
		((LocalMap *)map_)->exitLocation();
		event->accept();
	} else {
		GraphicsMap::keyPressEvent(event);
	}
}

/**
 * \class GraphicsLocation
 */

GraphicsLocation::GraphicsLocation(Location *location) :
	GraphicsObject(location)
{
	pixmap_ = DataManager::pixmap(Data::ImagePath::LocationKennel);
}

QRectF GraphicsLocation::boundingRect() const
{
	qreal width  = (qreal)pixmap_->width();
	qreal height = (qreal)pixmap_->height();
	return {-width / 2, -height / 2, width, height};
}

void GraphicsLocation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->save();

	painter->setPen(Qt::white);

	painter->drawText(boundingRect(), Qt::AlignTop, ((Location *)object_)->name());

	painter->setPen(Qt::black);

	painter->drawPixmap(boundingRect().toRect(), *pixmap_);

	painter->restore();
}

