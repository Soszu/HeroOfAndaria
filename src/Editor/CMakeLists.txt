set (HOAEditor_SRCS
	main.cpp
	MainWindow.cpp
	ContentEditor.cpp
	ItemEditor.cpp
	CreatureEditor.cpp
)

set (HOAEditor_HDRS
	MainWindow.h
	ContentEditor.h
	CreatureEditor.h
	ItemEditor.h
	Strings.h
	Shortcuts.h
)

qt5_wrap_cpp (HOAEditor_SRCS ${HOAEditor_HDRS})

add_executable (HOAEditor ${HOAEditor_SRCS})
target_link_libraries (HOAEditor ${Qt5Widgets_LIBRARIES} HOASystem)
