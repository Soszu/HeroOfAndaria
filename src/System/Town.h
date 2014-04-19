#ifndef TOWN_H
#define TOWN_H

#include <QtCore>
#include "System/Object.h"
#include "System/Place.h"

class Town : public Object
{
Q_OBJECT;

public:
	Town(const QString &name);

	virtual HOA::ObjectType objectType() const;

	QString name() const;

	const QVector <Place *> & places() const;
	void visitPlace(Place *p);
	void addPlace(Place *p);

	void exitTown();

signals:
	void townExited();

private:
	QString name_;

	QVector <Place *> places_;
};

#endif // TOWN_H
