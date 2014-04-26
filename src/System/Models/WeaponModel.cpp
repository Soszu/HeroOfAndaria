#include "System/Models/WeaponModel.h"

QList <WeaponBase *> WeaponModel::weapons_;
QHash <UID, WeaponBase *> WeaponModel::uidToWeapon;

int WeaponModel::columnCount(const QModelIndex& index) const
{
	if (index.isValid())
		return 0;
	return ColumnCount;
}

QVariant WeaponModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		const WeaponBase *weapon = weapons_[index.row()];
		switch (index.column()) {
			case Type:                     return weapon->type();
			case AttackType:               return weapon->attackType();
			case Damage:                   return weapon->damage();
			case Reach:                    return weapon->reach();
			case HitRatio:                 return weapon->hitRatio();
			case StrengthModifier:         return weapon->strengthModifier();
			case AgilityModifier:          return weapon->agilityModifier();
			case IntelligenceModifier:     return weapon->intelligenceModifier();
		}
	}

	return QVariant();
}

bool WeaponModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (!index.isValid() || role != Qt::EditRole)
		return false;

	WeaponBase *weapon = weapons_[index.row()];
	switch (index.column()) {
		case Type:                     weapon->setType(static_cast<HOA::WeaponType>(value.toInt())); break;
		case AttackType:               weapon->setAttackType(static_cast<HOA::AttackType>(value.toInt())); break;
		case Damage:                   weapon->setDamage(value.toInt()); break;
		case Reach:                    weapon->setReach(value.toInt()); break;
		case HitRatio:                 weapon->setHitRatio(value.toInt()); break;
		case StrengthModifier:         weapon->setStrengthModifier(value.toInt()); break;
		case AgilityModifier:          weapon->setAgilityModifier(value.toInt()); break;
		case IntelligenceModifier:     weapon->setIntelligenceModifier(value.toInt()); break;
	}

	emit dataChanged(index, index);

	return true;
}

Qt::ItemFlags WeaponModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;
	return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

int WeaponModel::rowCount(const QModelIndex &parent) const
{
	return weapons_.count();
}

void WeaponModel::reset()
{
	beginResetModel();
	changed_ = false;
	qDeleteAll(weapons_);
	weapons_.clear();
	uidToWeapon.clear();
	endResetModel();
}

bool WeaponModel::isChanged() const
{
	return changed_;
}

void WeaponModel::setChanged(bool changed)
{
	changed_ = changed;
}

WeaponModel & WeaponModel::instance()
{
	static WeaponModel *instance = new WeaponModel;
	return *instance;
}

bool WeaponModel::addWeapon(UID uid){
	if (hasWeapon(uid))
		return false;

	int row = weapons_.count();

	instance().beginInsertRows(QModelIndex(), row, row);

	WeaponBase *weapon = new WeaponBase(uid);
	weapons_.insert(row, weapon);
	uidToWeapon[uid] = weapon;

	instance().endInsertRows();
	return true;
}

bool WeaponModel::empty(){
	return weapons_.empty();
}

int WeaponModel::uidToIndex(UID uid)
{
	for (int i = 0; i < weapons_.count();++i)
		if (weapons_[i]->uid() == uid)
			return i;
	return -1;
}

const WeaponBase * WeaponModel::weapon(UID uid)
{
	return uidToWeapon.value(uid, nullptr);
}

const WeaponBase * WeaponModel::weapon(const QModelIndex &index)
{
	return weapons_[index.row()];
}

const WeaponBase * WeaponModel::weapon(const QString &name)
{
	return weapon(ItemModel::item(name)->uid());
}

const QList <WeaponBase *> & WeaponModel::weapons()
{
	return weapons_;
}

bool WeaponModel::hasWeapon(const QString &name)
{
	return weapon(name) != nullptr;
}

bool WeaponModel::hasWeapon(UID uid)
{
	return weapon(uid) != nullptr;
}

bool WeaponModel::removeWeapon(UID uid)
{
	for (int i = 0; i < weapons_.count(); ++i) {
		if (weapons_[i]->uid() == uid) {
			instance().beginRemoveRows(QModelIndex(), i, i);

			delete weapons_.takeAt(i);
			uidToWeapon.remove(uid);

			instance().endRemoveRows();
			return true;
		}
	}
	return false;
}

WeaponModel::WeaponModel(QObject *parent) : QAbstractTableModel(parent), changed_(false)
{
	auto modelChanged = [this]{
		this->changed_ = true;
	};

	connect(this, &QAbstractTableModel::dataChanged, modelChanged);
	connect(this, &QAbstractTableModel::rowsInserted, modelChanged);
	connect(this, &QAbstractTableModel::rowsMoved, modelChanged);
	connect(this, &QAbstractTableModel::rowsRemoved, modelChanged);
}

WeaponModel::~WeaponModel()
{
	qDeleteAll(weapons_);
}

QDataStream & operator << (QDataStream &out, const WeaponModel &wModel)
{
	out << static_cast<UID>(wModel.weapons_.count());
	for (const WeaponBase *weapon : wModel.weapons_)
		out << *weapon;
	return out;
}

QDataStream & operator >> (QDataStream &in, WeaponModel &wModel)
{
	wModel.beginResetModel();
	qDeleteAll(wModel.weapons_);
	wModel.weapons_.clear();
	wModel.uidToWeapon.clear();

	UID count;
	in >> count;
	for (UID i = 0; i < count; ++i) {
		WeaponBase *weapon = new WeaponBase;
		in >> *weapon;
		wModel.weapons_.insert(i, weapon);
		wModel.uidToWeapon[weapon->uid()] = weapon;
	}
	wModel.endResetModel();

	return in;
}