# Add executables
add_library(
	pixel_button
	button.cpp
)

# Set arduino library link targets
target_link_arduino_libraries(
	pixel_button
	core
)