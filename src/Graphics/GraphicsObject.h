#ifndef GRAPHICSOBJECT_H
#define GRAPHICSOBJECT_H

#include <QtWidgets>
#include "System/Object.h"

class GraphicsObject : public QGraphicsObject
{
public:
	GraphicsObject(Object *object);

private:
	Object *object_;

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // GRAPHICSOBJECT_H
