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
{
	registeredAttacks_.append(attack.uid());
}

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

const QVector <HOA::Effect> Object::effects()
{
	return effects_;
}

void Object::addEffect(const HOA::Effect &effect)
{
	effects_.append(effect);
}

void Object::removeEffect(const HOA::Effect &effect)
{
	for (int i = 0; i < effects_.size(); ++i) {
		if (effects_[i] == effect) {
			effects_.remove(i);
			--i;
		}
	}
}

void Object::removeEffect(const HOA::EffectType effectType)
{
	for (int i = 0; i < effects_.size(); ++i) {
		if (effects_[i].type == effectType) {
			effects_.remove(i);
			--i;
		}
	}
}

int Object::advanceTimeout()
{
	static const int ADVANCE_TIMEOUT = 40;
	return ADVANCE_TIMEOUT;
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

void Object::advance()
{
	//TODO static changes (effects expiring...)
	emit advanced();
}

void Object::initTimer()
{
	advanceTimer_.start(advanceTimeout());
}