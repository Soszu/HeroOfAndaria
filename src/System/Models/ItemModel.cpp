#include "System/Models/ItemModel.h"

QList <ItemBase *> ItemModel::items_;
QHash <UID, ItemBase *> ItemModel::uidToItem;

int ItemModel::columnCount(const QModelIndex& index) const
{
	if (index.isValid())
		return 0;
	return ColumnCount;
}

QVariant ItemModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		const ItemBase *item = items_[index.row()];
		switch (index.column()) {
			case Name:                return item->name();
			case Type:                return item->type();
			case Weight:              return item->weight();
			case Price:               return item->price();
			case MinStrength:         return item->minStrength();
			case MinAgility:          return item->minAgility();
			case MinIntelligence:     return item->minIntelligence();
			case Effects:             return QVariant::fromValue(item->effects());
		}
	}

	return QVariant();
}

bool ItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (!index.isValid() || role != Qt::EditRole)
		return false;

	ItemBase *item = items_[index.row()];
	switch (index.column()) {
		case Name:                item->setName(value.toString()); break;
		case Type:                item->setType(static_cast<HOA::ItemType>(value.toInt())); break;
		case Weight:              item->setWeight(value.toInt()); break;
		case Price:               item->setPrice(value.toInt()); break;
		case MinStrength:         item->setMinStrength(value.toInt()); break;
		case MinAgility:          item->setMinAgility(value.toInt()); break;
		case MinIntelligence:     item->setMinIntelligence(value.toInt()); break;
		case Effects:             item->setEffects(value.value<QList <HOA::Effect> >()); break;
	}

	emit dataChanged(index, index);

	return true;
}

Qt::ItemFlags ItemModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;
	return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

bool ItemModel::insertRows(int row, int count, const QModelIndex &parent)
{
	int nameSuffix = 0;
	beginInsertRows(QModelIndex(), row, row + count - 1);
	for (int i = 0; i < count; ++i) {
		QString itemName;
		do {
			++nameSuffix;
			itemName = QString("%1 %2").arg(HOA::Strings::DefaultNewItemName).arg(nameSuffix);
		} while (hasItem(itemName));

		items_.insert(row + i, new ItemBase(nextUid++, itemName));
	}
	endInsertRows();

	return true;
}

bool ItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
	beginRemoveRows(QModelIndex(), row, row + count - 1);
	for (int i = 0; i < count; ++i)
		removeItemFromRow(row);
	endRemoveRows();

	return true;
}

int ItemModel::rowCount(const QModelIndex &parent) const
{
	return items_.count();
}

void ItemModel::reset()
{
	removeRows(0, rowCount());
	nextUid = MinUid;
	changed_ = false;
}

bool ItemModel::isChanged() const
{
	return changed_;
}

void ItemModel::setChanged(bool changed)
{
	changed_ = changed;
}

ItemModel & ItemModel::instance()
{
	static ItemModel *instance = new ItemModel;
	return *instance;
}

void ItemModel::addNewItem(){
	instance().insertRows(items_.count(), 1);
}

bool ItemModel::empty(){
	return items_.empty();
}

const ItemBase * ItemModel::itemInRow(int row)
{
	return items_[row];
}

const ItemBase * ItemModel::item(UID uid)
{
	return uidToItem.value(uid, nullptr);
}

const ItemBase * ItemModel::item(const QModelIndex &index)
{
	return items_[index.row()];
}

const ItemBase * ItemModel::item(const QString &name)
{
	for (const ItemBase * item : items_)
		if (item->name() == name)
			return item;

		return nullptr;
}

const QList <ItemBase *> & ItemModel::items()
{
	return items_;
}

bool ItemModel::hasItem(const QString &name)
{
	return item(name) != nullptr;
}

void ItemModel::removeItem(UID uid)
{
	ItemModel &iModel = instance();

	for (int i = 0; i < items_.count(); ++i) {
		if (items_[i]->uid() == uid) {
			         iModel.beginRemoveRows(QModelIndex(), i, i);
			delete items_.takeAt(i);
			         iModel.endRemoveRows();

			uidToItem.remove(uid);
			return;
		}
	}
}

ItemModel::ItemModel(QObject *parent) : QAbstractTableModel(parent), changed_(false), nextUid(MinUid)
{
	auto modelChanged = [this]{
		this->changed_ = true;
	};

	connect(this, &QAbstractTableModel::dataChanged, modelChanged);
	connect(this, &QAbstractTableModel::rowsInserted, modelChanged);
	connect(this, &QAbstractTableModel::rowsMoved, modelChanged);
	connect(this, &QAbstractTableModel::rowsRemoved, modelChanged);
}

ItemModel::~ItemModel()
{
	qDeleteAll(items_);
}

void ItemModel::addItem(int row, ItemBase* item)
{
	items_.insert(row, item);
	uidToItem[item->uid()] = item;
}

void ItemModel::removeItemFromRow(int row)
{
	uidToItem.remove(items_[row]->uid());
	delete items_.takeAt(row);
}


QDataStream & operator << (QDataStream &out, const ItemModel &iModel)
{
	out << iModel.nextUid << static_cast<UID>(iModel.items_.count());
	for (const ItemBase *item : iModel.items_)
		out << *item;
	return out;
}

QDataStream & operator >> (QDataStream &in, ItemModel &iModel)
{
	iModel.beginResetModel();
	qDeleteAll(iModel.items_);
	iModel.items_.clear();
	iModel.uidToItem.clear();

	UID count;
	in >> iModel.nextUid >> count;
	for (UID i = 0; i < count; ++i) {
		ItemBase *item = new ItemBase;
		in >> *item;
		iModel.addItem(i, item);
	}
	iModel.endResetModel();

	return in;
}