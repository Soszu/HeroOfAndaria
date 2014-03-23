#include "System/Blacksmith.h"

Blacksmith::Blacksmith(const QString &name)
	: Place(name)
{

}
HOA::PlaceType Blacksmith::type() const
{
	return HOA::PlaceType::Blacksmith;
}
