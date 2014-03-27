#ifndef EDITOR_SHORTCUTS_H
#define EDITOR_SHORTCUTS_H

#include <QtCore>

namespace HOAEditor {
	namespace Shortcuts {
		const QKeySequence MenuFileNew        = QObject::tr("Ctrl+N");
		const QKeySequence MenuFileLoad       = QObject::tr("Ctrl+L");
		const QKeySequence MenuFileSave       = QObject::tr("Ctrl+S");
		const QKeySequence MenuFileQuit       = QObject::tr("Ctrl+Q");

		const QKeySequence AddCreature        = QObject::tr("Insert");
		const QKeySequence RemoveCreature     = QObject::tr("Delete");
	}
}

#endif //EDITOR_SHORTCUTS_H
