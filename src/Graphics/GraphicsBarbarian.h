#ifndef GRAPHICS_BARBARIAN_H
#define GRAPHICS_BARBARIAN_H

#include "GraphicsCreature.h"
#include "System/Barbarian.h"

class GraphicsBarbarian : public GraphicsCreature
{
public:
	GraphicsBarbarian(Barbarian *barbarian);

	virtual QPainterPath weaponShape() const;

	virtual int creatureWidth() const;
	virtual int creatureHeight() const;

protected:
	virtual void initRenderer();

	virtual void paintWeapon(QPainter *painter);

	virtual void advance();

private:
	QSvgRenderer *weaponRender_;

	QPointF weaponVector_;
	qreal weaponAngle_;
};

#endif // GRAPHICS_BARBARIAN_H

