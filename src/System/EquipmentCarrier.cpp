#include "System/EquipmentCarrier.h"

EquipmentCarrier::~EquipmentCarrier()
{}

void EquipmentCarrier::addItem(Item *item)
{
	items_.append(item);
}

Item * EquipmentCarrier::takeItem(const Item *item)
{
	Item *sought = findItem(item);
	removeItem(item);
	return sought;
}

void EquipmentCarrier::removeItem(const Item *item)
{
	items_.remove(items_.indexOf(findItem(item)));
}

bool moveItem(EquipmentCarrier *lhs, EquipmentCarrier *rhs, Item *item)
{
	rhs->addItem(lhs->takeItem(item));
	return true;
}

bool sellItem(EquipmentCarrier *seller, EquipmentCarrier *buyer, Item *item)
{
	if (buyer->money() >= item->price()) {
		seller->money_ += item->price();
		buyer->money_ -= item->price();
		moveItem(seller, buyer, item);
		return true;
	} else {
		return false;
	}
}

const QVector <Item *> & EquipmentCarrier::itemList() const
{
	return items_;
}

int EquipmentCarrier::money() const
{
	return money_;
}

void EquipmentCarrier::setMoney(int money)
{
	money_ = money;
}

Item * EquipmentCarrier::findItem(const Item *item)
{
	for (Item *it : items_)
		if (it == item)
			return it;
	return nullptr;
}
