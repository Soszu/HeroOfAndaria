#ifndef MOVABLE_H
#define MOVABLE_H

#include <QtCore>
#include "System/Object.h"

namespace HOA {
	/** Numbers are important */
	enum class Direction : quint8 {
		Front      = 0,
		LeftFront  = 1,
		Left       = 2,
		LeftRear   = 3,
		Rear       = 4,
		RightRear  = 5,
		Right      = 6,
		RightFront = 7,
		None       = 8,
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

protected:
	void advance();

private:
	QPoint speed_;
	HOA::Direction moveDirection_;
};

#endif // MOVABLE_H
