set (HOASystem_SRCS
	Attack.cpp
	Carriable.cpp
	Creature.cpp
	EquipmentCarrier.cpp
	Grid.cpp
	Inn.cpp
	LocalMap.cpp
	Mission.cpp
	Movable.cpp
	Object.cpp
	Quest.cpp
	Tile.cpp
	Blacksmith.cpp
	Character.cpp
	CreatureBase.cpp
	GlobalMap.cpp
	Human.cpp
	Item.cpp
	Map.cpp
	Monster.cpp
	NonHuman.cpp
	Place.cpp
	QuestCarrier.cpp
	Town.cpp
)

set (HOASystem_HDRS
	Object.h
)

qt5_wrap_cpp (HOASystem_SRCS ${HOASystem_HDRS})

add_library (HOASystem ${HOASystem_SRCS})
target_link_libraries (HOASystem ${Qt5Widgets_LIBRARIES})
