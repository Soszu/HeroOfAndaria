#ifndef WEAPONMODEL_H
#define WEAPONMODEL_H

#include <QtWidgets>
#include "System/Uid.h"
#include "System/CommonStrings.h"
#include "System/Bases/WeaponBase.h"

class WeaponBase;

class WeaponModel : public QAbstractTableModel
{
	Q_OBJECT;

public:
	int columnCount(const QModelIndex &index = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
	bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	void reset();

	bool isChanged() const;
	void setChanged(bool changed);

	static WeaponModel & instance();

	static void addNewWeapon();
	static bool empty();
	static const WeaponBase * weaponInRow(int row);
	static const WeaponBase * weapon(UID uid);
	static const WeaponBase * weapon(const QModelIndex &index);
	static const WeaponBase * weapon(const QString &name);
	static const QList <WeaponBase *> & weapons();
	static bool hasWeapon(const QString &name);
	static void removeWeapon(UID uid);

	static const int Name                    = 0;
	static const int Type                    = 1;
	static const int AttackType              = 2;
	static const int Damage                  = 3;
	static const int HitRatio                = 4;
	static const int Reach                   = 5;
	static const int StrengthModifier        = 6;
	static const int AgilityModifier         = 7;
	static const int IntelligenceModifier    = 8;
	static const int ColumnCount             = 9;

	friend QDataStream & operator << (QDataStream &out, const WeaponModel &wModel);
	friend QDataStream & operator >> (QDataStream &in, WeaponModel &wModel);

private:
	explicit WeaponModel(QObject *parent = nullptr);
	WeaponModel(const WeaponModel &) = delete;
	WeaponModel(WeaponModel &&) = delete;
	void operator=(const WeaponModel &) = delete;
	void operator=(WeaponModel &&) = delete;
	~WeaponModel();

	void addWeapon(int row, WeaponBase *weapon);
	void removeWeaponFromRow(int row);

	bool changed_;
	UID nextUid;

	static const UID MinUid = 1;
	static QList <WeaponBase *> weapons_;
	static QHash <UID, WeaponBase *> uidToWeapon;
};

#endif // WEAPONMODEL_H
