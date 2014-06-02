#ifndef CREATURE_H
#define CREATURE_H

#include "System/Attack.h"
#include "System/Bases/CreatureBase.h"
#include "System/EquipmentCarrier.h"
#include "System/Movable.h"
#include "System/Utils/Uid.h"
#include "System/Weapon.h"

namespace HOA {
	enum class CreatureAction : quint8 {
		None,
		Attack,
		Recoil,
	};
}

class Creature : public Movable, public EquipmentCarrier
{
Q_OBJECT;

public:
	Creature(const CreatureBase *base = nullptr);
	~Creature();

	virtual HOA::ObjectType objectType() const;

	void setBase(const CreatureBase *base);

	qreal maxSpeed() const;

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

	Attack currentAttack() const;

	virtual bool canMove() const;
	virtual bool canRotate() const;
	bool canPerformAction(HOA::CreatureAction action);

	//TODO To the wastebin!
	HOA::CreatureAction currentAction() const;
	int currentActionTime() const;
	int currentActionTotalTime() const;

	friend QDataStream & operator << (QDataStream &out, const Creature &creature);
	friend QDataStream & operator >> (QDataStream &in, Creature &creature);

public slots:
	virtual void advance();

signals:
	void hitPointsChanged();
	void died();

private:
	void initStats();
	void initActions();

	const CreatureBase *base_;
	int hitPoints_;

	QVector <HOA::Effect> effects_;

	QTimeLine actionTimeLine_;
	HOA::CreatureAction currentAction_;

	QVector <Weapon *> weapons_;
	Weapon *currentWeapon_;

	Attack currentAttack_;

	//TODO looks like in wrong place? // yeah, when the speed momentum works this will be unnecessary
	QPointF recoilDirection_;

private slots:
	void onActionFinished();
};

#endif // CREATURE_H
