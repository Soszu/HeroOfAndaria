#ifndef WEAPONMODEL_H
#define WEAPONMODEL_H

#include <QtWidgets>
#include "System/Bases/WeaponBase.h"
#include "System/CommonStrings.h"
#include "System/Models/ItemModel.h"
#include "System/Utils/Uid.h"

class WeaponBase;

class WeaponModel : public QAbstractTableModel
{
	Q_OBJECT;

public:
	int columnCount(const QModelIndex &index = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	Qt::ItemFlags flags(const QModelIndex &index) const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	void reset();

	bool isChanged() const;
	void setChanged(bool changed);

	static WeaponModel & instance();

	static bool addWeapon(UID uid);
	static bool empty();
	static int uidToIndex(UID uid);
	static const WeaponBase * weapon(UID uid);
	static const WeaponBase * weapon(const QModelIndex &index);
	static const WeaponBase * weapon(const QString &name);
	static const QList <WeaponBase *> & weapons();
	static bool hasWeapon(const QString &name);
	static bool hasWeapon(UID uid);
	static bool removeWeapon(UID uid);

	static const int Type                    = 0;
	static const int AttackType              = 1;
	static const int Damage                  = 2;
	static const int HitRatio                = 3;
	static const int Reach                   = 4;
	static const int StrengthModifier        = 5;
	static const int AgilityModifier         = 6;
	static const int IntelligenceModifier    = 7;
	static const int ColumnCount             = 8;

	friend QDataStream & operator << (QDataStream &out, const WeaponModel &wModel);
	friend QDataStream & operator >> (QDataStream &in, WeaponModel &wModel);

private:
	explicit WeaponModel(QObject *parent = nullptr);
	WeaponModel(const WeaponModel &) = delete;
	WeaponModel(WeaponModel &&) = delete;
	void operator=(const WeaponModel &) = delete;
	void operator=(WeaponModel &&) = delete;
	~WeaponModel();

	bool changed_;

	static QList <WeaponBase *> weapons_;
	static QHash <UID, WeaponBase *> uidToWeapon;
};

#endif // WEAPONMODEL_H
