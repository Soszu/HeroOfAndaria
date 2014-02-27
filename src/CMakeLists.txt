set (HeroOfAndaria_SRCS
	Attack.cpp
	Blacksmith.cpp
	Carriable.cpp
	Character.cpp
	Creature.cpp
	CreatureBase.cpp
	EquipmentCarrier.cpp
	GlobalMap.cpp
	GraphicsBlacksmith.cpp
	GraphicsCreature.cpp
	GraphicsEquipmentExchange.cpp
	GraphicsGlobalMap.cpp
	GraphicsInn.cpp
	GraphicsItem.cpp
	GraphicsLocalMap.cpp
	GraphicsMap.cpp
	GraphicsObject.cpp
	GraphicsPlace.cpp
	GraphicsTown.cpp
	Grid.cpp
	Human.cpp
	Inn.cpp
	Item.cpp
	LocalMap.cpp
	main.cpp
	MainWindow.cpp
	Map.cpp
	Menu.cpp
	Mission.cpp
	Monster.cpp
	Movable.cpp
	NonHuman.cpp
	Object.cpp
	Place.cpp
	Quest.cpp
	QuestCarrier.cpp
	Tile.cpp
	Town.cpp
)

set (HeroOfAndaria_HDRS
	Object.h
	GraphicsMap.h
)

qt5_wrap_cpp (HeroOfAndaria_SRCS ${HeroOfAndaria_HDRS})

add_executable (HeroOfAndaria ${HeroOfAndaria_SRCS})
target_link_libraries (HeroOfAndaria ${Qt5Widgets_LIBRARIES})
