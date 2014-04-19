#ifndef GRAPHICSLOCALMAP_H
#define GRAPHICSLOCALMAP_H

#include "Graphics/GraphicsMap.h"
#include "System/LocalMap.h"

/**
 * \class GraphicsLocalMap
 */
class GraphicsLocalMap : public GraphicsMap
{
public:
	GraphicsLocalMap(LocalMap *map);

private:
	void initMap();
	void initLayout();

	void keyPressEvent(QKeyEvent *event);
};

/**
 * \class GraphicsLocation
 * Graphical representation of Location on the GlobalMap.
 */
class GraphicsLocation : public GraphicsObject
{
public:
	GraphicsLocation(Location *location);

private:
	QPixmap *pixmap_;

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // GRAPHICSLOCALMAP_H
