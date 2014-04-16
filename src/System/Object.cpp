#include "System/Attack.h"
#include "System/Object.h"

QTimer Object::advanceTimer_;

Object::Object() :
	attackManager_(nullptr)
{
	static bool timerInitialized = false;
	if (!timerInitialized) {
		initTimer();
		timerInitialized = true;
	}
	connect(&advanceTimer_, &QTimer::timeout, this, &Object::advance);
}

Object::~Object()
{
	emit destroyed();
}

bool Object::isMovable() const
{
	return false;
}

void Object::setAttackManager(AttackManager *attackManager)
{
	attackManager_ = attackManager;
}

void Object::receiveAttack(const Attack &attack)
{}

QPoint Object::position() const
{
	return position_;
}

void Object::setPosition(const QPoint &position)
{
	position_ = position;
	emit positionSet();
}

QPoint Object::rotation() const
{
	return rotation_;
}

void Object::setRotation(const QPoint &rotation)
{
	rotation_ = rotation;
	emit rotationSet();
}

void Object::advance()
{
	//TODO static changes
	emit advanced();
}

void Object::initTimer()
{
	advanceTimer_.start(ADVANCE_TIMEOUT);
}