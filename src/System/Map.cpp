#include "System/Map.h"

Map::Map(int width, int height, Human *player) :
	Grid(width, height), player_(player)
{
	//TODO
	test();
}

Object * Map::newestObject()
{
	return newestObject_;
}

const QVector <Object *> & Map::objects() const
{
	return objects_;
}

Human * Map::player()
{
	return player_;
}

bool Map::canCollide(const Movable *lhs, const Object *rhs) const
{
	return lhs == rhs;
}

void Map::onCollision(Object *object, const QVector <Object *> &collisions)
{}

void Map::addObject(Object *object)
{
	objects_.append(object);
	newestObject_ = object;
	emit objectAdded();
}

void Map::test()
{
	player_->setPosition({800, 500});
	player_->setRotation({25, 800});
	addObject(player_);
}