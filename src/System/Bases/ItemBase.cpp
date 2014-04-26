#include "System/Bases/ItemBase.h"

/**
 * \struct HOA::Effect
 */

bool HOA::Effect::operator==(const Effect &effect) const
{
	return this->type      == effect.type
	    && this->duration  == effect.duration
	    && this->magnitude == effect.magnitude;
}

QString HOA::Effect::description()
{
	return HOA::EffectTypeLabels[type] + QString(" ") + QString::number(magnitude);
}

QDataStream & operator<<(QDataStream &out, const HOA::Effect &effect)
{
	out << static_cast<quint16>(effect.type) << effect.duration << effect.magnitude;
	return out;
}

QDataStream & operator>>(QDataStream &in, HOA::Effect &effect)
{
	quint16 typeV;
	in >> typeV >> effect.duration >> effect.magnitude;
	effect.type = static_cast<HOA::EffectType>(typeV);
	return in;
}

/**
 * \class ItemBase
 */

ItemBase::ItemBase() : ItemBase(MinUid, QString())
{}

ItemBase::ItemBase(UID uid, const QString &name) :
	uid_(uid),
	name_(name),
	type_(HOA::ItemType::Armor), //weapon as default type is not recommended
	weight_(0),
	price_(0),
	minStrength_(0),
	minAgility_(0),
	minIntelligence_(0)
{}

UID ItemBase::uid() const
{
	return uid_;
}

QString ItemBase::name() const
{
	return name_;
}

void ItemBase::setName(const QString& name)
{
	name_ = name;
}

HOA::ItemType ItemBase::type() const
{
	return type_;
}

void ItemBase::setType(HOA::ItemType type)
{
	type_ = type;
}

int ItemBase::weight() const
{
	return weight_;
}

void ItemBase::setWeight(int weight)
{
	weight_ = weight;
}

int ItemBase::price() const
{
	return price_;
}

void ItemBase::setPrice(int price)
{
	price_ = price;
}

QList <HOA::Effect> ItemBase::effects() const
{
	return effects_;
}

void ItemBase::setEffects(QList <HOA::Effect> effects)
{
	effects_ = effects;
}

int ItemBase::minStrength() const
{
	return minStrength_;
}

void ItemBase::setMinStrength(int strength)
{
	minStrength_ = strength;
}

int ItemBase::minAgility() const
{
	return minAgility_;
}

void ItemBase::setMinAgility(int agility)
{
	minAgility_ = agility;
}

int ItemBase::minIntelligence() const
{
	return minIntelligence_;
}

void ItemBase::setMinIntelligence(int intelligence)
{
	minIntelligence_ = intelligence;
}

QDataStream & operator << (QDataStream &out, const ItemBase &item)
{
	out << item.uid() << item.name();
// 	out << item.type();
	out << item.weight() << item.price();
	out << item.minStrength() << item.minAgility() << item.minIntelligence();
// 	out << item.effects();

	return out;
}

QDataStream & operator >> (QDataStream &in, ItemBase &item)
{
	in >> item.uid_ >> item.name_;
// 	in >> item.type_;
	in >> item.weight_ >> item.price_;
	in >> item.minStrength_ >> item.minAgility_ >> item.minIntelligence_;
// 	in >> item.effects_;

	return in;
}