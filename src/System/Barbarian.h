#ifndef BARBARIAN_H
#define BARBARIAN_H

#include "System/Creature.h"

class Barbarian : public Creature
{
public:
	Barbarian();

	virtual HOA::ObjectType objectType() const;

protected:
	void advance();
};

#endif // BARBARIAN_H
