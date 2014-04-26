#ifndef GRAPHICSCREATURE_H
#define GRAPHICSCREATURE_H

#include "Graphics/GraphicsObject.h"
#include "System/Creature.h"

class GraphicsCreature : public GraphicsObject
{
public:
	GraphicsCreature(Creature *creature);

	virtual QPolygonF weaponShape() const;
	virtual QPainterPath figureShape() const;
	virtual QPainterPath shape() const;

	virtual int creatureSize() const;

	static void triggerHealthVisibility();
	static bool healthVisibilityEnabled();
	static void triggerBoundingBoxesVisibility();
	static bool boundingBoxesVisibilityEnabled();

protected:
	QPixmap *pixmap_;
	QPixmap *pixmapDead_;

	virtual void initPixmap();  /** invoke this function in constructor of every derived class */

	qreal scale() const;               /** change from loaded image to pixmap on the screen */
	QPointF pointZero() const;         /** top left point */

	virtual QPointF weaponAttachPoint() const;

	virtual void paintFigure(QPainter *painter);
	virtual void paintWeapon(QPainter *painter);
	virtual void paintBoundingBoxes(QPainter *painter);
	virtual void paintHealth(QPainter *painter);

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
	virtual void advance();
};

#endif // GRAPHICSCREATURE_H
