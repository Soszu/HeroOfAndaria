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

	static void setMovementManager(const MovementManager *movement);

	QPointF speed() const;
	virtual qreal maxSpeed() const = 0;
	virtual qreal acceleration() const; //TODO make it pure

	qreal rotationSpeed() const;

	virtual bool canMove() const;
	virtual bool canRotate() const;

	void move(HOA::Direction direction);
	void stop();

	void rotate(const QPointF &rotation);

protected:
	static const MovementManager *movementManager_;

	void advance();

private:
	QPointF speed_;
	HOA::Direction moveDirection_;

	QPointF targetRotation_;
};

/**
 * \enum HOA::CollisionType
 */
namespace HOA {
	namespace Collision {
		enum Type : quint8 {
			None   = 0x00,
			Attack = 0x01,
			Simple = 0x02,
		};
	}
}

/**
 * \class MovementManager
 * Analyses the move and checks if it is possible given present state.
 * TODO perhaps something more...?
 */
class MovementManager
{
public:
	virtual bool canMove(const Movable *object, const QPointF &vector, qreal angle = 0.0) const = 0;
	virtual bool canRotate(const Movable *object, qreal angle) const = 0;

	virtual void collide(Object *lhs, Object *rhs) = 0;
	virtual int collisionType(const Object *lhs, const Object *rhs) const = 0;
};

#endif // MOVABLE_H
