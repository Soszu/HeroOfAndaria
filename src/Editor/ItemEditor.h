//TODO enable, weponmapper, addnewWeapon

#ifndef ITEMEDITOR_H
#define ITEMEDITOR_H

#include <QtWidgets>
#include <QDebug>
#include "Editor/ContentEditor.h"
#include "Editor/Strings.h"
#include "System/CommonStrings.h"
#include "System/Bases/ItemBase.h"
#include "System/Bases/WeaponBase.h"

class EffectsListWidget : public QGroupBox
{
	Q_OBJECT
	Q_PROPERTY(QList <HOA::Effect> effects_ READ effects WRITE setEffects USER true)
public:
	EffectsListWidget(const QString& title, QDataWidgetMapper* mapper, QWidget* parent = 0);

	QList <HOA::Effect> effects() const;
	void setEffects(QList <HOA::Effect> effects);

private slots:
	void addEffect();
	void removeEffect();
	void updateEditors(const QModelIndex &index);

	void updateEffectType(int i);
	void updateEffectMagnitude(int i);
	void updateEffectDuration(int i);

private:
	static const int SPIN_BOX_WIDTH = 50;

	void initButtons();
	void initEditors();
	void initList();
	void initLayout();

	QDataWidgetMapper* mapper_;

	QList <HOA::Effect> effects_;
	QStringList effectsNames;
	QStringListModel *effectsModel;

	QListView *effectsListEdit;
	QComboBox *effectTypeEdit;
	QSpinBox *effectMagnitudeEdit;
	QSpinBox *effectDurationEdit;

	QPushButton *addEffectButton;
	QPushButton *removeEffectButton;
};

class ItemEditor : public ContentEditor
{
    Q_OBJECT

public:
	ItemEditor();
	void clear();
	void loadFromStream(QDataStream& in);
	void saveToStream(QDataStream& out) const;
	bool isChanged() const;

public slots:
	void modelSaved();

private:
	static const int SPIN_BOX_WIDTH = 50;

	void initModels();
	void initEditPart();
	void initItemDetails(QGroupBox *groupBox);
	void initWeaponDetails(QGroupBox *groupBox);
	void initViewPart();
	void initLayout();
	void initMappers();

	void alignForm(QFormLayout *form);

	QVBoxLayout *editLayout;
	QVBoxLayout *viewLayout;

	ItemModel *itemModel;
	QDataWidgetMapper *itemMapper;
	QDataWidgetMapper *weaponMapper;
	WeaponModel *weaponModel;
	bool weaponsMapped;

	//--- Item name ---
	QLineEdit *nameEdit;

	//--- Item type ---
	QComboBox *typeEdit;

	//--- Item details ---
	QSpinBox *weightEdit;
	QSpinBox *priceEdit;
	QSpinBox *minStrengthEdit;
	QSpinBox *minAgilityEdit;
	QSpinBox *minIntelligenceEdit;

	//--- Weapon details ---
	QGroupBox *weaponDetails;

	QComboBox *weaponTypeEdit;
	QComboBox *weaponAttackTypeEdit;

	QSpinBox *damageEdit;
	QSpinBox *hitRatioEdit;
	QSpinBox *reachEdit;
	QSpinBox *strengthModifierEdit;
	QSpinBox *agilityModifierEdit;
	QSpinBox *intelligenceModifierEdit;

	//--- Item effects ---
	EffectsListWidget *itemEffects;

	//--- Item list---
	QListView *itemsList;
	QPushButton *addItemButton;
	QPushButton *removeItemButton;

private slots:
	void itemTypeChanged(int index);
	void adjustWeaponMapper(int index);

	void addItem();
	void removeItem();
};

#endif // ITEMEDITOR_H
