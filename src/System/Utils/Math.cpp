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
