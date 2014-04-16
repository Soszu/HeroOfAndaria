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

	int strengthModifier() const;
	void setStrengthModifier(int strengthModifier);

	int agilityModifier() const;
	void setAgilityModifier(int agilityModifier);

	int intelligenceModifier() const;
	void setIntelligenceModifier(int intelligenceModifier);

	HOA::WeaponType weaponType() const;
	void setType(HOA::WeaponType type);

	friend QDataStream & operator << (QDataStream &out, const WeaponBase &weapon);
	friend QDataStream & operator >> (QDataStream &in, WeaponBase &weapon);

private:
	UID uid_;
	QString name_;

	int damage_;
	int hitRatio_;
	int reach_;

	int strengthModifier_;
	int agilityModifier_;
	int intelligenceModifier_;

	HOA::WeaponType weaponType_;
};

/* ---------------  Weapon Model class -------------------------- */

#endif // WEAPONBASE_H
