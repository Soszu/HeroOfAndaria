#ifndef GRAPHICSCREATURE_H
#define GRAPHICSCREATURE_H

#include "Graphics/GraphicsObject.h"
#include "System/Creature.h"

class GraphicsCreature : public GraphicsObject
{
public:
	GraphicsCreature(Creature *creature);

private:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
	void advance();
};

#endif // GRAPHICSCREATURE_H
