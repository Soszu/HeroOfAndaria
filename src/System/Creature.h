#ifndef CREATURE_H
#define CREATURE_H

#include "System/Attack.h"
#include "System/CreatureBase.h"
#include "System/EquipmentCarrier.h"
#include "System/Movable.h"

class Creature : public EquipmentCarrier, public Movable
{
public:
	Creature();

	virtual HOA::ObjectType objectType() const;

	void attack(const Attack &attack) const;
	void receiveAttack(const Attack &attack);

private:
	const CreatureBase *base;
};

#endif // CREATURE_H
