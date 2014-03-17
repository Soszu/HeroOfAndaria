#ifndef OBJECT_H
#define OBJECT_H

#include <QtCore>

namespace HOA {
	//TODO more when the time comes
	enum class ObjectType : quint8 {
		Creature,
		Item
	};
}

class Object : public QObject
{
Q_OBJECT;

public:
	Object();
	virtual ~Object();

	virtual HOA::ObjectType objectType() const = 0;

	QPoint position() const;
	void setPosition(const QPoint &position);

	QPoint rotation() const;
	void setRotation(const QPoint &rotation);

protected:
	static const int ADVANCE_TIMEOUT      = 40;
	static const int TIME_DIVIDER         = 40;
	static const int REAL_ADVANCE_TIMEOUT = ADVANCE_TIMEOUT / TIME_DIVIDER;

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
