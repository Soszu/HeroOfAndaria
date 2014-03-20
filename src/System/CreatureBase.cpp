#include "System/CreatureBase.h"

/* ---------------  CreatureBase class -------------------------- */

CreatureBase::CreatureBase() : uid_(EmptyUid), name_(QString()), fullHitPoints_(0),
                             strength_(0), agility_(0), intelligence_(0), endurance_(0)
{}

CreatureBase::CreatureBase(UID uid, const QString &name)
                           : uid_(uid), name_(name), fullHitPoints_(0),
                           strength_(0), agility_(0), intelligence_(0), endurance_(0)
{}

CreatureBase::CreatureBase(const CreatureBase &creature)
                           : name_(creature.name()), fullHitPoints_(creature.fullHitPoints()),
                           strength_(strength()), agility_(agility()),
                           intelligence_(creature.intelligence()), endurance_(endurance())
{}

CreatureBase::CreatureBase(const QString &name, int fullHitPoints, int strength,
			   int agility, int intelligence, int endurance)
                           : name_(name), fullHitPoints_(fullHitPoints), strength_(strength),
                           agility_(agility), intelligence_(intelligence), endurance_(endurance)
{}

UID CreatureBase::uid() const
{
	return uid_;
}

QString CreatureBase::name() const
{
	return name_;
}

void CreatureBase::setName(const QString& name)
{
	name_ = name;
}

int CreatureBase::fullHitPoints() const
{
	return fullHitPoints_;
}

void CreatureBase::setFullHitPoints(int fullHitPoints)
{
	fullHitPoints_ = fullHitPoints;
}

int CreatureBase::strength() const
{
	return strength_;
}

void CreatureBase::setStrength(int strength)
{
	strength_ = strength;
}

int CreatureBase::agility() const
{
	return agility_;
}

void CreatureBase::setAgility(int agility)
{
	agility_ = agility;
}

int CreatureBase::intelligence() const
{
	return endurance_;
}

void CreatureBase::setIntelligence(int intelligence)
{
	intelligence_ = intelligence;
}

int CreatureBase::endurance() const
{
	return endurance_;
}

void CreatureBase::setEndurance(int endurance)
{
	endurance_ = endurance;
}

QDataStream & operator << (QDataStream &out, const CreatureBase &creature)
{
	out << creature.name_ << "(" << creature.uid_ << ")"
	<< "\nstats:"
	<< "\n\tfull hit points:    " << creature.fullHitPoints_
	<< "\n\tstrength:           " << creature.strength_
	<< "\n\tagility:            " << creature.agility_
	<< "\n\tintelligence:       " << creature.intelligence_
	<< "\n\tendurance:          " << creature.endurance_;

	return out;
}

QDataStream & operator >> (QDataStream &in, CreatureBase &creature)
{
	in >> creature.name_ >> creature.uid_;
	in >> creature.fullHitPoints_;
	in >> creature.strength_ >> creature.agility_ >> creature.intelligence_ >> creature.endurance_;

	return in;
}

/* ---------------  CreatureModel class -------------------------- */

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

Qt::ItemFlags CreatureModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;
	return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable;
}

bool CreatureModel::insertRows(int row, int count, const QModelIndex &parent)
{
	int nameSuffix = 0;
	beginInsertRows(QModelIndex(), row, row + count - 1);
	for (int i = 0; i < count; ++i) {
		QString creatureName;
		do {
			++nameSuffix;
			creatureName = QString("%1 %2").arg(Strings::DefaultNewCreatureName).arg(nameSuffix);
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

bool CreatureModel::loadFromFile(const QString &fileName)
{
	return ::loadFromFile(instance(), fileName);
}

bool CreatureModel::saveToFile(const QString &fileName)
{
	return ::saveToFile(instance(), fileName);
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


QDataStream & operator << (QDataStream& out, const CreatureModel &cModel)
{
	out << cModel.nextUid << static_cast<UID>(cModel.creatures_.count());
	for (const CreatureBase *creature : cModel.creatures_)
		out << *creature;
	return out;
}

QDataStream & operator >> (QDataStream& in, CreatureModel &cModel)
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