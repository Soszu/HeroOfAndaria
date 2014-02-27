#ifndef ITEM_H
#define ITEM_H

class Item : public Carriable, public Movable
{
public:
	Item();
	
	QString name() const;
	
private:
	int type_;
};

#endif // ITEM_H
