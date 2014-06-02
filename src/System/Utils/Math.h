#ifndef UTILS_H
#define UTILS_H

#include <QtCore>

namespace HOA {
	qreal vectorLength(const QPointF &vector);
	QPointF rotateVector(const QPointF &vector, qreal angle);
	QPointF lengthenVector(const QPointF &vector, qreal length);

	qreal rotationToAngle(const QPointF &rotation);
	qreal angleDifference(qreal lhs, qreal rhs);
	qreal det(const QPointF &a, const QPointF &b, const QPointF &s = QPointF(0.0, 0.0));
}

#endif // UTILS_H
