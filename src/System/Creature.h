#ifndef CREATURE_H
#define CREATURE_H

#include "System/Attack.h"
#include "System/CreatureBase.h"
#include "System/EquipmentCarrier.h"
#include "System/Movable.h"
#include "System/Uid.h"
#include "System/Weapon.h"

namespace HOA {
	enum class CreatureAction : quint8 {
		None,
		Attack,
		Recoil,
	};
}

/**
 * \class Creature
 */
class Creature : public Movable, public EquipmentCarrier
{
Q_OBJECT;

public:
	Creature(const CreatureBase *base = nullptr);
	~Creature();

	virtual HOA::ObjectType objectType() const;

	//TODO ekhm. Not private?
	void initStats();
	void initActions();

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

	void setCurrentWeapon(Weapon *weapon);
	Weapon * currentWeapon() const;

	//TODO in effects and certainly not in public
	bool freezed_;

	HOA::CreatureAction currentAction() const;
	int currentActionTime() const;
	int currentActionTotalTime() const;

	friend QDataStream & operator << (QDataStream &out, const Creature &creature);
	friend QDataStream & operator >> (QDataStream &in, Creature &creature);

signals:
	void hitPointsChanged();

private:
	const CreatureBase *base_;
	int hitPoints_;

	QTimeLine actionTimeLine_;
	HOA::CreatureAction currentAction_;

	QVector <Weapon *> weapons_;
	Weapon *currentWeapon_;

private slots:
	void onActionFinished();
};

#endif // CREATURE_H
