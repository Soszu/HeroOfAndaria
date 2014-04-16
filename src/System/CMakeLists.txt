set (HOASystem_SRCS
	Attack.cpp
	Blacksmith.cpp
	Carriable.cpp
	Character.cpp
	Creature.cpp
	CreatureBase.cpp
	DataManager.cpp
	EquipmentCarrier.cpp
	GlobalMap.cpp
	Grid.cpp
	Human.cpp
	Inn.cpp
	Item.cpp
	ItemBase.cpp
# 	LocalMap.cpp
	Map.cpp
# 	Mission.cpp
# 	Monster.cpp
	Movable.cpp
# 	NonHuman.cpp
	Object.cpp
	Paths.cpp
 	Place.cpp
# 	Quest.cpp
	QuestCarrier.cpp
	Tile.cpp
 	Town.cpp
 	Utils.cpp
 	Weapon.cpp
 	WeaponBase.cpp
)

set (HOASystem_HDRS
	Creature.h
	CreatureBase.h
	GlobalMap.h
	Object.h
	Map.h
	Town.h
)

qt5_wrap_cpp (HOASystem_SRCS ${HOASystem_HDRS})

add_library (HOASystem ${HOASystem_SRCS})
target_link_libraries (HOASystem ${Qt5Widgets_LIBRARIES})
