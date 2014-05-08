#ifndef GRAPHICSCHARACTER_H
#define GRAPHICSCHARACTER_H

#include "Graphics/GraphicsCreature.h"
#include "System/Character.h"

class GraphicsCharacter : public GraphicsCreature
{
public:
	GraphicsCharacter(Character *character);

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

#endif // GRAPHICSCHARACTER_H
