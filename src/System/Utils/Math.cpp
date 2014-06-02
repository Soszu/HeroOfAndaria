#include <cmath>
#include "System/Utils/Math.h"

qreal HOA::vectorLength(const QPointF &vector)
{
	return qSqrt(vector.x() * vector.x() + vector.y() * vector.y());
}

QPointF HOA::rotateVector(const QPointF &vector, qreal angle)
{
	qreal x = vector.x();
	qreal y = vector.y();

	qreal px = x * qCos(angle) - y * qSin(angle);
	qreal py = x * qSin(angle) + y * qCos(angle);

	return {px, py};
}

QPointF HOA::lengthenVector(const QPointF &vector, qreal length)
{
	qreal x = vector.x();
	qreal y = vector.y();

	qreal currentLength = vectorLength({x, y});

	if (currentLength == 0)
		return {0, 0};

	x /= currentLength;
	y /= currentLength;

	x *= length;
	y *= length;

	return {x, y};
}

qreal HOA::rotationToAngle(const QPointF &rotation)
{
	return std::fmod(QLineF(QPointF(0.0, 0.0), QPointF(rotation.x(), -rotation.y())).angle() + 270.0, 360.0);
}

qreal HOA::angleDifference(qreal lhs, qreal rhs)
{
	qreal l = std::fmod(lhs, 360.0);
	qreal r = std::fmod(rhs, 360.0);
	if (l < 0)
		l += 360.0;
	if (r < 0)
		r += 360.0;
	return qMin(qAbs(l - r), 360.0 - qAbs(l - r));
}

qreal HOA::det(const QPointF &a, const QPointF &b, const QPointF &s)
{
	return (a.x() - s.x()) * (b.y() - s.y()) - (a.y() - s.y()) * (b.x() - s.x());
}
