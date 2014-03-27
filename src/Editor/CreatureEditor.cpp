#include "Editor/CreatureEditor.h"

CreatureEditor::CreatureEditor() : ContentEditor(HOAEditor::Strings::CratureEditorName)
{
	initView();
	initButtonsAndLayout();
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

void CreatureEditor::saveToStream(QDataStream &out)
{
	out << *model;
}

void CreatureEditor::loadFromStream(QDataStream& in)
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

	widget_ = view;

	mapper = new QDataWidgetMapper(this);
	mapper->setModel(model);
	mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
	connect(view->selectionModel(), &QItemSelectionModel::currentRowChanged, mapper, &QDataWidgetMapper::setCurrentModelIndex);
}

void CreatureEditor::initButtonsAndLayout()
{
	QPushButton *addCreatureButton = new QPushButton(HOAEditor::Strings::AddCreatureButton);
	addCreatureButton->setShortcut(HOAEditor::Shortcuts::AddCreature);
	connect(addCreatureButton, &QPushButton::clicked, this, &CreatureEditor::addCreature);

	QPushButton *removeCreatureButton = new QPushButton(HOAEditor::Strings::RemoveCreatureButton);
	removeCreatureButton->setShortcut(HOAEditor::Shortcuts::RemoveCreature);
	connect(removeCreatureButton, &QPushButton::clicked, this, &CreatureEditor::removeCreature);

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
