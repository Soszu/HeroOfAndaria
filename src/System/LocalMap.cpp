#include "System/LocalMap.h"
#include "System/Monster.h"
#include "System/Barbarian.h"

/**
 * \class LocalMap
 */

LocalMap::LocalMap(int width, int height, Human *player) :
	Map(width, height, player)
{
	//TODO
	test();
}

void LocalMap::exitLocation()
{
	emit locationExited();
}

void LocalMap::test()
{
	//Monster *creature = new Monster();
	//creature->setPosition({300, 300});
	//creature->setRotation({150, 600});
	//addObject(creature);

	Barbarian *creature = new Barbarian();
	creature->setPosition({100, 100});
	addObject(creature);

	Barbarian *creature2 = new Barbarian();
	creature2->setPosition({700, 700});
	addObject(creature2);
}

/**
 * \class Location
 */

Location::Location(const QString &name, LocalMap *localMap) :
	name_(name),
	localMap_(localMap)
{}

HOA::ObjectType Location::objectType() const
{
	return HOA::ObjectType::Location;
}

QString Location::name() const
{
	return name_;
}

LocalMap * Location::localMap() const
{
	return localMap_;
}

