#include "System/Movable.h"

/**
 * \class Movable
 */

static qreal vectorLength(const QPointF &vector)
{
	return qSqrt(vector.x() * vector.x() + vector.y() * vector.y());
}

static QPointF rotateVector(const QPointF &vector, qreal angle)
{
	qreal x = vector.x();
	qreal y = vector.y();

	qreal px = x * qCos(angle) - y * qSin(angle);
	qreal py = x * qSin(angle) + y * qCos(angle);

	return {px, py};
}

static QPointF lengthenVector(const QPointF &vector, qreal length)
{
	qreal x = vector.x();
	qreal y = vector.y();

	qreal currentLength = vectorLength({x, y});

	if (currentLength == 0)
		return {0, 0};

	x /= currentLength;
	y /= currentLength;

	x *= length;
	y *= length;

	return {x, y};
}

Movable::Movable() :
	movementManager_(nullptr), speed_({0, 0}), moveDirection_(HOA::Direction::None)
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

		QPointF destinationDistance = rotation() - position();
		qreal destinationDistanceLength = vectorLength(destinationDistance);

		QPointF dir = rotateVector(destinationDistance, ((qreal)moveDirection_) * (-M_PI / 4));

		speed_ = lengthenVector(dir, qMin((qreal)maxSpeed(), destinationDistanceLength)).toPoint();

		Q_ASSERT(movementManager_ != nullptr);
		QPoint vector = speed() * REAL_ADVANCE_TIMEOUT;

		if (movementManager_->canMakeMove(this, vector))
			setPosition(position() + vector);

		//HACK
		if (!movementManager_->canMakeMove(this, {0, 0}))
			setPosition(position() - vector);
	}
	Object::advance();
}