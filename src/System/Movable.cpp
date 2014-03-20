#include "System/Movable.h"
#include <cmath>

/**
 * \class Movable
 */

static QPoint rotateVector(QPoint const &vector, qreal angle)
{
	qreal x = vector.x();
	qreal y = vector.y();

	qreal px = x * cos(angle) - y * sin(angle);
	qreal py = x * sin(angle) + y * cos(angle);

	return QPoint((int)px, (int)py);
}

static QPoint vectorLength(QPoint const &vector, int length)
{
	qreal x = vector.x();
	qreal y = vector.y();

	qreal curLength = sqrt(pow(x, 2) + pow(y, 2));

	x /= curLength;
	y /= curLength;

	x *= length;
	y *= length;

	return QPoint(x, y);
}

Movable::Movable() :
	movementManager_(nullptr), speed_(QPoint(0,0)), moveDirection_(HOA::Direction::None)
{}

bool Movable::isMovable() const
{
	return true;
}

void Movable::setMovementManager(const MovementManager *movementManager)
{
	movementManager_ = movementManager;
}

QPoint Movable::speed() const
{
	return speed_;
}

void Movable::stop()
{
	moveDirection_ = HOA::Direction::None;
}

void Movable::move(HOA::Direction direction)
{
	moveDirection_ = direction;
}

void Movable::advance()
{
	if (moveDirection_ != HOA::Direction::None) {
		//TODO make some height difference check + effects (awww, this damn rocky terrain, my feet hurt) - virtual function?
		QPoint dir = rotateVector(rotation() - position(), ((qreal)moveDirection_) * (-M_PI / 4));
		speed_ = std::move(vectorLength(dir, maxSpeed()));

		Q_ASSERT(movementManager_ != nullptr);
		QPoint vector = speed() * REAL_ADVANCE_TIMEOUT;
		if (movementManager_->canMakeMove(this, vector))
			setPosition(position() + vector);
	}
	Object::advance();
}