#ifndef COMMON_STRINGS_H
#define COMMON_STRINGS_H

#include <QtCore>
namespace HOA {
	namespace Strings {
		const QString DefaultNewCreatureName = QObject::tr("Creature");

		const QString CreatureName           = QObject::tr("Name");
		const QString CreatureFullHitPoints  = QObject::tr("Full Hit Points");
		const QString CreatureStrength       = QObject::tr("Strength");
		const QString CreatureAgility        = QObject::tr("Agility");
		const QString CreatureIntellgence    = QObject::tr("Intelligence");
		const QString CreatureEndurance      = QObject::tr("Endurance");
	}
}

#endif
