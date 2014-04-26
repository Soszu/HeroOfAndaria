#ifndef EDITOR_STRINGS_H
#define EDITOR_STRINGS_H

#include <QtCore>
#include "Editor/Shortcuts.h"

namespace HOAEditor {

	namespace Messages {
		const QString HowToStart           = QObject::tr("Use \"New\" or \"Load\" from \"File\" menu to start");
		const QString ContentLoaded        = QObject::tr("Content loaded");
		const QString ContentSaved        = QObject::tr("Content saved");
	}

	namespace Strings {
		const QString MenuFile           = QObject::tr("&File");
		const QString MenuFileNew        = QObject::tr("New");
		const QString MenuFileLoad       = QObject::tr("Load");
		const QString MenuFileSave       = QObject::tr("Save");
		const QString MenuFileSaveAs     = QObject::tr("Save as");
		const QString MenuFileQuit       = QObject::tr("Quit");

		const QString LoadFileDialog             = QObject::tr("Load Content");
		const QString SaveFileDialog             = QObject::tr("Save Content");
		const QString HOAContentFilesExtension   = QObject::tr("hoa");
		const QString HOAContentFiles            = QObject::tr("HOA content files (*.%1)").arg(HOAContentFilesExtension);

		const QString CratureEditorName      = QObject::tr("Creatures");
		const QString AddCreatureButton      = QObject::tr("Add Creature");
		const QString RemoveCreatureButton   = QObject::tr("Remove Creature");

		const QString ItemEditorName     = QObject::tr("Items");
		const QString AddItemButton      = QObject::tr("Add Item");
		const QString RemoveItemButton   = QObject::tr("Remove Item");
		const QString AddEffectButton    = QObject::tr("Add Effect");
		const QString RemoveEffectButton = QObject::tr("Remove Effect");

		const QString ItemsListLabel     = QObject::tr("Items list");
		const QString ItemNameLabel      = QObject::tr("Item name");
		const QString ItemTypeLabel      = QObject::tr("Item type");
		const QString ItemDetailsLabel   = QObject::tr("Item details");
		const QString WeaponDetailsLabel = QObject::tr("Weapon details");
		const QString ItemEffectsLabel   = QObject::tr("Item effects");
		const QString EffectsListLabel   = QObject::tr("Effects list");
		const QString EffectDetailsLabel = QObject::tr("Effect details");
	}
}

#endif //EDITOR_STRINGS_H
