set (HOAGraphics_SRCS GraphicsMonster.cpp
	GraphicsBlacksmith.cpp
	GraphicsCharacter.cpp
	GraphicsCreature.cpp
	GraphicsEquipmentExchange.cpp
	GraphicsGlobalMap.cpp
	GraphicsFactory.cpp
	GraphicsInn.cpp
	GraphicsItem.cpp
	GraphicsLocalMap.cpp
	GraphicsMap.cpp
	GraphicsObject.cpp
	GraphicsPlace.cpp
	GraphicsTown.cpp
	ImageButton.cpp
	KeyboardManager.cpp
	Panels.cpp
)

set (HOAGraphics_HDRS
	GraphicsEquipmentExchange.h
	GraphicsBlacksmith.h
	GraphicsInn.h
	GraphicsGlobalMap.h
	GraphicsMap.h
	GraphicsObject.h
	GraphicsPlace.h
	GraphicsTown.h
	ImageButton.h
	Panels.h
)

qt5_wrap_cpp (HOAGraphics_SRCS ${HOAGraphics_HDRS})

add_library (HOAGraphics ${HOAGraphics_SRCS})
target_link_libraries (HOAGraphics ${Qt5Widgets_LIBRARIES} ${Qt5Svg_LIBRARIES} HOASystem)
