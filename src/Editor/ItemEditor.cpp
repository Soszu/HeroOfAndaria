#include "Editor/ItemEditor.h"

EffectsListWidget::EffectsListWidget(const QString &title, QDataWidgetMapper *mapper, QWidget *parent) : QGroupBox(title, parent), mapper_(mapper)
{
	initButtons();
	initEditors();
	initList();
	initLayout();
}

QList< HOA::Effect > EffectsListWidget::effects() const
{
	return effects_;
}

void EffectsListWidget::setEffects(QList< HOA::Effect > effects)
{
	effectsModel->removeRows(0, effects_.count());

	effectsNames.clear();
	for (auto effect : effects)
		effectsNames.append(effect.description());
	effectsModel->setStringList(effectsNames);

	effects_ = effects;
}

void EffectsListWidget::addEffect()
{
	effectsModel->insertRow(effects_.count());
	effects_.push_back(HOA::Effect());
	effectsModel->setData(effectsModel->index(effects_.count()), effects_.back().description());
	mapper_->submit();
}

void EffectsListWidget::removeEffect()
{
	QModelIndex selected = effectsListEdit->selectionModel()->currentIndex();
	if (!selected.isValid())
		return;

	effectsModel->removeRow(selected.row());
	effects_.removeAt(selected.row());
	mapper_->submit();
}

void EffectsListWidget::updateEditors(const QModelIndex& index)
{
	if (!index.isValid())
		return;

	HOA::Effect effect = effects_[index.row()];

	//effectTypeEdit
	int idx = 0;
	while (idx < HOA::EffectTypeLabels.count() && effect.type != effectTypeEdit->itemData(idx))
		++idx;
	effectTypeEdit->setCurrentIndex(idx);

	//effectMagnitudeEdit
	effectMagnitudeEdit->setValue(effect.magnitude);

	//effectDurationEdit
	effectDurationEdit->setValue(effect.duration);
	//effectsListEdit->setCurrentIndex(index);
}

void EffectsListWidget::updateEffectType(int i)
{
	QModelIndex selected = effectsListEdit->selectionModel()->currentIndex();
	if (!selected.isValid())
		return;

	effects_[selected.row()].type = static_cast<HOA::EffectType>(effectTypeEdit->itemData(i).toInt());
	mapper_->submit();
	effectsListEdit->setCurrentIndex(selected);
}

void EffectsListWidget::updateEffectMagnitude(int i)
{
	QModelIndex selected = effectsListEdit->selectionModel()->currentIndex();
	if (!selected.isValid())
		return;

	effects_[selected.row()].magnitude = i;
	mapper_->submit();
	effectsListEdit->setCurrentIndex(selected);
}

void EffectsListWidget::updateEffectDuration(int i)
{
	QModelIndex selected = effectsListEdit->selectionModel()->currentIndex();
	if (!selected.isValid())
		return;

	effects_[selected.row()].duration = i;
	mapper_->submit();
	effectsListEdit->setCurrentIndex(selected);
}

void EffectsListWidget::initButtons()
{
	addEffectButton = new QPushButton(HOAEditor::Strings::AddEffectButton);
	addEffectButton->setShortcut(HOAEditor::Shortcuts::AddEffect);
	connect(addEffectButton, &QPushButton::clicked, this, &EffectsListWidget::addEffect);

	removeEffectButton = new QPushButton(HOAEditor::Strings::RemoveEffectButton);
	removeEffectButton->setShortcut(HOAEditor::Shortcuts::RemoveEffect);
	connect(removeEffectButton, &QPushButton::clicked, this, &EffectsListWidget::removeEffect);
}

void EffectsListWidget::initEditors()
{
	effectTypeEdit = new QComboBox;
	for (auto effectType : HOA::EffectTypeLabels.keys())
		effectTypeEdit->addItem(HOA::EffectTypeLabels[effectType], effectType);
	connect(effectTypeEdit, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &EffectsListWidget::updateEffectType);


	for (QSpinBox **spinBox : {&effectMagnitudeEdit, &effectDurationEdit}) {
		*spinBox = new QSpinBox;
		(*spinBox)->setFixedWidth(SPIN_BOX_WIDTH);
	}
	connect(effectMagnitudeEdit, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &EffectsListWidget::updateEffectMagnitude);
	connect(effectDurationEdit, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &EffectsListWidget::updateEffectDuration);
}

void EffectsListWidget::initList()
{
	effectsModel = new QStringListModel(this);
	effectsModel->setStringList(effectsNames);

	effectsListEdit = new QListView;
	effectsListEdit->setModel(effectsModel);

	connect(effectsListEdit, &QListView::activated, this, &EffectsListWidget::updateEditors);
}

void EffectsListWidget::initLayout()
{
	QHBoxLayout *itemEffectsLayout = new QHBoxLayout(this);
	QGroupBox *effectDetails = new QGroupBox(HOAEditor::Strings::EffectDetailsLabel);
	QFormLayout *effectDetailsLayout = new QFormLayout(effectDetails);
	//alignForm(effectDetailsLayout);
	QVBoxLayout *effectsListLayout = new QVBoxLayout;
	QHBoxLayout *buttonsLayout = new QHBoxLayout;

	itemEffectsLayout->addLayout(effectsListLayout);
	itemEffectsLayout->addWidget(effectDetails);

	effectDetailsLayout->addRow(HOA::Strings::ItemEffectType,      effectTypeEdit);
	effectDetailsLayout->addRow(HOA::Strings::ItemEffectMagnitude, effectMagnitudeEdit);
	effectDetailsLayout->addRow(HOA::Strings::ItemEffectDuration,  effectDurationEdit);

	effectsListLayout->addWidget(new QLabel(HOAEditor::Strings::EffectsListLabel));
	effectsListLayout->addWidget(effectsListEdit);
	effectsListLayout->addLayout(buttonsLayout);

	buttonsLayout->addWidget(addEffectButton);
	buttonsLayout->addWidget(removeEffectButton);
	buttonsLayout->addStretch();
}

ItemEditor::ItemEditor() : ContentEditor(HOAEditor::Strings::ItemEditorName)
{
	initModels();
	initEditPart();
	initViewPart();
	initLayout();

	initItemMapper();
	initWeaponMappper();
}

ItemEditor::~ItemEditor()
{
	delete itemMapper;
}

void ItemEditor::clear()
{
	itemModel->reset();
	weaponModel->reset();
}

void ItemEditor::loadFromStream(QDataStream& in)
{
	in >> *itemModel;
	in >> *weaponModel;
}

void ItemEditor::saveToStream(QDataStream& out) const
{
	out << *itemModel;
	out << *weaponModel;
}

bool ItemEditor::isChanged() const
{
	return (itemModel->isChanged() || weaponModel->isChanged());
}

void ItemEditor::modelSaved()
{
	itemModel->setChanged(false);
	weaponModel->setChanged(false);
}

void ItemEditor::initModels()
{
	itemModel = &ItemModel::instance();
	weaponModel = &WeaponModel::instance();
	itemMapper = new QDataWidgetMapper();
}

void ItemEditor::initLayout()
{
	QWidget *placeholder = new QWidget;
	QHBoxLayout *mainLayout = new QHBoxLayout(placeholder);

	mainLayout->addLayout(editLayout);
	mainLayout->addLayout(viewLayout);

	widget_ = placeholder;
}

void ItemEditor::initEditPart()
{
	nameEdit = new QLineEdit;
	typeEdit = new QComboBox;
	for (auto itemType : HOA::ItemTypeLabels.keys())
		typeEdit->addItem(HOA::ItemTypeLabels[itemType], itemType);
	connect(typeEdit, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &ItemEditor::itemTypeChanged);

	QFormLayout *nameAndTypeLayout = new QFormLayout;
	nameAndTypeLayout->addRow(HOAEditor::Strings::ItemNameLabel, nameEdit);
	nameAndTypeLayout->addRow(HOAEditor::Strings::ItemTypeLabel, typeEdit);

	QGroupBox *itemDetails = new QGroupBox(HOAEditor::Strings::ItemDetailsLabel);
	initItemDetails(itemDetails);

	weaponDetails = new QGroupBox(HOAEditor::Strings::WeaponDetailsLabel);
	weaponDetails->setEnabled(false);
	initWeaponDetails(weaponDetails);

	QHBoxLayout *detailsLayout = new QHBoxLayout;
	detailsLayout->addWidget(itemDetails);
	detailsLayout->addWidget(weaponDetails);

	itemEffects = new EffectsListWidget(HOAEditor::Strings::ItemEffectsLabel, itemMapper);

	editLayout = new QVBoxLayout;
	editLayout->addLayout(nameAndTypeLayout);
	editLayout->addLayout(detailsLayout);
	editLayout->addWidget(itemEffects);
}

void ItemEditor::initItemDetails(QGroupBox *groupBox)
{
	QFormLayout *itemDetailsLayout = new QFormLayout(groupBox);

	for (QSpinBox **spinBox : {&weightEdit, &priceEdit, &minStrengthEdit, &minAgilityEdit, &minIntelligenceEdit}) {
		*spinBox = new QSpinBox;
		(*spinBox)->setFixedWidth(SPIN_BOX_WIDTH);
	}

	itemDetailsLayout->addRow(HOA::Strings::ItemWeight,          weightEdit);
	itemDetailsLayout->addRow(HOA::Strings::ItemPrice,           priceEdit);
	itemDetailsLayout->addRow(HOA::Strings::ItemMinStrength,     minStrengthEdit);
	itemDetailsLayout->addRow(HOA::Strings::ItemMinAgility,      minAgilityEdit);
	itemDetailsLayout->addRow(HOA::Strings::ItemMinIntelligence, minIntelligenceEdit);

	alignForm(itemDetailsLayout);
}

void ItemEditor::initWeaponDetails(QGroupBox* groupBox)
{
	QFormLayout *weaponDetailsLayout = new QFormLayout(groupBox);

	alignForm(weaponDetailsLayout);

	weaponTypeEdit = new QComboBox;
	for (auto weaponType : HOA::WeaponTypeLabels.keys())
		weaponTypeEdit->addItem(HOA::WeaponTypeLabels[weaponType], weaponType);

	weaponAttackTypeEdit = new QComboBox;
	for (auto attackType : HOA::AttackTypeLabels.keys())
		weaponAttackTypeEdit->addItem(HOA::AttackTypeLabels[attackType], attackType);

	weaponDetailsLayout->addRow(HOA::Strings::WeaponType,       weaponTypeEdit);
	weaponDetailsLayout->addRow(HOA::Strings::WeaponAttackType, weaponAttackTypeEdit);

	for (QSpinBox **spinBox : {&damageEdit, &hitRatioEdit, &reachEdit, &strengthModifierEdit, &agilityModifierEdit, &intelligenceModifierEdit}) {
		*spinBox = new QSpinBox;
		(*spinBox)->setFixedWidth(SPIN_BOX_WIDTH);
	}

	weaponDetailsLayout->addRow(HOA::Strings::WeaponDamage,               damageEdit);
	weaponDetailsLayout->addRow(HOA::Strings::WeaponReach,                reachEdit);
	weaponDetailsLayout->addRow(HOA::Strings::WeaponHitRatio,             hitRatioEdit);
	weaponDetailsLayout->addRow(HOA::Strings::WeaponStrengthModifier,     strengthModifierEdit);
	weaponDetailsLayout->addRow(HOA::Strings::WeaponAgilityModifier,      agilityModifierEdit);
	weaponDetailsLayout->addRow(HOA::Strings::WeaponIntelligenceModifier, intelligenceModifierEdit);

	alignForm(weaponDetailsLayout);
}

void ItemEditor::initViewPart()
{
	itemsList = new QListView;
	itemsList->setModel(itemModel);
	itemsList->setModelColumn(ItemModel::Name);
	itemsList->setSelectionMode(QAbstractItemView::SingleSelection);

	addItemButton = new QPushButton(HOAEditor::Strings::AddItemButton);
	addItemButton->setShortcut(HOAEditor::Shortcuts::AddItem);
	connect(addItemButton, &QPushButton::clicked, this, &ItemEditor::addItem);

	removeItemButton = new QPushButton(HOAEditor::Strings::RemoveItemButton);
	removeItemButton->setShortcut(HOAEditor::Shortcuts::RemoveItem);
	connect(removeItemButton, &QPushButton::clicked, this, &ItemEditor::removeItem);

	QHBoxLayout *buttonsLayout = new QHBoxLayout;
	buttonsLayout->addWidget(addItemButton);
	buttonsLayout->addWidget(removeItemButton);
	buttonsLayout->addStretch();

	viewLayout = new QVBoxLayout;
	viewLayout->addWidget(itemsList);
	viewLayout->addLayout(buttonsLayout);
}

void ItemEditor::initItemMapper()
{
	itemMapper->setModel(itemModel);
	itemMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

	itemMapper->addMapping(nameEdit,            ItemModel::Name);
	itemMapper->addMapping(typeEdit,            ItemModel::Type, "currentIndex");
	itemMapper->addMapping(weightEdit,          ItemModel::Weight);
	itemMapper->addMapping(priceEdit,           ItemModel::Price);
	itemMapper->addMapping(minStrengthEdit,     ItemModel::MinStrength);
	itemMapper->addMapping(minAgilityEdit,      ItemModel::MinAgility);
	itemMapper->addMapping(minIntelligenceEdit, ItemModel::MinIntelligence);
 	itemMapper->addMapping(itemEffects,         ItemModel::Effects);

	connect(itemsList->selectionModel(), &QItemSelectionModel::currentRowChanged, itemMapper, &QDataWidgetMapper::setCurrentModelIndex);
}

void ItemEditor::initWeaponMappper()
{
	//TODO
}

void ItemEditor::alignForm(QFormLayout* form)
{
	form->setRowWrapPolicy(QFormLayout::DontWrapRows);
	form->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
	form->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
	form->setLabelAlignment(Qt::AlignLeft);
}

void ItemEditor::itemTypeChanged(int index)
{
	QVariant var = typeEdit->itemData(index);
	if (var == QVariant::Invalid)
		return;

	if (var == HOA::ItemType::Weapon) {
		weaponDetails->setEnabled(true);
		return;
		///add/removeWeapon (UID)
	}

	weaponDetails->setEnabled(false);
}

void ItemEditor::addItem()
{
	itemModel->insertRows(itemModel->rowCount(), 1);
	//TODO sprawdz uid i stwórz weapon
	//addWeapon (UID) /ewentualnie
}

void ItemEditor::removeItem()
{
	QModelIndex selected = itemsList->selectionModel()->currentIndex();
	if (!selected.isValid())
		return;

	itemModel->removeRows(selected.row(), 1);
	//TODO sprawdz UID i ewentualnie usun weapon
	///removeWeapon (UID) /ewentualnie
}
