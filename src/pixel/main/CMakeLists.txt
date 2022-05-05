# Add executables
add_executable(
	pixel
	pixel.cpp
)

# Set library link targets
target_link_libraries(
	pixel PRIVATE
	pixel_application
	pixel_buttons
	pixel_display
	pixel_logger
)

# Set arduino library link targets
target_link_arduino_libraries(
	pixel PRIVATE
	core
	Adafruit_NeoPixel
)

# Set arduino upload targets
target_enable_arduino_upload(pixel)
