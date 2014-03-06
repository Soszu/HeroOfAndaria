#ifndef ITEM_H
#define ITEM_H

#include <QtCore>
#include "System/Carriable.h"
#include "System/ItemBase.h"
#include "System/Movable.h"

class Item : public Carriable, public Movable
{
public:
	Item(int type);

private:
	ItemBase *base_;
};

#endif // ITEM_H
