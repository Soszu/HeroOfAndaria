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
			case Name:                     return weapon->name();
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
		case Name:                     weapon->setName(value.toString()); break;
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

bool WeaponModel::insertRows(int row, int count, const QModelIndex &parent)
{
	int nameSuffix = 0;
	beginInsertRows(QModelIndex(), row, row + count - 1);
	for (int i = 0; i < count; ++i) {
		QString weaponName;
		do {
			++nameSuffix;
			weaponName = QString("%1 %2").arg(HOA::Strings::DefaultNewWeaponName).arg(nameSuffix);
		} while (hasWeapon(weaponName));

		weapons_.insert(row + i, new WeaponBase(nextUid++, weaponName));
	}
	endInsertRows();

	return true;
}

bool WeaponModel::removeRows(int row, int count, const QModelIndex &parent)
{
	beginRemoveRows(QModelIndex(), row, row + count - 1);
	for (int i = 0; i < count; ++i)
		removeWeaponFromRow(row);
	endRemoveRows();

	return true;
}

int WeaponModel::rowCount(const QModelIndex &parent) const
{
	return weapons_.count();
}

void WeaponModel::reset()
{
	removeRows(0, rowCount());
	nextUid = MinUid;
	changed_ = false;
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

void WeaponModel::addNewWeapon(){
	instance().insertRows(weapons_.count(), 1);
}

bool WeaponModel::empty(){
	return weapons_.empty();
}

const WeaponBase * WeaponModel::weaponInRow(int row)
{
	return weapons_[row];
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
	for (const WeaponBase * weapon : weapons_)
		if (weapon->name() == name)
			return weapon;

		return nullptr;
}

const QList <WeaponBase *> & WeaponModel::weapons()
{
	return weapons_;
}

bool WeaponModel::hasWeapon(const QString &name)
{
	return weapon(name) != nullptr;
}

void WeaponModel::removeWeapon(UID uid)
{
	WeaponModel &wModel = instance();

	for (int i = 0; i < weapons_.count(); ++i) {
		if (weapons_[i]->uid() == uid) {
			wModel.beginRemoveRows(QModelIndex(), i, i);
			delete weapons_.takeAt(i);
			wModel.endRemoveRows();

			uidToWeapon.remove(uid);
			return;
		}
	}
}

WeaponModel::WeaponModel(QObject *parent) : QAbstractTableModel(parent), changed_(false), nextUid(MinUid)
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

void WeaponModel::addWeapon(int row, WeaponBase* weapon)
{
	weapons_.insert(row, weapon);
	uidToWeapon[weapon->uid()] = weapon;
}

void WeaponModel::removeWeaponFromRow(int row)
{
	uidToWeapon.remove(weapons_[row]->uid());
	delete weapons_.takeAt(row);
}

QDataStream & operator << (QDataStream &out, const WeaponModel &wModel)
{
	out << wModel.nextUid << static_cast<UID>(wModel.weapons_.count());
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
	in >> wModel.nextUid >> count;
	for (UID i = 0; i < count; ++i) {
		WeaponBase *weapon = new WeaponBase;
 		in >> *weapon;
		wModel.addWeapon(i, weapon);
	}
	wModel.endResetModel();

	return in;
}