# Add executables
add_library(
	pixel_logger
	logger.cpp
)

# Set arduino library link targets
target_link_arduino_libraries(
	pixel_logger
	core
)