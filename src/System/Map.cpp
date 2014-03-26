#include "System/Map.h"

Map::Map(int width, int height) :
	Grid(width, height)
{
	//TEST

	player_ = new Human();
	player_->setPosition({800, 500});
	player_->setRotation({25, 800});
	addObject(player_);

	Creature *creature1 = new Creature;
	creature1->setPosition({200, 300});
	creature1->setRotation({0, 0});
	addObject(creature1);

	Creature *creature2 = new Creature;
	creature2->setPosition({700, 400});
	creature2->setRotation({0, 0});
	addObject(creature2);

	Creature *creature3 = new Creature;
	creature3->setPosition({300, 600});
	creature3->setRotation({0, 0});
	addObject(creature3);
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
