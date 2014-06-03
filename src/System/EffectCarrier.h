#ifndef EFFECTCARRIER_H
#define EFFECTCARRIER_H

#include "System/Bases/ItemBase.h"

class EffectCarrier
{
public:
	const QVector <HOA::Effect> effects();

	HOA::Effect effect(HOA::EffectType effectType) const;
	void addEffect(const HOA::Effect &effect);
	bool hasEffect(HOA::EffectType effectType) const;

	void removeEffect(const HOA::Effect &effect);
	void removeEffect(HOA::EffectType effectType);

	void removeEffects(HOA::EffectType effectType);

	void triggerExpire(int time);

private:
	QVector <HOA::Effect> effects_;
};

#endif // EFFECTCARRIER_H
