#ifndef MONSTER_H
#define MONSTER_H

#include "System/Creature.h"

class Monster : public Creature
{
public:
	Monster();

	virtual HOA::ObjectType objectType() const;
};

#endif // MONSTER_H
