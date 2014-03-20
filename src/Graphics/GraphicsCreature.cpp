#include "Graphics/GraphicsCreature.h"

GraphicsCreature::GraphicsCreature(Creature *creature)
	: GraphicsObject((Object *)creature)
{}

//TODO everything here

static int CREATURE_SIZE = 30;

QRectF GraphicsCreature::boundingRect() const
{
	return {
		qreal(-CREATURE_SIZE / 2),
		qreal(-CREATURE_SIZE / 2),
		qreal(CREATURE_SIZE),
		qreal(CREATURE_SIZE)
	};
}

QPainterPath GraphicsCreature::shape() const
{
	QPainterPath path;
	path.addEllipse(boundingRect());
	return path;
}

void GraphicsCreature::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	painter->save();

	//TODO no, it's not the final version in this program

	painter->setBrush(Qt::yellow);
	painter->drawPath(shape());

	QPolygon polygon;
	polygon << QPoint(-CREATURE_SIZE / 5, 0)
	        << QPoint(0, CREATURE_SIZE / 3)
	        << QPoint(CREATURE_SIZE / 5, 0);
	QPainterPath path;
	path.addPolygon(polygon);

	painter->setPen(Qt::black);
	painter->drawPath(path);

	painter->restore();
}

void GraphicsCreature::advance()
{
	GraphicsObject::advance();
}