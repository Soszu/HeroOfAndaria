#include "System/Map.h"

Map::Map(int width, int height)
	: Grid(width, height)
{
	//TEST

	player_ = new Human();

	player_->setPosition({800, 500});
	player_->setRotation({25, 800});

	addObject(player_);
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
