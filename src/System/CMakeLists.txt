set (HOASystem_SRCS
	AI/AI.cpp
	Attack.cpp
	Bases/CreatureBase.cpp
	Bases/ItemBase.cpp
	Bases/WeaponBase.cpp
	Blacksmith.cpp
	Carriable.cpp
	Character.cpp
	Creature.cpp
	DataManager.cpp
	EquipmentCarrier.cpp
	GlobalMap.cpp
	Grid.cpp
	Human.cpp
	Inn.cpp
	Item.cpp
	LocalMap.cpp
	Map.cpp
# 	Mission.cpp
	Monster.cpp
	Models/CreatureModel.cpp
	Models/ItemModel.cpp
	Models/WeaponModel.cpp
	Movable.cpp
# 	NonHuman.cpp
	Object.cpp
	Paths.cpp
 	Place.cpp
# 	Quest.cpp
	QuestCarrier.cpp
	Tile.cpp
 	Town.cpp
 	Utils/Math.cpp
 	Weapon.cpp
)

set (HOASystem_HDRS
	Creature.h
	GlobalMap.h
	LocalMap.h
	Models/CreatureModel.h
	Models/ItemModel.h
	Models/WeaponModel.h
	Map.h
	Object.h
	Town.h
)

qt5_wrap_cpp (HOASystem_SRCS ${HOASystem_HDRS})

add_library (HOASystem ${HOASystem_SRCS})
target_link_libraries (HOASystem ${Qt5Widgets_LIBRARIES})
