#ifndef OBJECT_H
#define OBJECT_H

#include <QtCore>
#include "System/Bases/ItemBase.h"

namespace HOA {
	//TODO more when the time comes
	enum class ObjectType : quint8 {
		Creature,
		Monster,
		Character,
		Human,

		Item,
		Weapon,

		Location,
		Town,
	};

	const QVector <ObjectType> creatureTypes {
		ObjectType::Creature,
		ObjectType::Monster,
		ObjectType::Character,
		ObjectType::Human,
	};
}

class Attack;
class AttackManager;

class Object : public QObject
{
Q_OBJECT;

public:
	Object();
	virtual ~Object();

	virtual HOA::ObjectType objectType() const = 0;
	virtual bool isMovable() const;

	/** Attacks */

	void setAttackManager(AttackManager *attackManager);
	virtual void receiveAttack(const Attack &attack);

	/** Position and rotation */

	QPoint position() const;
	void setPosition(const QPoint &position);

	QPoint rotation() const;
	void setRotation(const QPoint &rotation);

	/** Effects */

	const QVector <HOA::Effect> effects();
	void addEffect(const HOA::Effect &effect);
	void removeEffect(const HOA::Effect &effect);
	void removeEffect(const HOA::EffectType effectType);

protected:
	static int advanceTimeout();
	static int timeDivisor();
	static int realAdvanceTimeout();

	AttackManager *attackManager_;
	QVector <int> registeredAttacks_; //TODO with global timer remove attacks some time ago in advance()

	QVector <HOA::Effect> effects_;

protected slots:
	virtual void advance();

signals:
	void positionSet();
	void rotationSet();
	void destroyed();
	void advanced();

private:
	QPoint position_;
	QPoint rotation_;

	static QTimer advanceTimer_;

	static void initTimer();
};

#endif // OBJECT_H
