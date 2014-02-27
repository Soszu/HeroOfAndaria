#ifndef ITEM_H
#define ITEM_H

#include <QtCore>
#include "System/Carriable.h"
#include "System/Movable.h"

class Item : public Carriable, public Movable
{
public:
	Item(int type);

	QString name() const;

private:
	int type_;
};

#endif // ITEM_H
