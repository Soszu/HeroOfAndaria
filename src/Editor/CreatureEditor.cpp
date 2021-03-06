#include "Editor/CreatureEditor.h"

CreatureEditor::CreatureEditor() : ContentEditor(HOAEditor::Strings::CratureEditorName)
{
	initView();
	initButtons();
	initLayout();
}

void CreatureEditor::clear()
{
	model->reset();
}

bool CreatureEditor::isChanged() const
{
	return model->isChanged();
}

void CreatureEditor::modelSaved()
{
	model->setChanged(false);
}

void CreatureEditor::saveToStream(QDataStream &out) const
{
	out << *model;
}

void CreatureEditor::loadFromStream(QDataStream &in)
{
	in >> *model;
}

void CreatureEditor::initView()
{
	view = new QTableView;
	model = &CreatureModel::instance();
	view->setModel(model);
	view->setSelectionBehavior(QAbstractItemView::SelectRows);
	view->setSelectionMode(QAbstractItemView::SingleSelection);
}

void CreatureEditor::initButtons()
{
	addCreatureButton = new QPushButton(HOAEditor::Strings::AddCreatureButton);
	addCreatureButton->setShortcut(HOAEditor::Shortcuts::AddCreature);
	connect(addCreatureButton, &QPushButton::clicked, this, &CreatureEditor::addCreature);

	removeCreatureButton = new QPushButton(HOAEditor::Strings::RemoveCreatureButton);
	removeCreatureButton->setShortcut(HOAEditor::Shortcuts::RemoveCreature);
	connect(removeCreatureButton, &QPushButton::clicked, this, &CreatureEditor::removeCreature);
}

void CreatureEditor::initLayout()
{
	QVBoxLayout *mainLayout = new QVBoxLayout;
	QHBoxLayout *buttonLayout = new QHBoxLayout;

	mainLayout->addWidget(view);
	mainLayout->addLayout(buttonLayout);

	buttonLayout->addWidget(addCreatureButton);
	buttonLayout->addWidget(removeCreatureButton);
	buttonLayout->addStretch();

	widget_ = new QWidget;
	widget_->setLayout(mainLayout);
}

void CreatureEditor::addCreature()
{
	model->insertRows(model->rowCount(), 1);
}

void CreatureEditor::removeCreature()
{
	QModelIndex selected = view->selectionModel()->currentIndex();
	if (!selected.isValid())
		return;

	model->removeRows(selected.row(), 1);
}
