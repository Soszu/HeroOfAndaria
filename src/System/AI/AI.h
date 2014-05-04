#ifndef AI_H
#define AI_H

#include "System/Creature.h"

namespace HOA {
	enum class AIBehaviour : quint16 {
		None,
		Walk,
		Run,
		Jump,
		Rotate,

		PrimaryAttack,
		SecondaryAttack,
	};
}

/**
 * \class VisibilityManager
 * 'Eyes' of the AI. Should be implemented by some kind of map.
 */
class VisibilityManager
{
public:
	virtual QVector <Object *> objectsInCircle(const QPoint &center, int ray) = 0;
};

/**
 * \class AI
 * Represents artificial intelligence for the given Creature.
 * On AI timer timeout each of the Creatures checks it's AI object for
 */
class AI
{
public:
	AI(Creature *creature);

	static void setVisibilityManager(VisibilityManager *visibilityManager);

	/**
	 * \struct Behaviour
	 * Contains data about the behaviour of the creature.
	 * Fields' first and second values depend on the behaviour.
	 */
	struct Behaviour {
		HOA::AIBehaviour behaviour;
		int first;
		int second;
	};

	virtual QVector<Behaviour> act() = 0;

protected:
	/** Note that visibilityManager must be set each time the map is changed! */
	static VisibilityManager *visibilityManager_;
	Creature *creature_;
};

/**
 * \class AIFactory
 * Produces AI objects for Creatures.
 */
class AIFactory
{
public:
	static AI * ai(Creature *creature);

private:
	AIFactory() = delete;
	AIFactory(const AIFactory &) = delete;

	static QHash <Creature *, AI *> map_;
};

/**
 * \class FollowerAI
 */
class FollowerAI : public AI
{
public:
	FollowerAI(Creature *creature);
	virtual QVector<Behaviour> act();
private:
	bool seesPlayer;
	QPointF playerPos;

	void detectPlayer();
};

#endif // AI_H
