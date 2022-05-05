# Add executables
add_library(
	pixel_application
	application.cpp
	brightness.cpp
	launchpad.cpp
	point.cpp
	restart.cpp
)

# Set library link targets
target_link_libraries(
	pixel_application
	pixel_button
	pixel_display
	pixel_utility
)

# Set arduino library link targets
target_link_arduino_libraries(
	pixel_application
	core
)