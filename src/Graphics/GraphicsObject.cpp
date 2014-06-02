#include "Graphics/GraphicsObject.h"
#include "System/Utils/Math.h"

GraphicsObject::GraphicsObject(Object *object) :
	object_(object)
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

QPainterPath GraphicsObject::figureShape() const
{
	QPainterPath path;
	path.addRect(boundingRect());
	return path;
}

QPainterPath GraphicsObject::shape() const
{
	return figureShape();
}

QVector <GraphicsObject *> GraphicsObject::collisions(const QPointF &vector, qreal angle)
{
	QVector <GraphicsObject *> collisions;

	QMatrix matrix;
	matrix.translate(vector.x(), vector.y());
	matrix.rotate(angle);

	QList <QGraphicsItem *> cs = scene()->items(mapToScene(matrix.map(shape())), Qt::IntersectsItemShape);
	for (QGraphicsItem *item : cs)
		if (item != static_cast<QGraphicsItem *>(this))
			collisions.append(static_cast<GraphicsObject *>(item));
	return collisions;
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
	QGraphicsObject::setRotation(HOA::rotationToAngle(object_->rotation() - object_->position()));
}