#ifndef GLOBALMAP_H
#define GLOBALMAP_H

#include <QtCore>
#include "System/Map.h"
#include "System/Town.h"

class GlobalMap : public Map
{
public:
	GlobalMap(int width, int height);

	QVector <Town *> towns() const;
};

#endif // GLOBALMAP_H
