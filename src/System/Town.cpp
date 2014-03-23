#include "System/Town.h"

Town::Town()
{}

HOA::ObjectType Town::objectType() const
{
	return HOA::ObjectType::Town;
}

/**
 * @brief Town::visitPlace(Place *) - players enters place
 * @param p - entered place
 */
void Town::visitPlace(Place *p)
{
	/* TODO
		tu bedzie to co sie dzieje
		po wejsciu do obiektu
	*/
}

const QVector <Place *> & Town::places() const
{
	return this->places_;
}

void Town::addPlace(Place* p)
{
	this->places_.append(p);
}
