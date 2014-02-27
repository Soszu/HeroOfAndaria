#ifndef TOWN_H
#define TOWN_H

class Town :  Object
{
public:
	Town();
	
	const QVector <Place *> & places() const;
	
private:
	QVector <Place *> places_;
};

#endif // TOWN_H
