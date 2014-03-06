#include "System/Movable.h"
#include <cmath>


QPoint rotateVector(QPoint const & vector, double angle) {
	double x = vector.x();
	double y = vector.y();
	
	double px = x * cos(angle) + y * sin(angle);
	double py = x * sin(angle) + y * cos(angle);
	
	return QPoint((int)px, (int)py);
}

QPoint setVectorLength(QPoint const & vector, int length) {
	double x = vector.x();
	double y = vector.y();

	double curLength = sqrt(pow(x, 2) + pow(y,2));
	
	x /= curLength;
	y /= curLength;
	
	x *= length;
	y *= length;
	
	return QPoint(x, y);
}

Movable::Movable() : speed_(QPoint(0,0))
{
	
}

QPoint Movable::speed() const {
	return this->speed_;
}

void Movable::stop() {
	this->speed_ = QPoint(0,0);
}

void Movable::move(HOA::Direction direction) {
	QPoint dir = rotateVector(this->rotation(), ((double)direction) * (M_PI / 4));
	this->speed_ = std::move(setVectorLength(dir, this->maxSpeed()));
}
void Movable::advance(double dt) {
	this->setPosition(this->position() + this->speed() * dt);
}



