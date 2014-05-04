#include "System/Movable.h"
#include "System/Utils/Math.h"

/**
 * \class Movable
 */

const MovementManager * Movable::movementManager_ = nullptr;

Movable::Movable() :
	speed_({0, 0}), moveDirection_(HOA::Direction::None)
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
		qreal destinationDistanceLength = HOA::vectorLength(destinationDistance);

		QPointF dir = HOA::rotateVector(destinationDistance, ((qreal)moveDirection_) * (-M_PI / 4));

		speed_ = HOA::lengthenVector(dir, qMin((qreal)maxSpeed(), destinationDistanceLength)).toPoint();

		Q_ASSERT(movementManager_ != nullptr);
		QPoint vector = speed() * realAdvanceTimeout();

		if (movementManager_->canMakeMove(this, vector)) {
			setPosition(position() + vector);

			//HACK
			if (!movementManager_->canMakeMove(this, {0, 0}))
				setPosition(position() - vector);
		}
	}
	Object::advance();
}
