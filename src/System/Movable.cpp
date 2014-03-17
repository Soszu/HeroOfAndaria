#include "System/Movable.h"
#include <cmath>

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

Movable::Movable()
	: speed_(QPoint(0,0)), moveDirection_(HOA::Direction::None)
{}

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
		QPoint dir = rotateVector(rotation() - position(), ((qreal)moveDirection_) * (-M_PI / 4));
		speed_ = std::move(vectorLength(dir, maxSpeed()));

		setPosition(position() + speed() * REAL_ADVANCE_TIMEOUT);
	}
	Object::advance();
}
