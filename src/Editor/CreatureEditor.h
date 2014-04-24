#ifndef CREATUREEDITOR_H
#define CREATUREEDITOR_H

#include <QtWidgets>
#include "Editor/ContentEditor.h"
#include "Editor/Strings.h"
#include "System/Bases/CreatureBase.h"

class CreatureEditor : public ContentEditor
{
Q_OBJECT

public:
	CreatureEditor();
	void clear();
	bool isChanged() const;
	void saveToStream(QDataStream &out) const;
	void loadFromStream(QDataStream &in);

public slots:
	void modelSaved();

private:
	void initView();
	void initButtons();
	void initLayout();

	QTableView *view;
	CreatureModel *model;

	QPushButton *addCreatureButton;
	QPushButton *removeCreatureButton;

private slots:
	void addCreature();
	void removeCreature();
};

#endif // CREATUREEDITOR_H
