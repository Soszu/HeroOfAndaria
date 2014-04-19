#ifndef LOCALMAP_H
#define LOCALMAP_H

#include "System/Map.h"

/**
 * \class LocalMap
 */
class LocalMap : public Map
{
Q_OBJECT;

public:
	LocalMap(int width, int height, Human *player);

	void exitLocation();

signals:
	void locationExited();

private:
	void test();
};

/**
 * \class Location
 */
class Location : public Object
{
public:
	Location(const QString &name, LocalMap *localMap);

	virtual HOA::ObjectType objectType() const;

	QString name() const;

	LocalMap * localMap() const;

private:
	QString name_;

	LocalMap *localMap_;
};

#endif // LOCALMAP_H
