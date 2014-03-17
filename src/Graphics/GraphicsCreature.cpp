#include "Graphics/GraphicsCreature.h"

GraphicsCreature::GraphicsCreature(Creature *creature)
	: GraphicsObject((Object *)creature)
{}

//TODO everything here
static int CREATURE_SIZE = 30;

QRectF GraphicsCreature::boundingRect() const
{
	return QRectF(-CREATURE_SIZE / 2, -CREATURE_SIZE / 2,
	              CREATURE_SIZE, CREATURE_SIZE);
}

void GraphicsCreature::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	painter->save();

	//TODO no, it's not the final version in this program

	painter->setBrush(Qt::yellow);
	painter->drawEllipse(boundingRect());

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
{}