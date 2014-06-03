#ifndef CREATUREBASE_H
#define CREATUREBASE_H

#include <QtWidgets>
#include "System/CommonStrings.h"
#include "System/Models/CreatureModel.h"
#include "System/Utils/Uid.h"

class CreatureBase
{

public:
	CreatureBase();
	CreatureBase(UID uid, const QString &name);
	CreatureBase(const CreatureBase &creature);
	CreatureBase(const QString &name,
	             int fullHitPoints,
	             int strength,
	             int agility,
	             int intelligence,
	             int endurance);

	UID uid() const;

	QString name() const;
	void setName(const QString &name);

	int fullHitPoints() const;
	void setFullHitPoints(int fullHitPoints);

	int strength() const;
	void setStrength(int strength);
	int agility() const;
	void setAgility(int agility);
	int intelligence() const;
	void setIntelligence(int intelligence);
	int endurance() const;
	void setEndurance(int endurance);

	friend QDataStream & operator << (QDataStream &out, const CreatureBase &creature);
	friend QDataStream & operator >> (QDataStream &in, CreatureBase &creature);

private:
	UID uid_;

	QString name_;

	int fullHitPoints_;

	int strength_;
	int agility_;
	int intelligence_;
	int endurance_;
};

#endif // CREATUREBASE_H
