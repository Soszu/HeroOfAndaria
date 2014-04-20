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

Object * GraphicsObject::object()
{
	return object_;
}

QPainterPath GraphicsObject::shape() const
{
	QPainterPath path;
	path.addRect(boundingRect());
	return path;
}

QVector <GraphicsObject *> GraphicsObject::collisions(const QPoint &vector)
{
	QVector <GraphicsObject *> collisions;

	QList <QGraphicsItem *> cs = scene()->items(mapToScene(shape().translated(vector)), Qt::IntersectsItemShape);
	for (QGraphicsItem *item : cs)
		if (item != static_cast<QGraphicsItem *>(this))
			collisions.append(static_cast<GraphicsObject *>(item));
	return collisions;
}

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
	checkCollisions();
	QGraphicsItem::advance(1);
}

void GraphicsObject::checkCollisions()
{
	if (!collisions().isEmpty())
		emit collided();
}

void GraphicsObject::adjustPosition()
{
	QGraphicsObject::setPos(object_->position());
}

void GraphicsObject::adjustRotation()
{
	QGraphicsObject::setRotation(vectorAngle(object_->position(), object_->rotation()));
}