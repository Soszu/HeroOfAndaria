#include "System/Item.h"

Item::Item(const ItemBase *base) : base_(base)
{}

Item::Item(const QString& name) : base_(ItemModel::item(name))
{}

Item::Item(UID uid) : base_(ItemModel::item(uid))
{}

HOA::ObjectType Item::objectType() const
{
	return HOA::ObjectType::Item;
}

void Item::setBase(const ItemBase *base)
{
	base_ = base;
}

UID Item::uid() const
{
	return base_->uid();
}

QString Item::name() const
{
	return base_->name();
}

HOA::ItemType Item::type() const
{
	return base_->type();
}

int Item::weight() const
{
	return base_->weight();
}

int Item::price() const
{
	return base_->price();
}

int Item::minStrength() const
{
	return base_->minStrength();
}

int Item::minAgility() const
{
	return base_->minAgility();
}

int Item::minIntelligence() const
{
	return base_->minIntelligence();
}

QList< HOA::Effect > Item::effects() const
{
	return base_->effects();
}

QDataStream& operator<<(QDataStream &out, const Item &item)
{
	out << item.uid();
	return out;
}

QDataStream& operator>>(QDataStream &in, Item &item)
{
	UID uid;
	in >> uid;
	item.setBase(ItemModel::item(uid));
	return in;

}
