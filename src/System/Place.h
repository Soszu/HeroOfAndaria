#ifndef PLACE_H
#define PLACE_H

#include <QtCore>

namespace HOA {
	enum class PlaceType {
		Inn,
		Blacksmith,
	};
}

class Place
{
public:
	Place(const QString &name);

	virtual HOA::PlaceType type() const = 0;
	QString name() const;

private:
	QString name_;
};

#endif // PLACE_H
