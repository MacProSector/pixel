# Set global parameters
cmake_minimum_required(VERSION 3.7.0)
project(pixel)

# Disable compiler built-in include directory filtering
unset(CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES)
unset(CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES)

# Set installation paths
string(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_PATH)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../../install/${CMAKE_PROJECT_NAME}/${CMAKE_BUILD_TYPE_PATH}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../../install/${CMAKE_PROJECT_NAME}/${CMAKE_BUILD_TYPE_PATH}/lib)

# Set library parameters
set(ADAFRUIT_NEOPIXEL_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/libraries/Adafruit_NeoPixel)
set(EIGEN_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/libraries/Eigen)

# Set include directories
include_directories(
	${CMAKE_SOURCE_DIR}
	${CMAKE_BINARY_DIR}
	${ARDUINO_BOARD_COMPILER_SDK_PATH}/include/freertos/include
	${ARDUINO_BOARD_COMPILER_SDK_PATH}/include/freertos/port/xtensa/include
	${ADAFRUIT_NEOPIXEL_INCLUDE_DIRS}
	${EIGEN_INCLUDE_DIRS}
)

# Add subdirectories
add_subdirectory(applications)
add_subdirectory(buttons)
add_subdirectory(display)
add_subdirectory(logger)
add_subdirectory(main)
