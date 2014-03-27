#ifndef EDITOR_STRINGS_H
#define EDITOR_STRINGS_H

#include <QtCore>
#include "Editor/Shortcuts.h"

namespace HOAEditor {
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
	}
}

#endif //EDITOR_STRINGS_H
