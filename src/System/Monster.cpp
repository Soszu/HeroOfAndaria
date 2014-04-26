#include "System/Monster.h"

Monster::Monster()
{}

HOA::ObjectType Monster::objectType() const
{
	return HOA::ObjectType::Monster;
}
