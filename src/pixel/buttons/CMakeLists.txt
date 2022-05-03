# Add executables
add_library(
	pixel_buttons
	buttons.cpp
)

# Set arduino library link targets
target_link_arduino_libraries(
	pixel_buttons
	core
)