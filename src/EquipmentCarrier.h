#ifndef EQUIPMENTCARRIER_H
#define EQUIPMENTCARRIER_H

class EquipmentCarrier
{
public:
	EquipmentCarrier();
	
	void addItem(Item *item);
	Item * takeItem(const Item *item);
	void removeItem(const Item *item);
	friend void moveItem(EquipmentCarrier *lhs, EquipmentCarrier *rhs, Item *item);
	
	const QVector <Item *> & itemList() const;
	
	int money() const;
	void setMoney(int money);
	
private:
	QVector <Item *> items_;
	int money_;
};

#endif // EQUIPMENTCARRIER_H
