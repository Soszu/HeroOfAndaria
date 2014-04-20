#ifndef GRAPHICSCREATURE_H
#define GRAPHICSCREATURE_H

#include "Graphics/GraphicsObject.h"
#include "System/Creature.h"

class GraphicsCreature : public GraphicsObject
{
public:
	GraphicsCreature(Creature *creature);

	QPolygonF weaponShape() const;
	QPainterPath figureShape() const;
	QPainterPath shape() const;

private:
	QPixmap *pixmap_;
	QPixmap *weaponPixmap_;

	QPointF weaponVector_;
	qreal weaponAngle_;

	qreal scale() const;               // change from loaded image to pixmap on the screen
	QPointF pointZero() const;         // top left point
	QPointF weaponAttachPoint() const;

	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
	void advance();
};

#endif // GRAPHICSCREATURE_H
