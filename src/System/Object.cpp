#include "System/Attack.h"
#include "System/Object.h"

AttackManager * Object::attackManager_ = nullptr;

Object::Object()
{}

Object::~Object()
{
	emit destroyed();
}

bool Object::isMovable() const
{
	return false;
}

int Object::advanceTimeout()
{
	static const int ADVANCE_TIMEOUT = 40;
	return ADVANCE_TIMEOUT;
}

void Object::setAttackManager(AttackManager *attackManager)
{
	attackManager_ = attackManager;
}

void Object::receiveAttack(const Attack &attack)
{
	registeredAttacks_.append(attack.uid());
}

QPointF Object::position() const
{
	return position_;
}

void Object::setPosition(const QPointF &position)
{
	position_ = position;
	emit positionSet();
}

QPointF Object::rotation() const
{
	return rotation_;
}

void Object::setRotation(const QPointF &rotation)
{
	rotation_ = rotation;
	emit rotationSet();
}

void Object::advance()
{
	EffectCarrier::triggerExpire(advanceTimeout());
	emit advanced();
}

int Object::timeDivisor()
{
	static const int TIME_DIVISOR = 40;
	return TIME_DIVISOR;
}

int Object::realAdvanceTimeout()
{
	return advanceTimeout() / timeDivisor();
}
