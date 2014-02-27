#ifndef CREATURE_H
#define CREATURE_H

#include "Attack.h"
#include "CreatureBase.h"
#include "EquipmentCarrier.h"
#include "Movable.h"

class Creature : public EquipmentCarrier, public Movable
{
public:
	Creature();

	void attack(const Attack &attack) const;
	void receiveAttack(const Attack &attack);

private:
	const CreatureBase *base;
};

#endif // CREATURE_H
