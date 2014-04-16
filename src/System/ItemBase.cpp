#include "ItemBase.h"

ItemBase::ItemBase()
{

}

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

HOA::Effect ItemBase::effect() const
{
	return effect_;
}

void ItemBase::setEffect(HOA::Effect effect)
{
	effect_ = effect;
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
	return out;
}

QDataStream & operator >> (QDataStream &in, ItemBase &item)
{
	return in;
}
