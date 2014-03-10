#ifndef GRAPHICSCREATURE_H
#define GRAPHICSCREATURE_H

#include "Graphics/GraphicsObject.h"
#include "System/Creature.h"

class GraphicsCreature : public GraphicsObject
{
public:
	GraphicsCreature(Creature *creature);
};

#endif // GRAPHICSCREATURE_H
