#include "System/GlobalMap.h"

//TEST
#include "System/Blacksmith.h"
#include "System/Inn.h"

GlobalMap::GlobalMap(int width, int height)
	: Map(width, height), currentTown_(nullptr)
{
	//TEST
	Town *myTown = new Town("Moja towna");

	Blacksmith *bl = new Blacksmith("Kowal");
	Inn *inn = new Inn("Gospoda");

	myTown->addPlace(bl);
	myTown->addPlace(inn);

	myTown->setPosition({500, 500});
	myTown->setRotation(myTown->position() + QPoint(0, 10));

	addObject(myTown);
}


bool GlobalMap::canCollide(const Movable *lhs, const Object *rhs) const
{
	if (lhs->objectType() == HOA::ObjectType::Human && rhs->objectType() == HOA::ObjectType::Town)
		return true;
	else
		return Map::canCollide(lhs, rhs);
}

void GlobalMap::onCollision(Object *object, const QVector <Object *> &collisions)
{
	//TODO
	Map::onCollision(object, collisions);
}

QVector <Town *> GlobalMap::towns() const
{
	QVector <Town *> ts;
	for (Object *obj : objects_)
		if (obj->objectType() == HOA::ObjectType::Town)
			ts.append((Town *)obj);
	return ts;
}

Town * GlobalMap::currentTown() const
{
	return currentTown_;
}

void GlobalMap::enterTown(Town *town)
{
	currentTown_ = town;
	emit townEntered();
}

void GlobalMap::exitTown(Town *town)
{
	currentTown_ = nullptr;
	emit townExited();
}

void GlobalMap::addObject(Object *object)
{
	if (object->objectType() == HOA::ObjectType::Town)
		connect((Town *)object, &Town::townExited, this, &GlobalMap::onTownExited);
	Map::addObject(object);
}

void GlobalMap::onTownExited()
{
	exitTown(currentTown_);
}
