# Add executables
add_library(
	pixel_utility
	interrupt.cpp
	logger.cpp
)

# Set library link targets
target_link_libraries(
	pixel_utility
	pixel_common
)

# Set arduino library link targets
target_link_arduino_libraries(
	pixel_utility
	core
)