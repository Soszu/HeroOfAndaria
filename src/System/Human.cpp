#include "System/Human.h"

Human::Human()
{}

HOA::ObjectType Human::objectType() const
{
	return HOA::ObjectType::Human;
}
