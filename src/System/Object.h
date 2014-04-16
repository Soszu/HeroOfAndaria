#ifndef OBJECT_H
#define OBJECT_H

#include <QtCore>

namespace HOA {
	//TODO more when the time comes
	enum class ObjectType : quint8 {
		Creature,
		Human,
		Item,
		Weapon,
		Town,
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

	void setAttackManager(AttackManager *attackManager);
	virtual void receiveAttack(const Attack &attack);

	QPoint position() const;
	void setPosition(const QPoint &position);

	QPoint rotation() const;
	void setRotation(const QPoint &rotation);

protected:
	static const int ADVANCE_TIMEOUT      = 40;
	static const int TIME_DIVISOR         = 40;
	static const int REAL_ADVANCE_TIMEOUT = ADVANCE_TIMEOUT / TIME_DIVISOR;

	AttackManager *attackManager_;

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
