#ifndef CREATUREMODEL_H
#define CREATUREMODEL_H

#include <QtWidgets>
#include "System/Uid.h"
#include "System/CommonStrings.h"
#include "System/Bases/CreatureBase.h"

class CreatureBase;

class CreatureModel : public QAbstractTableModel
{
Q_OBJECT;

public:
	int columnCount(const QModelIndex &index = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
	bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	void reset();

	bool isChanged() const;
	void setChanged(bool changed);

	static CreatureModel & instance();

	static void addNewCreature();
	static bool empty();
	static const CreatureBase * creatureInRow(int row);
	static const CreatureBase * creature(UID uid);
	static const CreatureBase * creature(const QModelIndex &index);
	static const CreatureBase * creature(const QString &name);
	static const QList <CreatureBase *> & creatures();
	static bool hasCreature(const QString &name);
	static void removeCreature(UID uid);

	static const int Name                 = 0;
	static const int FullHitPoints        = 1;
	static const int Strength             = 2;
	static const int Agility              = 3;
	static const int Intelligence         = 4;
	static const int Endurance            = 5;
	static const int ColumnCount          = 6;

	friend QDataStream & operator << (QDataStream &out, const CreatureModel &cModel);
	friend QDataStream & operator >> (QDataStream &in, CreatureModel &cModel);

private:
	explicit CreatureModel(QObject *parent = nullptr);
	CreatureModel(const CreatureModel &) = delete;
	CreatureModel(CreatureModel &&) = delete;
	void operator=(const CreatureModel &) = delete;
	void operator=(CreatureModel &&) = delete;
	~CreatureModel();

	void addCreature(int row, CreatureBase *creature);
	void removeCreatureFromRow(int row);

	bool changed_;
	UID nextUid;

	static const UID MinUid = 1;
	static QList <CreatureBase *> creatures_;
	static QHash <UID, CreatureBase *> uidToCreature;
};

#endif // CREATUREMODEL_H
