#include "System/GlobalMap.h"

//TODO
#include "System/Blacksmith.h"
#include "System/Inn.h"

GlobalMap::GlobalMap(int width, int height, Human *player)
	: Map(width, height, player), currentTown_(nullptr)
{
	//TODO
	test();
}

bool GlobalMap::canCollide(const Movable *lhs, const Object *rhs) const
{
	if (rhs->objectType() == HOA::ObjectType::Town
	    || rhs->objectType() == HOA::ObjectType::Location)
		return true;
	else
		return Map::canCollide(lhs, rhs);
}

void GlobalMap::onCollision(Object *object, const QVector <Object *> &collisions)
{
	//TODO
	Map::onCollision(object, collisions);
}

void GlobalMap::addObject(Object *object)
{
	if (object->objectType() == HOA::ObjectType::Town)
		connect((Town *)object,
		        &Town::townExited,
		        this,
		        &GlobalMap::onTownExited);
	else if (object->objectType() == HOA::ObjectType::Location)
		connect(((Location *)object)->localMap(),
		        &LocalMap::locationExited,
		        this,
		        &GlobalMap::onLocationExited);
	Map::addObject(object);
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
	emit townExited();
	currentTown_ = nullptr;
}

QVector <Location *> GlobalMap::locations() const
{
	QVector <Location *> ls;
	for (Object *obj : objects_)
		if (obj->objectType() == HOA::ObjectType::Location)
			ls.append((Location *)obj);
	return ls;
}

Location * GlobalMap::currentLocation() const
{
	return currentLocation_;
}

void GlobalMap::enterLocation(Location *location)
{
	currentLocation_ = location;
	emit locationEntered();
}

void GlobalMap::exitLocation(Location *location)
{
	emit locationExited();
	currentLocation_ = nullptr;
}

void GlobalMap::test()
{
	// add town

	Town *myTown = new Town("Moja towna");

	Blacksmith *bl = new Blacksmith("Kowal");
	Inn *inn = new Inn("Gospoda");

	myTown->addPlace(bl);
	myTown->addPlace(inn);

	myTown->setPosition({500, 500});
	myTown->setRotation(myTown->position() + QPoint(0, 10));

	addObject(myTown);

	// add location

	LocalMap *localMap = new LocalMap(150, 150, player());

	Location *myLocation = new Location("Psia buda", localMap);

	myLocation->setPosition({700, 200});
	myLocation->setRotation(myLocation->position() + QPoint(0, 10));

	addObject(myLocation);
	
	
	player()->setPosition({700, 200});
}

void GlobalMap::onTownExited()
{
	exitTown(currentTown_);
}

void GlobalMap::onLocationExited()
{
	exitLocation(currentLocation_);
}
