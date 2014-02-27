#ifndef ITEM_H
#define ITEM_H

#include <QtCore>
#include "Carriable.h"
#include "Movable.h"

class Item : public Carriable, public Movable
{
public:
	Item(int type);

	QString name() const;

private:
	int type_;
};

#endif // ITEM_H
