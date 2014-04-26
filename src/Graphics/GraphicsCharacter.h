#ifndef GRAPHICSCHARACTER_H
#define GRAPHICSCHARACTER_H

#include "Graphics/GraphicsCreature.h"
#include "System/Character.h"

class GraphicsCharacter : public GraphicsCreature
{
public:
	GraphicsCharacter(Character *character);

	virtual QPolygonF weaponShape() const;
	virtual QPainterPath figureShape() const;

	virtual int creatureSize() const;

protected:
	virtual void initPixmap();

	virtual void paintWeapon(QPainter *painter);

	virtual void advance();

private:
	QPixmap *weaponPixmap_;

	QPointF weaponVector_;
	qreal weaponAngle_;
};

#endif // GRAPHICSCHARACTER_H
