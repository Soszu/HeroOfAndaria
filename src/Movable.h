#ifndef MOVABLE_H
#define MOVABLE_H

#include <QtCore>
#include "Object.h"

namespace HOA {
	enum class Direction {
		Front      = 0,
		RightFront = 1,
		RightRear  = 2,
		Rear       = 3,
		LeftRear   = 4,
		LeftFront  = 5,
	};
}

class Movable : public Object
{
public:
	Movable();

	QPoint speed() const;
	virtual int maxSpeed() const = 0;

	void move(HOA::Direction direction);
	void stop();

private:
	QPoint speed_;

	void advance();
};

#endif // MOVABLE_H
