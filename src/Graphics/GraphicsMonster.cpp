#include "Graphics/GraphicsMonster.h"
#include "System/DataManager.h"

GraphicsMonster::GraphicsMonster(Monster *monster) :
	GraphicsCreature(monster)
{
	initRenderer();
}

QPolygonF GraphicsMonster::weaponShape()
{
	return QPolygonF();
}

int GraphicsMonster::creatureHeight() const
{
	static const int MONSTER_HEIGHT = 120;
	return MONSTER_HEIGHT;
}

int GraphicsMonster::creatureWidth() const
{
	static const int MONSTER_WIDTH = 50;
	return MONSTER_WIDTH;
}

void GraphicsMonster::initRenderer()
{
	renderer_     = DataManager::renderer(Data::ImagePath::Wolf);
	rendererDead_ = DataManager::renderer(Data::ImagePath::WolfDead);
}

QPointF GraphicsMonster::weaponAttachPoint()
{
	return {0.0, 0.0};
}

void GraphicsMonster::advance()
{
	return GraphicsCreature::advance();
}
