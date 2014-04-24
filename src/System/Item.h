#ifndef ITEM_H
#define ITEM_H

#include <QtCore>
#include "System/Carriable.h"
#include "System/Movable.h"
#include "System/Bases/ItemBase.h"

class Item : public Carriable, public Movable
{
public:
	Item(const ItemBase *base = nullptr);

	virtual HOA::ObjectType objectType() const;

	void setBase(const ItemBase *base);

	UID uid() const;
	QString name() const;

	HOA::ItemType type() const;

	int weight() const;
	int price() const;

	int minStrength() const;
	int minAgility() const;
	int minIntelligence() const;

	QList <HOA::Effect> effects() const;

	friend QDataStream & operator << (QDataStream &out, const Item &item);
	friend QDataStream & operator >> (QDataStream &in, Item &item);

private:
	const ItemBase *base_;
};

#endif // ITEM_H
