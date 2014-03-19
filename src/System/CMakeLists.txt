set (HOASystem_SRCS
# 	Attack.cpp
# 	Blacksmith.cpp
	Carriable.cpp
	Character.cpp
	Creature.cpp
	CreatureBase.cpp
	EquipmentCarrier.cpp
	GlobalMap.cpp
	Grid.cpp
	Human.cpp
# 	Inn.cpp
# 	Item.cpp
# 	LocalMap.cpp
	Map.cpp
# 	Mission.cpp
# 	Monster.cpp
	Movable.cpp
# 	NonHuman.cpp
	Object.cpp
 	Place.cpp
# 	Quest.cpp
	QuestCarrier.cpp
	Tile.cpp
 	Town.cpp
)

set (HOASystem_HDRS
	Object.h
	Map.h
)

qt5_wrap_cpp (HOASystem_SRCS ${HOASystem_HDRS})

add_library (HOASystem ${HOASystem_SRCS})
target_link_libraries (HOASystem ${Qt5Widgets_LIBRARIES})
