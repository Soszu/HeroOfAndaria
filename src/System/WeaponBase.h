/*
 *  operators >> ,<<
 *  constructors
 *  model
 */

#ifndef WEAPONBASE_H
#define WEAPONBASE_H

#include <QtWidgets>
#include "System/Uid.h"

namespace HOA {
	enum WeaponType : quint8 {
		Melee,
		Ranged,
		Magic
	};
}

class WeaponBase
{
public:
	WeaponBase();
	//WeaponBase(UID uid, QString name);
	WeaponBase(const WeaponBase &weapon );
	//TODO?
	/*
	WeaponBase(const QString &name,
	           int damage,
	           int hitRatio,
	           int reach,
	           int strengthInfluence,
	           int agilityInfluence,
	           int intelligenceInfluence,
	           HOA::WeaponType type);*/

	int damage() const;
	void setDamage(int damage);

	int hitRatio() const;
	void setHitRatio(int hitRatio);

	int reach() const;
	void setReach(int reach);

	int strengthInfluence() const;
	void setStrengthInfluence(int strengthInfluence);

	int agilityInfluence() const;
	void setAgilityInfluence(int agilityInfluence);

	int intelligenceInfluence() const;
	void setIntelligenceInfluence(int intelligenceInfluence);

	WeaponType weaponType() const;
	void setType(WeaponType type);

	friend QDataStream & operator << (QDataStream &out, const WeaponBase &weapon);
	friend QDataStream & operator >> (QDataStream &in, WeaponBase &weapon);

private:
	int damage_;
	int hitRatio_;
	int reach_;

	int strengthInfluence_;
	int agilityInfluence_;
	int intelligenceInfluence_;

	HOA::WeaponType weaponType_;
};

/* ---------------  Weapon Model class -------------------------- */

#endif // WEAPONBASE_H
