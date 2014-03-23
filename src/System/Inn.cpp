#include "System/Inn.h"

Inn::Inn(const QString &name)
	: Place(name)
{}


HOA::PlaceType Inn::type() const
{
	return HOA::PlaceType::Inn;
}
