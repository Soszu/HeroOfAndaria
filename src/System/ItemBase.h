/*
 * operators <<, >>
 * constructors
 * model
 */

#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <QtWidgets>
#include "System/Uid.h"

namespace HOA {
	enum ItemType : quint8 {
		OneHandedWeapon,
		TwoHandedWeapon,
		Shield,
		Armor,
		Artefact,
		Tool
	};

//I didn't get the purpouse of enum below, so I filled it with junk.
	enum EffectType : quint8 {
		FromItem
	};

	struct Effect {
		EffectType type;
		int duration;

		int maxHitPoints;

		int strength;
		int agility;
		int intelligence;
		int endurance;

		int damageResistance;
		int armor;

		int damage;
		int hitRatio;
	};
}

class ItemBase
{
public:
	ItemBase();

	UID uid() const;

	QString name() const;
	void setName(const QString &name);

	HOA::Effect effect() const;
	void setEffect(HOA::Effect effect);

	HOA::ItemType type() const;
	void setType(HOA::ItemType type);

	int weight() const;
	void setWeight(int weight);

	int price() const;
	void setPrice(int price);

	int minStrength() const;
	void setMinStrength(int strength);

	int minIntelligence() const;
	void setMinIntelligence(int intelligence);

	int minAgility() const;
	void setMinAgility(int agility);

	friend QDataStream & operator << (QDataStream &out, const ItemBase &item);
	friend QDataStream & operator >> (QDataStream &in, ItemBase &item);

private:
	int uid_;
	QString name_;

	HOA::ItemType type_;

	int weight_;
	int price_;

	HOA::Effect effect_;

	int minStrength_;
	int minIntelligence_;
	int minAgility_;
};

#endif // ITEMBASE_H
