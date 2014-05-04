#include "System/Monster.h"

Monster::Monster()
{}

HOA::ObjectType Monster::objectType() const
{
	return HOA::ObjectType::Monster;
}

void Monster::advance()
{
	Movable::move(HOA::Direction::Front);
	Movable::advance();
}
