#include "System/EquipmentCarrier.h"

EquipmentCarrier::EquipmentCarrier()
{

}
/**
 * Only written to be compileable
 */
void EquipmentCarrier::addItem(Item* item)
{

}

const QVector< Item* >& EquipmentCarrier::itemList() const
{
	return this->items_;
}
int EquipmentCarrier::money() const
{
	return this->money_;
}
void EquipmentCarrier::removeItem(const Item* item)
{

}
void EquipmentCarrier::setMoney(int money)
{

}
Item* EquipmentCarrier::takeItem(const Item* item)
{
	return NULL;
}
