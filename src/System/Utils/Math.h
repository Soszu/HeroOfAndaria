#ifndef UTILS_H
#define UTILS_H

#include <QtCore>

namespace HOA {
	qreal vectorLength(const QPointF &vector);
	QPointF rotateVector(const QPointF &vector, qreal angle);
	QPointF lengthenVector(const QPointF &vector, qreal length);
}

#endif // UTILS_H
