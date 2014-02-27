#ifndef MAP_H
#define MAP_H

class Map : public Grid
{
public:
	Map();
	
protected:
	QVector <Object *> objects_;
};

#endif // MAP_H
