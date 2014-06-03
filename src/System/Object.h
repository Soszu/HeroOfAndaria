#ifndef OBJECT_H
#define OBJECT_H

#include <QtCore>
#include "System/Bases/ItemBase.h"
#include "System/EffectCarrier.h"

namespace HOA {

	enum class ObjectType : quint8 {
		Creature,
		Monster,
		Barbarian,
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
		ObjectType::Barbarian,
		ObjectType::Character,
		ObjectType::Human,
	};
}

class Attack;
class AttackManager;

class Object : public QObject, public EffectCarrier
{
Q_OBJECT;

public:
	Object();
	virtual ~Object();

	virtual HOA::ObjectType objectType() const = 0;
	virtual bool isMovable() const;

	static int advanceTimeout();

	/** Attacks */

	static void setAttackManager(AttackManager *attackManager);
	virtual void receiveAttack(const Attack &attack);

	/** Position and rotation */

	QPointF position() const;
	void setPosition(const QPointF &position);

	QPointF rotation() const;
	void setRotation(const QPointF &rotation);

public slots:
	virtual void advance();

protected:
	static int timeDivisor();
	static int realAdvanceTimeout();

	static AttackManager *attackManager_;
	QVector <int> registeredAttacks_; //TODO with global timer remove attacks some time ago in advance()

signals:
	void positionSet();
	void rotationSet();
	void destroyed();
	void advanced();

private:
	QPointF position_;
	QPointF rotation_;
};

#endif // OBJECT_H
