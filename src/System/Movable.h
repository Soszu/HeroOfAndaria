#ifndef MOVABLE_H
#define MOVABLE_H

#include <QtCore>
#include "System/Object.h"

namespace HOA {
	enum class Direction {
		Front      = 0,
		LeftFront  = 1,
		Left       = 2,
		LeftRear   = 3,
		Rear       = 4,
		RightRear  = 5,
		Right      = 6,
		RightFront = 7
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

	void advance(double dt);
};

#endif // MOVABLE_H
