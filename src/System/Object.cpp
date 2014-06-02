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

void Object::advance()
{
	//TODO static changes (effects expiring...)
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
