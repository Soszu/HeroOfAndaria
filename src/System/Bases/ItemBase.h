//TODO enum serialization

#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <QtWidgets>
#include "System/CommonStrings.h"
#include "System/Models/ItemModel.h"
#include "System/Utils/Uid.h"

namespace HOA {
	enum ItemType : quint8 {
		Weapon,
		Shield,
		Artefact,
		Armor
	};

	const QMap <HOA::ItemType, QString> ItemTypeLabels = {
		{HOA::ItemType::Weapon,   HOA::Strings::ItemTypeWeapon},
		{HOA::ItemType::Shield,   HOA::Strings::ItemTypeShield},
		{HOA::ItemType::Artefact, HOA::Strings::ItemTypeArtefact},
		{HOA::ItemType::Armor,    HOA::Strings::ItemTypeArmor}
	};

	enum EffectType : quint8 {
		//TODO names & content check
		None,

		MaxHitPointsBonus,
		StrengthBonus,
		AgilityBonus,
		IntelligenceBonus,
		EnduranceBonus,
		DamageResistanceBonus,
		ArmorBonus,
		HitRatioBonus,

		PerformingAction,
		Immobilised,
		Freezed,
		Recoiling,
		CannotAttack,  //TODO something else
	};

	const QMap <HOA::EffectType, QString> EffectTypeLabels = {
		{HOA::EffectType::None,                  HOA::Strings::EffectTypeNone},

		{HOA::EffectType::MaxHitPointsBonus,     HOA::Strings::EffectTypeMaxHitPointsBonus},
		{HOA::EffectType::StrengthBonus,         HOA::Strings::EffectTypeStrengthBonus},
		{HOA::EffectType::AgilityBonus,          HOA::Strings::EffectTypeAgilityBonus},
		{HOA::EffectType::IntelligenceBonus,     HOA::Strings::EffectTypeIntelligenceBonus},
		{HOA::EffectType::EnduranceBonus,        HOA::Strings::EffectTypeEnduranceBonus},
		{HOA::EffectType::DamageResistanceBonus, HOA::Strings::EffectTypeDamageResistanceBonus},
		{HOA::EffectType::ArmorBonus,            HOA::Strings::EffectTypeArmorBonus},
		{HOA::EffectType::HitRatioBonus,         HOA::Strings::EffectTypeHitRatioBonus},

		{HOA::EffectType::PerformingAction,      HOA::Strings::EffectTypePerformingAction},
		{HOA::EffectType::Immobilised,           HOA::Strings::EffectTypeImmobilised},
		{HOA::EffectType::Freezed,               HOA::Strings::EffectTypeFreezed},
		{HOA::EffectType::Recoiling,             HOA::Strings::EffectTypeRecoiling},
		{HOA::EffectType::CannotAttack,          HOA::Strings::EffectTypeCannotAttack},
	};

	struct Effect {
		Effect(HOA::EffectType type = HOA::EffectType::None, int duration = PERMANENT, int magnitude = DEFAULT) :
			type(type), duration(duration), magnitude(magnitude)
		{}

		QString toString() const;

		bool operator==(const Effect &effect) const;

		QString description();
		bool isValid() const;

		EffectType type;
		int duration;
		int magnitude;

		/** Magnitude */
		static const int INACTIVE  =  0;
		static const int DEFAULT   =  1;
		/** Duration */
		static const int PERMANENT = -1;
	};

	QDataStream & operator << (QDataStream &out, const HOA::Effect &effect);
	QDataStream & operator >> (QDataStream &in, HOA::Effect &effect);
}

Q_DECLARE_METATYPE(HOA::Effect)

class ItemBase
{
public:
	ItemBase();
	ItemBase(UID uid, const QString &name);

	UID uid() const;

	QString name() const;
	void setName(const QString &name);

	HOA::ItemType type() const;
	void setType(HOA::ItemType type);

	int weight() const;
	void setWeight(int weight);

	int price() const;
	void setPrice(int price);

	int minStrength() const;
	void setMinStrength(int strength);

	int minAgility() const;
	void setMinAgility(int agility);

	int minIntelligence() const;
	void setMinIntelligence(int intelligence);

	QList <HOA::Effect> effects() const;
	void setEffects(QList <HOA::Effect> effect);

	friend QDataStream & operator << (QDataStream &out, const ItemBase &item);
	friend QDataStream & operator >> (QDataStream &in, ItemBase &item);

private:
	UID uid_;
	QString name_;

	HOA::ItemType type_;

	int weight_;
	int price_;

	int minStrength_;
	int minAgility_;
	int minIntelligence_;

	QList <HOA::Effect> effects_;
};

#endif // ITEMBASE_H
