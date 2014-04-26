#ifndef EQUIPMENTCARRIER_H
#define EQUIPMENTCARRIER_H

#include <QtWidgets>
#include "Item.h"

class EquipmentCarrier;

bool moveItem(EquipmentCarrier *lhs, EquipmentCarrier *rhs, Item *item);

class EquipmentCarrier
{
public:
	virtual ~EquipmentCarrier();

	void addItem(Item *item);
	Item * takeItem(const Item *item);
	void removeItem(const Item *item);
	friend bool moveItem(EquipmentCarrier *lhs, EquipmentCarrier *rhs, Item *item);

	friend bool sellItem(EquipmentCarrier *seller, EquipmentCarrier *buyer, Item *item);
	const QVector <Item *> & itemList() const;

	int money() const;
	void setMoney(int money);

private:
	QVector <Item *> items_;
	int money_;

	Item * findItem(const Item *item);
};

#endif // EQUIPMENTCARRIER_H
