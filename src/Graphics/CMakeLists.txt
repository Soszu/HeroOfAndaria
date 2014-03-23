set (HOAGraphics_SRCS
	GraphicsBlacksmith.cpp
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
)

set (HOAGraphics_HDRS
	GraphicsMap.h
	GraphicsObject.h
	GraphicsPlace.h
	GraphicsInn.h
	GraphicsBlacksmith.h
	GraphicsTown.h
)

qt5_wrap_cpp (HOAGraphics_SRCS ${HOAGraphics_HDRS})

add_library (HOAGraphics ${HOAGraphics_SRCS})
target_link_libraries (HOAGraphics ${Qt5Widgets_LIBRARIES} HOASystem)
