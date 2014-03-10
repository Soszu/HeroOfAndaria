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

	virtual HOA::ObjectType objectType() const = 0;

	QPoint position() const;
	void setPosition(QPoint position);

	QPoint rotation() const;
	void setRotation(QPoint rotation);

signals:
	void positionSet();
	void rotationSet();

private:
	QPoint position_;
	QPoint rotation_;
};

#endif // OBJECT_H
