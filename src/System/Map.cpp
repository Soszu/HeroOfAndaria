#include "System/Map.h"

Map::Map(int width, int height) :
	Grid(width, height)
{
	//TEST

	player_ = new Human();

	player_->setPosition({800, 500});
	player_->setRotation({25, 800});

	Creature *creature = new Creature;

	creature->setPosition({200, 300});
	creature->setRotation({0, 0});

	addObject(player_);
	addObject(creature);
}

Object * Map::newestObject()
{
	if (objects_.isEmpty())
		return nullptr;
	else
		return objects_.last();
}

const QVector <Object *> & Map::objects() const
{
	return objects_;
}

Human * Map::player()
{
	return player_;
}

void Map::onCollision(Object *object, const QVector <Object *> &collisions)
{}

void Map::addObject(Object *object)
{
	objects_.append(object);
	emit objectAdded();
}
