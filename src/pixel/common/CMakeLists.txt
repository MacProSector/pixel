# Add executables
add_library(
	pixel_common
	global.cpp
)

# Set arduino library link targets
target_link_arduino_libraries(
	pixel_common
	core
)