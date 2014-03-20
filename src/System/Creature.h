/*TODO
 * modify getters so they contain effects info and items info.
 * serialization of EQCarrier
 * stronger EQCarrier API?
 * EQCarrier setter?
 * rethink Effects stuff
 */

/*
 * why const EQCarrier & CreatureBase setters works?
 * can we add utils just like that, licence stuff...
 */

#ifndef CREATURE_H
#define CREATURE_H

#include "System/Attack.h"
#include "System/CreatureBase.h"
#include "System/EquipmentCarrier.h"
#include "System/Movable.h"
#include "System/Uid.h"

//Probably temporary solution; CreatureBase may be considered as Effect
namespace HOA {
	struct Effect {
		int maxHitPoints;
		int strength;
		int agility;
		int intelligence;
		int endurance;

		//int damageResistance;
		//int armor;
	};
}
/* ---------------  Creature class -------------------------- */

class Creature : public EquipmentCarrier, public Movable
{
public:
	Creature(const CreatureBase *base = nullptr);

	virtual HOA::ObjectType objectType() const;

	void setBase(const CreatureBase *base);

	int maxSpeed() const;


	UID uid() const;

	QString name() const;

	int hitPoints() const;
	void setHitPoints(int hitPoints);
	int fullHitPoints() const;

	int strength() const;
	int agility() const;
	int intelligence() const;
	int endurance() const;

	void attack(const Attack &attack);
	void receiveAttack(const Attack &attack);

	//const EquipmentCarrier * equipmentCarrier() const;

	friend QDataStream & operator << (QDataStream &out, const Creature &creature);
	friend QDataStream & operator >> (QDataStream &in, Creature &creature);

private:
	const CreatureBase *base;
	int hitPoints_;

	QList <HOA::Effect *> activeEffects_;
	//const EquipmentCarrier * equipmentCarrier_;

};

#endif // CREATURE_H
