#ifndef CARRIABLE_H
#define CARRIABLE_H

class Carriable
{
public:
	Carriable();

	virtual int weight() const = 0;
	virtual int price()  const = 0;
};

#endif // CARRIABLE_H
