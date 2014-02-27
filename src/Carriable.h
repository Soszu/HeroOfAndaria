#ifndef CARRIABLE_H
#define CARRIABLE_H

class Carriable
{
public:
	Carriable(int weight);
	
	int weight() const;
	int price() const;
	
private:
	int weight_;
	int price_;
};

#endif // CARRIABLE_H
