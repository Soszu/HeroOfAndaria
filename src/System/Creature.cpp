#include "System/Creature.h"

Creature::Creature(const CreatureBase *base) :
	base_(base), hitPoints_(0)
{
	initStats();
	initActions();

	//TODO
	setCurrentWeapon(new Weapon);
}

Creature::~Creature()
{}

void Creature::initStats()
{
	setHitPoints(fullHitPoints());
}

void Creature::initActions()
{
	freezed_ = false;
	currentAction_ = HOA::CreatureAction::None;
	connect(&actionTimeLine_, &QTimeLine::finished, this, &Creature::onActionFinished);
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

int Creature::maxSpeed() const
{
	//TODO depending on attributes and skills(?)
	return 4;
}

UID Creature::uid() const
{
	return base_->uid();
}

QString Creature::name() const
{
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
	//TODO

	if (freezed_)
		return;

	currentAction_ = HOA::CreatureAction::Attack;

	Attack fullAttack(attack);

	fullAttack.setAttacker(this);
	fullAttack.setWeapon(currentWeapon());

	currentAttack_ = fullAttack;

	attackManager_->attack(fullAttack);

	freezed_ = true;

	int attackDuration = 500;
	actionTimeLine_.setDuration(attackDuration);

	actionTimeLine_.stop();
	actionTimeLine_.start();
}

void Creature::receiveAttack(const Attack &attack)
{
	if (registeredAttacks_.contains(attack.uid()))
		return;

	//TODO no it's not perfect
	setHitPoints(qMax(hitPoints() - attack.weapon()->damage(), 0));

	freezed_ = true;

	if (hitPoints() == 0)
		return;

	Object::receiveAttack(attack);

	//TODO
	currentAction_ = HOA::CreatureAction::Recoil;

	int recoilDuration = 500;
	actionTimeLine_.setDuration(recoilDuration);

	actionTimeLine_.start();
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
	out << creature.uid();
	return out;
}

QDataStream & operator >> (QDataStream &in, Creature &creature)
{
	UID uid;
	in >> uid;
	creature.setBase(CreatureModel::creature(uid));
	return in;
}

void Creature::onActionFinished()
{
	freezed_ = false;
	currentAction_ = HOA::CreatureAction::None;
}