#include "System/Models/CreatureModel.h"

QList <CreatureBase *> CreatureModel::creatures_;
QHash <UID, CreatureBase *> CreatureModel::uidToCreature;

int CreatureModel::columnCount(const QModelIndex &index) const
{
	if (index.isValid())
		return 0;
	return ColumnCount;
}

QVariant CreatureModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		const CreatureBase *creature = creatures_[index.row()];
		switch (index.column()) {
			case Name:             return creature->name();
			case FullHitPoints:    return creature->fullHitPoints();
			case Strength:         return creature->strength();
			case Agility:          return creature->agility();
			case Intelligence:     return creature->intelligence();
			case Endurance:        return creature->endurance();
		}
	}

	return QVariant();
}

QVariant CreatureModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
		return QVariant();

	switch (section) {
		case Name:             return HOA::Strings::CreatureName;
		case FullHitPoints:    return HOA::Strings::CreatureFullHitPoints;
		case Strength:         return HOA::Strings::CreatureStrength;
		case Agility:          return HOA::Strings::CreatureAgility;
		case Intelligence:     return HOA::Strings::CreatureIntellgence;
		case Endurance:        return HOA::Strings::CreatureEndurance;
	}

	return QVariant();
}

Qt::ItemFlags CreatureModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;
	return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

bool CreatureModel::insertRows(int row, int count, const QModelIndex &parent)
{
	int nameSuffix = 0;
	beginInsertRows(QModelIndex(), row, row + count - 1);
	for (int i = 0; i < count; ++i) {
		QString creatureName;
		do {
			++nameSuffix;
			creatureName = QString("%1 %2").arg(HOA::Strings::DefaultNewCreatureName).arg(nameSuffix);
		} while (hasCreature(creatureName));

		creatures_.insert(row + i, new CreatureBase(nextUid++, creatureName));
	}
	endInsertRows();

	return true;
}

bool CreatureModel::removeRows(int row, int count, const QModelIndex &parent)
{
	beginRemoveRows(QModelIndex(), row, row + count - 1);
	for (int i = 0; i < count; ++i)
		removeCreatureFromRow(row);
	endRemoveRows();

	return true;
}

int CreatureModel::rowCount(const QModelIndex &parent) const
{
	return creatures_.count();
}

bool CreatureModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (!index.isValid() || role != Qt::EditRole)
		return false;

	CreatureBase *creature = creatures_[index.row()];
	switch (index.column()) {
		case Name:             creature->setName(value.toString()); break;
		case FullHitPoints:    creature->setFullHitPoints(value.toInt()); break;
		case Strength:         creature->setStrength(value.toInt()); break;
		case Agility:          creature->setAgility(value.toInt()); break;
		case Intelligence:     creature->setIntelligence(value.toInt()); break;
		case Endurance:        creature->setEndurance(value.toInt()); break;
		default:               return false;
	}

	emit dataChanged(index, index);

	return true;
}

void CreatureModel::reset()
{
	removeRows(0, rowCount());
	nextUid = MinUid;
	changed_ = false;
}

bool CreatureModel::isChanged() const
{
	return changed_;
}

void CreatureModel::setChanged(bool changed)
{
	changed_ = changed;
}

CreatureModel & CreatureModel::instance()
{
	static CreatureModel *instance = new CreatureModel;
	return *instance;
}

void CreatureModel::addNewCreature()
{
	instance().insertRows(creatures_.size(), 1);
}

bool CreatureModel::empty()
{
	return creatures_.empty();
}

const CreatureBase * CreatureModel::creatureInRow(int row)
{
	return creatures_[row];
}

const CreatureBase * CreatureModel::creature(UID uid)
{
	return uidToCreature.value(uid, nullptr);
}

const CreatureBase * CreatureModel::creature(const QModelIndex &index)
{
	return creatureInRow(index.row());
}

const CreatureBase * CreatureModel::creature(const QString &name)
{
	for (const CreatureBase * creature : creatures_)
		if (creature->name() == name)
			return creature;

	return nullptr;
}

const QList< CreatureBase *> & CreatureModel::creatures()
{
	return creatures_;
}

bool CreatureModel::hasCreature(const QString &name)
{
	return creature(name) != nullptr;
}

void CreatureModel::removeCreature(UID uid)
{
	CreatureModel &cModel = instance();

	for (int i = 0; i < creatures_.count(); ++i) {
		if (creatures_[i]->uid() == uid) {
			         cModel.beginRemoveRows(QModelIndex(), i, i);
			delete creatures_.takeAt(i);
			         cModel.endRemoveRows();

			uidToCreature.remove(uid);
			return;
		}
	}
}

CreatureModel::CreatureModel(QObject *parent) : QAbstractTableModel(parent), changed_(false), nextUid(MinUid)
{
	auto modelChanged = [this]{
		this->changed_ = true;
	};

	connect(this, &QAbstractTableModel::dataChanged, modelChanged);
	connect(this, &QAbstractTableModel::rowsInserted, modelChanged);
	connect(this, &QAbstractTableModel::rowsMoved, modelChanged);
	connect(this, &QAbstractTableModel::rowsRemoved, modelChanged);
}

CreatureModel::~CreatureModel()
{
	qDeleteAll(creatures_);
}

void CreatureModel::addCreature(int row, CreatureBase* creature)
{
	creatures_.insert(row, creature);
	uidToCreature[creature->uid()] = creature;
}

void CreatureModel::removeCreatureFromRow(int row)
{
	uidToCreature.remove(creatures_[row]->uid());
	delete creatures_.takeAt(row);
}


QDataStream & operator << (QDataStream &out, const CreatureModel &cModel)
{
	out << cModel.nextUid << static_cast<UID>(cModel.creatures_.count());
	for (const CreatureBase *creature : cModel.creatures_)
		out << *creature;
	return out;
}

QDataStream & operator >> (QDataStream &in, CreatureModel &cModel)
{
	cModel.beginResetModel();
	qDeleteAll(cModel.creatures_);
	cModel.creatures_.clear();
	cModel.uidToCreature.clear();

	UID count;
	in >> cModel.nextUid >> count;
	for (UID i = 0; i < count; ++i) {
		CreatureBase *creature = new CreatureBase;
		in >> *creature;
		cModel.addCreature(i, creature);
	}
	cModel.endResetModel();

	return in;
}