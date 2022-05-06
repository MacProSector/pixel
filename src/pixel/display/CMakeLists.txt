# Add executables
add_library(
	pixel_display
	display.cpp
)

# Set library link targets
target_link_libraries(
	pixel_display
	pixel_common
)

# Set arduino library link targets
target_link_arduino_libraries(
	pixel_display
	core
	Adafruit_NeoPixel
)