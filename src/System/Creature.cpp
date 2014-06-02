#include "System/Creature.h"
#include "System/Utils/Math.h"

Creature::Creature(const CreatureBase *base) :
	base_(base), hitPoints_(0)
{
	initStats();
	initActions();

	//TODO
	setCurrentWeapon(new Weapon);
	this->addItem(this->currentWeapon());
}

Creature::~Creature()
{}

void Creature::initStats()
{
	setHitPoints(fullHitPoints());
}

void Creature::initActions()
{
	currentAction_ = HOA::CreatureAction::None;

	//TODO no need for this
	connect(&actionTimeLine_, &QTimeLine::finished, this, &Creature::onActionFinished);
	actionTimeLine_.setCurveShape(QTimeLine::LinearCurve);
}

void Creature::setBase(const CreatureBase* base)
{
	this->base_ = base;

	if (base == nullptr)
		return;

	initStats();
}

HOA::ObjectType Creature::objectType() const
{
	return HOA::ObjectType::Creature;
}

qreal Creature::maxSpeed() const
{
	//TODO depending on attributes and skills(?)
	return 5.0;
}

UID Creature::uid() const
{
	return base_->uid();
}

QString Creature::name() const
{
	//TODO print it on the screen!
	if (objectType() == HOA::ObjectType::Monster)
		return "monster";
	else
		return "humano";
	return base_->name();
}

int Creature::hitPoints() const
{
	return hitPoints_;
}

void Creature::setHitPoints(int hitPoints)
{
	bool changed = hitPoints_ != hitPoints;
	hitPoints_ = hitPoints;
	if (changed)
		emit hitPointsChanged();
}

int Creature::fullHitPoints() const
{
	//TODO base
	return 20;
	return base_->fullHitPoints();
}

int Creature::agility() const
{
	return base_->agility();
}

int Creature::strength() const
{
	return base_->strength();
}

int Creature::intelligence() const
{
	return base_->intelligence();
}

int Creature::endurance() const
{
	return base_->endurance();
}

void Creature::attack(const Attack &attack)
{
	//TODO attack interval not working FIX IT

	if (!canPerformAction(HOA::CreatureAction::Attack))
		return;

	currentAction_ = HOA::CreatureAction::Attack;

	Attack fullAttack(attack);

	fullAttack.setAttacker(this);
	fullAttack.setWeapon(currentWeapon());

	currentAttack_ = fullAttack;

	attackManager_->attack(fullAttack);

	int attackDuration = 500;

	addEffect({HOA::EffectType::PerformingAction, attackDuration});
	addEffect({HOA::EffectType::CannotAttack,     attackDuration * 2});
}

void Creature::receiveAttack(const Attack &attack)
{
	if (registeredAttacks_.contains(attack.uid()))
		return;

	//TODO no it's not perfect
	setHitPoints(qMax(hitPoints() - attack.weapon()->damage(), 0));

	QPointF attackerPosition = attack.attacker()->position();
	QPointF vectorToAttacker = HOA::lengthenVector(attackerPosition - position(), 200.0);
	recoilDirection_         = HOA::rotateVector(vectorToAttacker, qDegreesToRadians(180.0)) + position();

	if (hitPoints() == 0) {
		addEffect({HOA::EffectType::Immobilised, HOA::Effect::PERMANENT});
		return;
	}

	Object::receiveAttack(attack);

	int recoilDuration = 500;
	addEffect({HOA::EffectType::Recoiling,    recoilDuration});
	addEffect({HOA::EffectType::Immobilised,  recoilDuration});
	addEffect({HOA::EffectType::CannotAttack, recoilDuration / 3});
}

void Creature::setCurrentWeapon(Weapon *weapon)
{
	currentWeapon_ = weapon;
}

Weapon * Creature::currentWeapon() const
{
	return currentWeapon_;
}

Attack Creature::currentAttack() const
{
	return currentAttack_;
}

bool Creature::canMove() const
{
	return !hasEffect(HOA::EffectType::Immobilised) && !hasEffect(HOA::EffectType::Freezed);
}

bool Creature::canRotate() const
{
	return !hasEffect(HOA::EffectType::Immobilised) && !hasEffect(HOA::EffectType::Freezed);
}

bool Creature::canPerformAction(HOA::CreatureAction action)
{
	return !hasEffect(HOA::EffectType::Freezed)
	    && !hasEffect(HOA::EffectType::PerformingAction)
	    && !hasEffect(HOA::EffectType::CannotAttack);
}

HOA::CreatureAction Creature::currentAction() const
{
	return currentAction_;
}

int Creature::currentActionTime() const
{
	return actionTimeLine_.currentTime();
}

int Creature::currentActionTotalTime() const
{
	return actionTimeLine_.duration();
}

QDataStream & operator << (QDataStream &out, const Creature &creature)
{
	out << creature.uid()
	    << creature.hitPoints_ << creature.effects_;
	return out;
}

QDataStream & operator >> (QDataStream &in, Creature &creature)
{
	UID uid;
	in >> uid;
	creature.setBase(CreatureModel::creature(uid));

	in >> creature.hitPoints_ >> creature.effects_;

	return in;
}

void Creature::advance()
{
	if (hasEffect(HOA::EffectType::Recoiling)) {
		//TODO depending on power of strike
		qreal x1 = (qreal)effect(HOA::EffectType::Recoiling).duration;
		qreal x2 = x1 + (qreal)advanceTimeout();

		auto distance = [](qreal x1, qreal x2) -> qreal {
			qreal v1 = x1 / 10.0;
			qreal v2 = x2 / 10.0;
			return v2 - v1;
		};

		QPointF vector = HOA::lengthenVector(recoilDirection_, distance(x1, x2));

		if (movementManager_->canMove(this, vector))
			setPosition(position() + vector);
		//HACK
		if (!movementManager_->canMove(this, QPointF(0.0, 0.0)))
			setPosition(position() - vector);
	}
	Movable::advance();
}

void Creature::onActionFinished()
{
	//TODO methinks we don't need it
	currentAction_ = HOA::CreatureAction::None;
}
