#include "Graphics/GraphicsBlacksmith.h"
#include "Graphics/GraphicsCharacter.h"
#include "Graphics/GraphicsCreature.h"
#include "Graphics/GraphicsFactory.h"
#include "Graphics/GraphicsInn.h"
#include "Graphics/GraphicsItem.h"
#include "Graphics/GraphicsLocalMap.h"
#include "Graphics/GraphicsMonster.h"
#include "Graphics/GraphicsTown.h"

QHash <const Object *, GraphicsObject *> GraphicsFactory::map_;
QHash <Place *, GraphicsPlace *> GraphicsFactory::placesMap_;
QHash <Map *, GraphicsMap *> GraphicsFactory::mapsMap_;

GraphicsObject * GraphicsFactory::get(Object *object)
{
	GraphicsObject *graphicsObject;
	const Object *constObject = (const Object *)object;
	if (!map_.contains(constObject)) {
		switch (object->objectType()) {
			case HOA::ObjectType::Creature:
				graphicsObject = new GraphicsCreature((Creature *)object);
				break;
			case HOA::ObjectType::Monster:
				graphicsObject = new GraphicsMonster((Monster *)object);
				break;
			case HOA::ObjectType::Character:
			case HOA::ObjectType::Human:
				graphicsObject = new GraphicsCharacter((Character *)object);
				break;
			case HOA::ObjectType::Item:
				graphicsObject = new GraphicsItem((Item *)object);
				break;
			case HOA::ObjectType::Location:
				graphicsObject = new GraphicsLocation((Location *)object);
				break;
			case HOA::ObjectType::Town:
				graphicsObject = new GraphicsTownObject((Town *)object);
				break;
			default:
				Q_ASSERT(false);
		}
		map_[constObject] = graphicsObject;
	} else {
		graphicsObject = map_[constObject];
	}

	return graphicsObject;
}

GraphicsObject * GraphicsFactory::get(const Object *object)
{
	Q_ASSERT(map_.contains(object));
	return map_[object];
}

GraphicsPlace * GraphicsFactory::get(Place *place)
{
	GraphicsPlace * graphicsPlace;
	if (!placesMap_.contains(place)) {
		switch (place->type()) {
			case HOA::PlaceType::Blacksmith:
				graphicsPlace = new GraphicsBlacksmith((Blacksmith *)place);
				break;
			case HOA::PlaceType::Inn:
				graphicsPlace = new GraphicsInn((Inn *)place);
				break;
			default:
				Q_ASSERT(false);
		}
		placesMap_[place] = graphicsPlace;
	} else {
		graphicsPlace = placesMap_[place];
	}

	return graphicsPlace;
}

GraphicsMap * GraphicsFactory::get(Map *map)
{
	GraphicsMap *graphicsMap;
	if (!mapsMap_.contains(map)) {
		//TODO put the global map here + some function in both global and local map or watch out
		graphicsMap = new GraphicsLocalMap(static_cast<LocalMap *>(map));
		mapsMap_[map] = graphicsMap;
	} else {
		graphicsMap = mapsMap_[map];
	}

	return graphicsMap;
}

GraphicsItem * GraphicsFactory::get(Item *item)
{
	return new GraphicsItem(item);
}
