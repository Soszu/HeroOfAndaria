#ifndef CREATURE_H
#define CREATURE_H

#include "System/Attack.h"
#include "System/CreatureBase.h"
#include "System/EquipmentCarrier.h"
#include "System/Movable.h"
#include "System/Uid.h"

/**
 * \class Creature
 */

class Creature : public EquipmentCarrier, public Movable
{
public:
	Creature(const CreatureBase *base = nullptr);

	virtual HOA::ObjectType objectType() const;

	void initStats();
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

	friend QDataStream & operator << (QDataStream &out, const Creature &creature);
	friend QDataStream & operator >> (QDataStream &in, Creature &creature);

signals:
	void hitPointsChanged();

private:
	const CreatureBase *base;
	int hitPoints_;

	QList <HOA::Effect *> activeEffects_;
};

#endif // CREATURE_H
