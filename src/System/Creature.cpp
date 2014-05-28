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
	freezed_   = false;
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
	return 5;
}

UID Creature::uid() const
{
	return base_->uid();
}

QString Creature::name() const
{
	//TODO
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

	freezed_   = true;

	QPoint attackerPosition = attack.attacker()->position();
	QPoint vectorToAttacker = HOA::lengthenVector(attackerPosition, 200.0).toPoint();
	recoilDirection_        = HOA::rotateVector(vectorToAttacker, qDegreesToRadians(180.0f)).toPoint();

	if (hitPoints() == 0)
		return;

	Object::receiveAttack(attack);

	//TODO
	currentAction_ = HOA::CreatureAction::Recoil;

	if (currentAction_ == HOA::CreatureAction::Recoil)
		qDebug() << "now currentAction = Recoil";

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
	if (currentAction() == HOA::CreatureAction::Recoil) {

		//TODO 1. depending on power of strike, 2. emmm... this is a sword, not an elephant...
		// a = 1 / 400000, b = -11/40000, c = -11/200, d = 50
		qreal x1 = (qreal)actionTimeLine_.currentTime();
		qreal x2 = x1 + (qreal)advanceTimeout();
		qreal v1 = x1 * x1 * x1  / 400000 + x1 * x1 * -11 / 40000 + x1 * -11 / 200 + 50;
		qreal v2 = x2 * x2 * x2  / 400000 + x2 * x2 * -11 / 40000 + x2 * -11 / 200 + 50;

		QPointF vector = HOA::lengthenVector(recoilDirection_, v2 - v1);

		if (movementManager_->canMakeMove(this, vector.toPoint()))
			setPosition(position() + vector.toPoint());
	}
	Movable::advance();
}

void Creature::onActionFinished()
{
	if (currentAction_ == HOA::CreatureAction::Recoil)
		qDebug() << "on action finished";
	freezed_       = false;
	currentAction_ = HOA::CreatureAction::None;
}
