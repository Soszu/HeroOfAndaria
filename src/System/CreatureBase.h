#ifndef CREATUREBASE_H
#define CREATUREBASE_H

#include <QtWidgets>
#include "System/FileIO.h"
#include "System/Uid.h"
#include "System/CommonStrings.h"

/* ---------------  CreatureBase class -------------------------- */

class CreatureBase
{

public:
	CreatureBase();
	CreatureBase(UID uid, const QString &name);
	CreatureBase(const CreatureBase &creature);
	CreatureBase(const QString &name,
	             int fullHitPoints,
	             int strength,
	             int agility,
	             int intelligence,
	             int endurance);

	UID uid() const;

	QString name() const;
	void setName(const QString &name);

	int fullHitPoints() const;
	void setFullHitPoints(int fullHitPoints);

	int strength() const;
	void setStrength(int strength);
	int agility() const;
	void setAgility(int agility);
	int intelligence() const;
	void setIntelligence(int intelligence);
	int endurance() const;
	void setEndurance(int endurance);

	friend QDataStream & operator << (QDataStream &out, const CreatureBase &creature);
	friend QDataStream & operator >> (QDataStream &in, CreatureBase &creature);

private:
	UID uid_;

	QString name_;

	int fullHitPoints_;

	int strength_;
	int agility_;
	int intelligence_;
	int endurance_;
};

/* ---------------  CreatureModel class -------------------------- */

class CreatureModel : public QAbstractTableModel
{
Q_OBJECT;

public:
	int columnCount(const QModelIndex &index = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
	bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

	bool isChanged() const;
	void setChanged(bool changed);

	static CreatureModel & instance();
	static bool loadFromFile(const QString &fileName);
	static bool saveToFile(const QString &fileName);

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
	friend bool ::saveToFile<CreatureModel>(CreatureModel &obj, const QString &fileName);

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

#endif // CREATUREBASE_H
