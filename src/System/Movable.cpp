#include "System/Movable.h"
#include "System/Utils/Math.h"

/**
 * \class Movable
 */

const MovementManager * Movable::movementManager_ = nullptr;

Movable::Movable() :
	speed_(0.0, 0.0), moveDirection_(HOA::Direction::None)
{}

bool Movable::isMovable() const
{
	return true;
}

void Movable::setMovementManager(const MovementManager *movementManager)
{
	movementManager_ = movementManager;
}

QPointF Movable::speed() const
{
	return speed_;
}

qreal Movable::acceleration() const
{
	static const qreal ARBITRARY_ACCELERATION_FOR_ANY_MOVABLE_OBJECT_WITH_A_SEMBLANCE_OF_SELF_RESPECT = 3.0;
	return ARBITRARY_ACCELERATION_FOR_ANY_MOVABLE_OBJECT_WITH_A_SEMBLANCE_OF_SELF_RESPECT;
}

qreal Movable::rotationSpeed() const
{
	static const qreal ARBITRARY_ROTATION_SPEED_FOR_ANY_MOVABLE_OBJECT_WITH_A_SEMBLANCE_OF_SELF_RESPECT = 6.5;
	return ARBITRARY_ROTATION_SPEED_FOR_ANY_MOVABLE_OBJECT_WITH_A_SEMBLANCE_OF_SELF_RESPECT;
}

bool Movable::canMove() const
{
	return true;
}

bool Movable::canRotate() const
{
	return true;
}

void Movable::move(HOA::Direction direction)
{
	moveDirection_ = direction;
}

void Movable::stop()
{
	moveDirection_ = HOA::Direction::None;
}

/** TODO Rotate relatively to position */
void Movable::rotate(const QPointF &rotation)
{
	targetRotation_ = rotation;
}

void Movable::advance()
{
	/** Movement */

	//TODO make some height difference check + effects (awww, this damn rocky terrain, my feet hurt) - virtual function?

	QPointF vector = speed() * (qreal)realAdvanceTimeout();

	if (movementManager_->canMove(this, vector)) {
		setPosition(position() + vector);
		setRotation(rotation() + vector);
		//HACK
		if (!movementManager_->canMove(this, {0, 0}))
			setPosition(position() - vector);
	}

	/** Speed acceleration */

	if (moveDirection_ != HOA::Direction::None && canMove()) {
		QPointF dir = HOA::rotateVector(rotation() - position(), ((qreal)moveDirection_) * (-M_PI / 4.0));
		speed_      = HOA::lengthenVector(dir, qMin((qreal)maxSpeed(), HOA::vectorLength(speed()) + acceleration()));
	} else {
		speed_      = HOA::lengthenVector(rotation(), qMax(0.0, HOA::vectorLength(speed()) - acceleration()));
	}

	static const qreal ROTATION_THRESHOLD = 1.0;

	/** Rotation */

	if (HOA::angleDifference(HOA::rotationToAngle(targetRotation_ - position()),
	                         HOA::rotationToAngle(rotation() - position())) > ROTATION_THRESHOLD
	   && canRotate()) {
		qreal dir = HOA::det(targetRotation_, rotation(), position()) > 0
			? -1.0
			: +1.0;

		qreal angle       = HOA::rotationToAngle(rotation()      - position());
		qreal targetAngle = HOA::rotationToAngle(targetRotation_ - position());

		QPointF currentRotation = rotation();
		QPointF rotationToSet;

		if (rotationSpeed() > HOA::angleDifference(angle, targetAngle))
			rotationToSet = targetRotation_;
		else
			rotationToSet = HOA::rotateVector(rotation() - position(),
			                                  qDegreesToRadians(rotationSpeed() * dir)) + position();

		if (movementManager_->canRotate(this, HOA::rotationToAngle(rotationToSet - position())))
			setRotation(rotationToSet);
		//HACK
		if (!movementManager_->canRotate(this, HOA::rotationToAngle(rotation() - position())))
			setRotation(currentRotation);
	}

	Object::advance();
}
