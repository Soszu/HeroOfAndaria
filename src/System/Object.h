#ifndef OBJECT_H
#define OBJECT_H

#include <QtCore>

class Object : public QObject
{
Q_OBJECT;

public:
	Object();

	QPoint position();
	void setPosition(QPoint position);

	int rotation() const;
	void setRotation(QPoint rotation);

signals:
	void positionSet();
	void rotationSet();

private:
	QPoint position_;
	QPoint rotation_;
};

#endif // OBJECT_H
