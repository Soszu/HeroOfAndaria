/*
 * operators <<, >>
 * constructors
 * model
 */

#ifndef ITEMMODEL_H
#define ITEMMODEL_H

#include <QtWidgets>
#include "System/Bases/ItemBase.h"
#include "System/CommonStrings.h"
#include "System/Utils/Uid.h"

class ItemBase;

class ItemModel : public QAbstractTableModel
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

	static ItemModel & instance();

	static void addNewItem();
	static bool empty();
	static const ItemBase * itemInRow(int row);
	static const ItemBase * item(UID uid);
	static const ItemBase * item(const QModelIndex &index);
	static const ItemBase * item(const QString &name);
	static const QList <ItemBase *> & items();
	static bool hasItem(const QString &name);
	static void removeItem(UID uid);

	static const int Name              = 0;
	static const int Type              = 1;
	static const int Weight            = 2;
	static const int Price             = 3;
	static const int MinStrength       = 4;
	static const int MinAgility        = 5;
	static const int MinIntelligence   = 6;
	static const int Effects           = 7;
	static const int ColumnCount       = 8;

	friend QDataStream & operator << (QDataStream &out, const ItemModel &wModel);
	friend QDataStream & operator >> (QDataStream &in, ItemModel &wModel);

private:
	explicit ItemModel(QObject *parent = nullptr);
	ItemModel(const ItemModel &) = delete;
	ItemModel(ItemModel &&) = delete;
	void operator=(const ItemModel &) = delete;
	void operator=(ItemModel &&) = delete;
	~ItemModel();

	void addItem(int row, ItemBase *item);
	void removeItemFromRow(int row);

	bool changed_;
	UID nextUid;

	static const UID MinUid = 1;
	static QList <ItemBase *> items_;
	static QHash <UID, ItemBase *> uidToItem;
};

#endif // ITEMMODEL_H
