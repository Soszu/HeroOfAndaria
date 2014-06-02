#ifndef GRAPHICSCREATURE_H
#define GRAPHICSCREATURE_H

#include "Graphics/GraphicsObject.h"
#include "System/Creature.h"

class QSvgRenderer;

class GraphicsCreature : public GraphicsObject
{
public:
	GraphicsCreature(Creature *creature);

	virtual QPainterPath weaponShape() const;
	virtual QPainterPath figureShape() const;
	virtual QPainterPath shape() const;

	virtual int creatureWidth() const;
	virtual int creatureHeight() const;

	static void triggerHealthVisibility();
	static bool healthVisibilityEnabled();
	static void triggerBoundingBoxesVisibility();
	static bool boundingBoxesVisibilityEnabled();

protected:

	QSvgRenderer *renderer_;
	QSvgRenderer *rendererDead_;

	virtual void initRenderer();            /** invoke this function in constructor of every derived class */

	qreal widthScale() const;               /** change from loaded image to pixmap on the screen */
	qreal heightScale() const;
	QPointF pointZero() const;              /** top left point */

	Creature * creature();

	virtual QPointF weaponAttachPoint() const;

	virtual void paintFigure(QPainter *painter);
	virtual void paintWeapon(QPainter *painter);
	virtual void paintBoundingBoxes(QPainter *painter);
	virtual void paintHealth(QPainter *painter);

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
	virtual void advance();

protected slots:
	void onDied();
};

#endif // GRAPHICSCREATURE_H
