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

	if (((Creature *)object_)->hitPoints() == 0)
		painter->setBrush(Qt::darkGray);
	else if (((Creature *)object_)->currentAction() == HOA::CreatureAction::Attack)
		painter->setBrush(Qt::blue);
	else if (((Creature *)object_)->currentAction() == HOA::CreatureAction::Recoil)
		painter->setBrush(Qt::red);
	else
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
	//TODO attack, recoil
	GraphicsObject::advance();
}