#ifndef COMMON_STRINGS_H
#define COMMON_STRINGS_H

#include <QtCore>
namespace HOA {
	namespace Strings {
		const QString DefaultNewCreatureName = QObject::tr("Creature");

		const QString CreatureName           = QObject::tr("Name");
		const QString CreatureFullHitPoints  = QObject::tr("Full hit points");
		const QString CreatureStrength       = QObject::tr("Strength");
		const QString CreatureAgility        = QObject::tr("Agility");
		const QString CreatureIntellgence    = QObject::tr("Intelligence");
		const QString CreatureEndurance      = QObject::tr("Endurance");

		const QString DefaultNewItemName = QObject::tr("Item");

		const QString ItemName             = QObject::tr("Name");
		const QString ItemType             = QObject::tr("Type");
		const QString ItemWeight           = QObject::tr("Weight");
		const QString ItemPrice            = QObject::tr("Price");
		const QString ItemMinStrength      = QObject::tr("Minimal strength");
		const QString ItemMinAgility       = QObject::tr("Minimal agility");
		const QString ItemMinIntelligence  = QObject::tr("Minimal intelligence");
		const QString ItemEffects          = QObject::tr("Effects");

		const QString ItemTypeWeapon   = QObject::tr("Weapon");
		const QString ItemTypeShield   = QObject::tr("Shield");
		const QString ItemTypeArmor    = QObject::tr("Armor");
		const QString ItemTypeArtefact = QObject::tr("Artefact");

		const QString ItemEffectType       = QObject::tr("Type");
		const QString ItemEffectMagnitude  = QObject::tr("Magnitude");
		const QString ItemEffectDuration    = QObject::tr("Duration");

		const QString EffectTypeMaxHitPointsBonus     = QObject::tr("Max hit points bonus");
		const QString EffectTypeStrengthBonus         = QObject::tr("Strength bonus");
		const QString EffectTypeAgilityBonus          = QObject::tr("Agility bonus");
		const QString EffectTypeIntelligenceBonus     = QObject::tr("Intelligence bonus");
		const QString EffectTypeEnduranceBonus        = QObject::tr("Endurance bonus");
		const QString EffectTypeDamageResistanceBonus = QObject::tr("Damage Resistance bonus");
		const QString EffectTypeArmorBonus            = QObject::tr("Armor bonus");
		const QString EffectTypeHitRatioBonus         = QObject::tr("Hit ratio bonus");

		const QString DefaultNewWeaponName = QObject::tr("Weapon");

		const QString WeaponName                 = QObject::tr("Name");
		const QString WeaponType                 = QObject::tr("Type");
		const QString WeaponAttackType           = QObject::tr("Attack type");
		const QString WeaponDamage               = QObject::tr("Damage");
		const QString WeaponReach                = QObject::tr("Reach");
		const QString WeaponHitRatio             = QObject::tr("Hit ratio");
		const QString WeaponStrengthModifier     = QObject::tr("Strength modifier");
		const QString WeaponAgilityModifier      = QObject::tr("Agility modifier");
		const QString WeaponIntelligenceModifier = QObject::tr("Intelligence modifier");

		const QString WeaponTypeOneHanded = QObject::tr("One Handed");
		const QString WeaponTypeTwoHanded = QObject::tr("Two Handed");

		const QString AttackTypeMelee    = QObject::tr("Melee");
		const QString AttackTypeDistance = QObject::tr("Distance");
		const QString AttackTypeMagic    = QObject::tr("Magic");
	}
}

#endif
