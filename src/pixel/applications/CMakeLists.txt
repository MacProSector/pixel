# Add executables
add_library(
	pixel_applications
	application.cpp
	brightness.cpp
	launchpad.cpp
	point.cpp
	restart.cpp
)

# Set library link targets
target_link_libraries(
	pixel_applications
	pixel_buttons
	pixel_display
	pixel_logger
)

# Set arduino library link targets
target_link_arduino_libraries(
	pixel_applications
	core
)