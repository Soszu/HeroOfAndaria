#ifndef CHARACTER_H
#define CHARACTER_H

#include "System/Creature.h"
#include "System/QuestCarrier.h"

/**
 * \class Character
 * Represents a non-monster being, human for instance.
 */
class Character : public Creature
{
public:
	Character();
};

#endif // CHARACTER_H
