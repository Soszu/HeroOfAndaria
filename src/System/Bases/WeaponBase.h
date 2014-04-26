//TODO enum serialization

#ifndef WEAPONBASE_H
#define WEAPONBASE_H

#include <QtWidgets>
#include "System/Uid.h"
#include "System/CommonStrings.h"
#include "System/Models/WeaponModel.h"

namespace HOA {
	enum AttackType : quint8 {
		Melee,
		Distance,
		Magic
	};

	const QHash <HOA::AttackType, QString> AttackTypeLabels = {
		{HOA::AttackType::Melee,    HOA::Strings::AttackTypeMelee},
		{HOA::AttackType::Distance, HOA::Strings::AttackTypeDistance},
		{HOA::AttackType::Magic,    HOA::Strings::AttackTypeMagic}
	};

	enum WeaponType : quint8 {
		OneHanded,
		TwoHanded
	};

	const QHash <HOA::WeaponType, QString> WeaponTypeLabels = {
		{HOA::WeaponType::OneHanded, HOA::Strings::WeaponTypeOneHanded},
		{HOA::WeaponType::TwoHanded, HOA::Strings::WeaponTypeTwoHanded}
	};
}

class WeaponBase
{
public:
	WeaponBase();
	WeaponBase(UID uid, QString name);

	UID uid() const;

	QString name() const;
	void setName(const QString &name);

	HOA::WeaponType type() const;
	void setType(HOA::WeaponType type);

	HOA::AttackType attackType() const;
	void setAttackType(HOA::AttackType type);

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

	friend QDataStream & operator << (QDataStream &out, const WeaponBase &weapon);
	friend QDataStream & operator >> (QDataStream &in, WeaponBase &weapon);

private:
	UID uid_;
	QString name_;

	HOA::WeaponType weaponType_;
	HOA::AttackType attackType_;

	int damage_;
	int hitRatio_;
	int reach_;

	int strengthModifier_;
	int agilityModifier_;
	int intelligenceModifier_;
};

#endif // WEAPONBASE_H
