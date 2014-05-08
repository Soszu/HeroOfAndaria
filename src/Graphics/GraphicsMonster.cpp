#include "Graphics/GraphicsMonster.h"
#include "System/DataManager.h"

GraphicsMonster::GraphicsMonster(Monster *monster) :
	GraphicsCreature(monster)
{
	initRenderer();
}

QPainterPath GraphicsMonster::weaponShape() const
{
	QPainterPath weapon;
	weapon.addEllipse(weaponAttachPoint(), creatureWidth() / 2, creatureHeight() / 4);
	return weapon;
}

int GraphicsMonster::creatureHeight() const
{
	static const int MONSTER_HEIGHT = 100;
	return MONSTER_HEIGHT;
}

int GraphicsMonster::creatureWidth() const
{
	static const int MONSTER_WIDTH = 30;
	return MONSTER_WIDTH;
}

void GraphicsMonster::initRenderer()
{
	renderer_     = DataManager::renderer(Data::ImagePath::Wolf);
	rendererDead_ = DataManager::renderer(Data::ImagePath::WolfDead);
}

QPointF GraphicsMonster::weaponAttachPoint() const
{
	return {0.0, qreal(creatureHeight()) * 0.28};
}

void GraphicsMonster::advance()
{
	return GraphicsCreature::advance();
}
