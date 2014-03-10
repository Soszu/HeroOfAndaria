#include "System/Creature.h"

Creature::Creature()
{

}

HOA::ObjectType Creature::objectType() const
{
	return HOA::ObjectType::Creature;
}
