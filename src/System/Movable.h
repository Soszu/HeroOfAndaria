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

class MovementManager;

/**
 * \class Movable
 */
class Movable : public Object
{
public:
	Movable();

	virtual bool isMovable() const;

	void setMovementManager(const MovementManager *movement);

	QPoint speed() const;
	virtual int maxSpeed() const = 0;

	void move(HOA::Direction direction);
	void stop();

protected:
	void advance();

private:
	const MovementManager *movementManager_;
	QPoint speed_;
	HOA::Direction moveDirection_;
};

/**
 * \class MovementManager
 * Analyses the move and checks if it is possible given present state.
 * TODO perhaps something more...?
 */
class MovementManager
{
public:
	virtual bool canMakeMove(const Movable *object, const QPoint &vector) const = 0;
};

#endif // MOVABLE_H
