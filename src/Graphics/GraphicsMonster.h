#ifndef GRAPHICSMONSTER_H
#define GRAPHICSMONSTER_H

#include "Graphics/GraphicsCreature.h"
#include "System/Monster.h"

class GraphicsMonster : public GraphicsCreature
{
public:
	GraphicsMonster(Monster *monster);

	virtual QPolygonF weaponShape();

	virtual int creatureWidth() const;
	virtual int creatureHeight() const;

protected:
	virtual void initRenderer();

	virtual QPointF weaponAttachPoint();

	virtual void advance();
};

#endif // GRAPHICSMONSTER_H