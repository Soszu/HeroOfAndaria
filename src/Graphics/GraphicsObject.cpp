#include "Graphics/GraphicsObject.h"

GraphicsObject::GraphicsObject(Object *object)
	: object_(object)
{
	connect(object_, &Object::positionSet, this, &GraphicsObject::adjustPosition);
	connect(object_, &Object::rotationSet, this, &GraphicsObject::adjustRotation);
	connect(object_, &Object::advanced,    this, &GraphicsObject::advance);

	adjustPosition();
	adjustRotation();
}

GraphicsObject::~GraphicsObject()
{}

qreal GraphicsObject::vectorAngle(const QPoint &middle, const QPoint &vector)
{
	if (vector == middle)
		return 0;
	QPoint effVector(vector - middle);
	qreal radians = qAtan2(-effVector.x(), effVector.y());
	return (int)qRadiansToDegrees(radians);
}

QRectF GraphicsObject::boundingRect() const
{
	return QRectF();
}

void GraphicsObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{}

void GraphicsObject::advance()
{
	adjustPosition();
	adjustRotation();
}

void GraphicsObject::adjustPosition()
{
	QGraphicsObject::setPos(object_->position());
}

void GraphicsObject::adjustRotation()
{
	QGraphicsObject::setRotation(vectorAngle(object_->position(), object_->rotation()));
}