#include "Graphics/GraphicsMonster.h"
#include "System/DataManager.h"

GraphicsMonster::GraphicsMonster(Monster *monster) :
	GraphicsCreature(monster)
{
	initPixmap();
}

QPolygonF GraphicsMonster::weaponShape()
{
	return QPolygonF();
}

QPainterPath GraphicsMonster::figureShape()
{
	QPainterPath figure;

	figure.addEllipse(pointZero().x() - 3.0,
	                  pointZero().y() - 3.0,
	                  scale() * pixmap_->width()  + 6.0,
	                  scale() * pixmap_->height() + 6.0);

	return QPainterPath();
}

int GraphicsMonster::creatureSize() const
{
	static const int MONSTER_SIZE = 40;
	return MONSTER_SIZE;
}

void GraphicsMonster::initPixmap()
{
	pixmap_     = DataManager::pixmap(Data::ImagePath::Wolf);
	pixmapDead_ = DataManager::pixmap(Data::ImagePath::WolfDead);
}

QPointF GraphicsMonster::weaponAttachPoint()
{
	return {0.0, 0.0};
}

void GraphicsMonster::advance()
{
	return GraphicsCreature::advance();
}
