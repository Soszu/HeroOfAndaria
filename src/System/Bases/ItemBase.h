//TODO enum serialization

#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <QtWidgets>
#include "System/Uid.h"
#include "System/CommonStrings.h"
#include "System/Models/ItemModel.h"

namespace HOA {
	enum ItemType : quint8 {
		Weapon,
		Shield,
		Artefact,
		Armor
	};

	const QHash <HOA::ItemType, QString> ItemTypeLabels = {
		{HOA::ItemType::Weapon,   HOA::Strings::ItemTypeWeapon},
		{HOA::ItemType::Shield,   HOA::Strings::ItemTypeShield},
		{HOA::ItemType::Artefact, HOA::Strings::ItemTypeArtefact},
		{HOA::ItemType::Armor,    HOA::Strings::ItemTypeArmor}
	};

	enum EffectType : quint8 {
		//TODO names & content check
		maxHitPointsBonus,
		strengthBonus,
		agilityBonus,
		intelligenceBonus,
		enduranceBonus,
		damageResistanceBonus,
		armorBonus,
		hitRatioBonus
	};

	const QHash <HOA::EffectType, QString> EffectTypeLabels = {
		{HOA::EffectType::maxHitPointsBonus,     HOA::Strings::EffectTypeMaxHitPointsBonus},
		{HOA::EffectType::strengthBonus,         HOA::Strings::EffectTypeStrengthBonus},
		{HOA::EffectType::agilityBonus,          HOA::Strings::EffectTypeAgilityBonus},
		{HOA::EffectType::intelligenceBonus,     HOA::Strings::EffectTypeIntelligenceBonus},
		{HOA::EffectType::enduranceBonus,        HOA::Strings::EffectTypeEnduranceBonus},
		{HOA::EffectType::damageResistanceBonus, HOA::Strings::EffectTypeDamageResistanceBonus},
		{HOA::EffectType::armorBonus,            HOA::Strings::EffectTypeArmorBonus},
		{HOA::EffectType::hitRatioBonus,         HOA::Strings::EffectTypeHitRatioBonus}
	};

	struct Effect {
		Effect() : type(HOA::EffectType::maxHitPointsBonus), duration(0), magnitude(0)
		{}

		EffectType type;
		int duration;
		int magnitude;

		QString description(){
			return EffectTypeLabels[type] + QString(" ") + QString::number(magnitude);
		}
	};
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
	int uid_;
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
