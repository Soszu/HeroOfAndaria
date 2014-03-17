set (HOAGame_SRCS
	main.cpp
	MainWindow.cpp
	Menu.cpp
)

set (HOAGame_HDRS
	MainWindow.h
	Menu.h
)

qt5_wrap_cpp (HOAGame_SRCS ${HOAGame_HDRS})

add_executable (HOAGame ${HOAGame_SRCS})
target_link_libraries (HOAGame ${Qt5Widgets_LIBRARIES} HOAGraphics HOASystem)
