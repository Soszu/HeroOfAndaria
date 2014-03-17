#include "System/Map.h"

Map::Map(int width, int height)
	: Grid(width, height)
{
	//TEST

	player_ = new Human();

	player_->setPosition({300, 400});
	player_->setRotation({25, 800});

	Creature *c1 = new Creature;
	c1->setPosition({200, 200});
	c1->setRotation({50, 50});

	Creature *c2 = new Creature;
	c2->setPosition({300, 300});
	c2->setRotation({120, 120});

	Creature *c3 = new Creature;
	c3->setPosition({400, 400});
	c3->setRotation({500, 500});

	addObject(player_);
	addObject(c1);
	addObject(c2);
	addObject(c3);
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

void Map::addObject(Object *object)
{
	objects_.append(object);
	emit objectAdded();
}
