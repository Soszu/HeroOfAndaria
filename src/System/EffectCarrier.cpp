#include "System/EffectCarrier.h"

HOA::Effect EffectCarrier::effect(HOA::EffectType effectType) const
{
	for (HOA::Effect e : effects_)
		if (e.type == effectType)
			return e;
	return HOA::Effect();
}

void EffectCarrier::addEffect(const HOA::Effect &effect)
{
	effects_.append(effect);
}

bool EffectCarrier::hasEffect(HOA::EffectType effectType) const
{
	return effect(effectType).isValid();
}

void EffectCarrier::removeEffect(const HOA::Effect &effect)
{
	for (int i = 0; i < effects_.size(); ++i) {
		if (effects_[i] == effect) {
			effects_.remove(i);
			--i;
		}
	}
}

void EffectCarrier::removeEffect(const HOA::EffectType effectType)
{
	for (int i = 0; i < effects_.size(); ++i)
		if (effects_[i].type == effectType)
			return effects_.remove(i);
}

void EffectCarrier::removeEffects(const HOA::EffectType effectType)
{
	for (int i = 0; i < effects_.size(); ++i) {
		if (effects_[i].type == effectType) {
			effects_.remove(i);
			--i;
		}
	}
}

const QVector <HOA::Effect> EffectCarrier::effects()
{
	return effects_;
}

void EffectCarrier::triggerExpire(int time)
{
	for (HOA::Effect &e : effects_) {
		if (e.duration != HOA::Effect::PERMANENT) {
			e.duration -= time;
			if (e.duration <= 0)
				removeEffect(e);
		}
	}
}
