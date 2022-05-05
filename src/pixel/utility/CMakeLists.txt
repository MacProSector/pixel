# Add executables
add_library(
	pixel_utility
	logger.cpp
)

# Set arduino library link targets
target_link_arduino_libraries(
	pixel_utility
	core
)