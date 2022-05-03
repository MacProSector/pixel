#!/bin/bash

# Validate operating system
if [[ "$OSTYPE" == "linux-gnu"* ]]
then
	echo "[INFO]: Setting up project for Linux..."
elif [[ "$OSTYPE" == "darwin"* ]]
then
	echo "[INFO]: Setting up project for macOS..."
else
	echo "[ERROR]: Unsupported operating system."
	echo "[ERROR]: Setup failed. Quit."
	exit
fi

# Declare global variables
CORES=$(getconf _NPROCESSORS_ONLN)
ECLIPSE_VERSION=4.23.0
BUILD_TYPE_DEBUG=Debug
BUILD_TYPE_RELEASE=Release

# Declare project variables
PROJECT_NAME=pixel
PROJECT_DIR=$(pwd)/../..
PROJECT_DIR_BUILD=$PROJECT_DIR/build
PROJECT_DIR_BUILD_DEBUG=$PROJECT_DIR_BUILD/$PROJECT_NAME/$(echo $BUILD_TYPE_DEBUG | tr "[:upper:]" "[:lower:]")
PROJECT_DIR_BUILD_RELEASE=$PROJECT_DIR_BUILD/$PROJECT_NAME/$(echo $BUILD_TYPE_RELEASE | tr "[:upper:]" "[:lower:]")
PROJECT_DIR_CMAKE=$PROJECT_DIR/cmake
PROJECT_DIR_CONFIG=$PROJECT_DIR/config
PROJECT_DIR_INSTALL=$PROJECT_DIR/install
PROJECT_DIR_LIB=$PROJECT_DIR/src/$PROJECT_NAME/libraries
PROJECT_DIR_SRC=$PROJECT_DIR/src
PROJECT_DIR_TEMP=/tmp/$PROJECT_NAME

# Declare Arduino IDE variables
ARDUINO_IDE_NAME_LINUX="arduino"
ARDUINO_IDE_NAME_MACOS="Arduino.app"
ARDUINO_IDE_VER_MAJ=1
ARDUINO_IDE_VER_MIN=8
ARDUINO_IDE_VER_PAT=19
ARDUINO_IDE_FILE_LINUX="arduino-$ARDUINO_IDE_VER_MAJ.$ARDUINO_IDE_VER_MIN.$ARDUINO_IDE_VER_PAT-linux64.tar.xz"
ARDUINO_IDE_FILE_MACOS="arduino-$ARDUINO_IDE_VER_MAJ.$ARDUINO_IDE_VER_MIN.$ARDUINO_IDE_VER_PAT-macosx.zip"
ARDUINO_IDE_FILE=$ARDUINO_IDE_FILE_LINUX
ARDUINO_IDE_URL_LINUX="https://downloads.arduino.cc/$ARDUINO_IDE_FILE_LINUX"
ARDUINO_IDE_URL_MACOS="https://downloads.arduino.cc/$ARDUINO_IDE_FILE_MACOS"
ARDUINO_IDE_URL=$ARDUINO_IDE_URL_LINUX
ARDUINO_IDE_DIR_LINUX="arduino-$ARDUINO_IDE_VER_MAJ.$ARDUINO_IDE_VER_MIN.$ARDUINO_IDE_VER_PAT"
ARDUINO_IDE_DIR_MACOS="Arduino.app"
ARDUINO_IDE_DIR=$ARDUINO_IDE_DIR_LINUX
ARDUINO_IDE_DIR_INSTALL_LINUX="/opt/$ARDUINO_IDE_NAME_LINUX"
ARDUINO_IDE_DIR_INSTALL_MACOS="/Applications/$ARDUINO_IDE_NAME_MACOS"
ARDUINO_IDE_DIR_INSTALL=$ARDUINO_IDE_DIR_INSTALL_LINUX

# Declare Arduino CMake Toolchain variables
ARDUINO_CMAKE_TOOLCHAIN_NAME="arduino_cmake_toolchain"
ARDUINO_CMAKE_TOOLCHAIN_VER="a9144ff9f97021f82e62ef144ce00f20b391fde4"
ARDUINO_CMAKE_TOOLCHAIN_VER_SHORT="a9144ff"
ARDUINO_CMAKE_TOOLCHAIN_URL="https://github.com/a9183756-gh/Arduino-CMake-Toolchain.git"
ARDUINO_CMAKE_TOOLCHAIN_DIR="Arduino-CMake-Toolchain"
ARDUINO_CMAKE_TOOLCHAIN_DIR_INSTALL="$PROJECT_DIR_CMAKE/$ARDUINO_CMAKE_TOOLCHAIN_NAME"

# Declare Adafruit NeoPixel variables
ADAFRUIT_NEOPIXEL_NAME="Adafruit_NeoPixel"
ADAFRUIT_NEOPIXEL_VER_MAJ=1
ADAFRUIT_NEOPIXEL_VER_MIN=10
ADAFRUIT_NEOPIXEL_VER_PAT=4
ADAFRUIT_NEOPIXEL_FILE="Adafruit_NeoPixel-$ADAFRUIT_NEOPIXEL_VER_MAJ.$ADAFRUIT_NEOPIXEL_VER_MIN.$ADAFRUIT_NEOPIXEL_VER_PAT.zip"
ADAFRUIT_NEOPIXEL_URL="https://downloads.arduino.cc/libraries/github.com/adafruit/$ADAFRUIT_NEOPIXEL_FILE"
ADAFRUIT_NEOPIXEL_DIR="Adafruit_NeoPixel-$ADAFRUIT_NEOPIXEL_VER_MAJ.$ADAFRUIT_NEOPIXEL_VER_MIN.$ADAFRUIT_NEOPIXEL_VER_PAT"
ADAFRUIT_NEOPIXEL_DIR_INSTALL="$PROJECT_DIR_LIB/$ADAFRUIT_NEOPIXEL_NAME"

# Declare Eigen variables
EIGEN_NAME="Eigen"
EIGEN_VER_MAJ=0
EIGEN_VER_MIN=2
EIGEN_VER_PAT=3
EIGEN_FILE="Eigen-$EIGEN_VER_MAJ.$EIGEN_VER_MIN.$EIGEN_VER_PAT.zip"
EIGEN_URL="https://downloads.arduino.cc/libraries/github.com/hideakitai/$EIGEN_FILE"
EIGEN_DIR="Eigen-$EIGEN_VER_MAJ.$EIGEN_VER_MIN.$EIGEN_VER_PAT"
EIGEN_DIR_INSTALL="$PROJECT_DIR_LIB/$EIGEN_NAME"

# Set OS-specific variables
if [[ "$OSTYPE" == "linux-gnu"* ]]
then
	ARDUINO_IDE_FILE=$ARDUINO_IDE_FILE_LINUX
	ARDUINO_IDE_URL=$ARDUINO_IDE_URL_LINUX
	ARDUINO_IDE_DIR=$ARDUINO_IDE_DIR_LINUX
	ARDUINO_IDE_DIR_INSTALL=$ARDUINO_IDE_DIR_INSTALL_LINUX
elif [[ "$OSTYPE" == "darwin"* ]]
then
	ARDUINO_IDE_FILE=$ARDUINO_IDE_FILE_MACOS
	ARDUINO_IDE_URL=$ARDUINO_IDE_URL_MACOS
	ARDUINO_IDE_DIR=$ARDUINO_IDE_DIR_MACOS
	ARDUINO_IDE_DIR_INSTALL=$ARDUINO_IDE_DIR_INSTALL_MACOS
fi

# Remove existing project temporary directory
if [ -d "$PROJECT_DIR_TEMP" ]
then
	echo "[INFO]: Removing existing project temporary directory..."
	rm -rf "$PROJECT_DIR_TEMP"
fi

# Create project directories
echo "[INFO]: Creating project directories..."
mkdir -p "$PROJECT_DIR_CMAKE"
mkdir -p "$PROJECT_DIR_TEMP"
mkdir -p "$PROJECT_DIR_LIB"
mkdir -p "$PROJECT_DIR_BUILD"

RETURN=$?
if [ $RETURN -ne 0 ]
then
	echo "[ERROR]: Setup failed. Quit."
	exit $RETURN
fi

# Install Arduino IDE
echo "[INFO]: Installing Arduino IDE $ARDUINO_IDE_VER_MAJ.$ARDUINO_IDE_VER_MIN.$ARDUINO_IDE_VER_PAT..."
if [ ! -d "$ARDUINO_IDE_DIR_INSTALL" ]
then
	echo "[INFO]: Downloading Arduino IDE $ARDUINO_IDE_VER_MAJ.$ARDUINO_IDE_VER_MIN.$ARDUINO_IDE_VER_PAT..."
	cd "$PROJECT_DIR_TEMP"
	curl -L --progress-bar "$ARDUINO_IDE_URL" -o "$ARDUINO_IDE_FILE"

	echo "[INFO]: Extracting Arduino IDE $ARDUINO_IDE_VER_MAJ.$ARDUINO_IDE_VER_MIN.$ARDUINO_IDE_VER_PAT..."
	tar -xf "$ARDUINO_IDE_FILE"

	mv "$ARDUINO_IDE_DIR" "$ARDUINO_IDE_DIR_INSTALL"

	RETURN=$?
	if [ $RETURN -ne 0 ]
	then
		echo "[ERROR]: Setup failed. Quit."
		exit $RETURN
	fi
else
	echo "[INFO]: Arduino IDE installation exists. Skip."
fi

# Install Arduino CMake Toolchain
echo "[INFO]: Installing Arduino CMake Toolchain $ARDUINO_CMAKE_TOOLCHAIN_VER_SHORT..."
if [ ! -d "$ARDUINO_CMAKE_TOOLCHAIN_DIR_INSTALL" ]
then
	echo "[INFO]: Downloading Arduino CMake Toolchain $ARDUINO_CMAKE_TOOLCHAIN_VER_SHORT..."
	cd "$PROJECT_DIR_TEMP"
	git clone "$ARDUINO_CMAKE_TOOLCHAIN_URL" "$ARDUINO_CMAKE_TOOLCHAIN_DIR"

	echo "[INFO]: Configuring Arduino CMake Toolchain $ARDUINO_CMAKE_TOOLCHAIN_VER_SHORT..."
	cd "$PROJECT_DIR_TEMP/$ARDUINO_CMAKE_TOOLCHAIN_DIR"
	git fetch origin pull/53/head:pull-53
	git checkout pull-53
	git apply -v "$PROJECT_DIR_CONFIG/$ARDUINO_CMAKE_TOOLCHAIN_NAME/compiler_sdk_path.patch"

	cd "$PROJECT_DIR_TEMP"
	mv "$ARDUINO_CMAKE_TOOLCHAIN_DIR" "$ARDUINO_CMAKE_TOOLCHAIN_DIR_INSTALL"

	RETURN=$?
	if [ $RETURN -ne 0 ]
	then
		echo "[ERROR]: Setup failed. Quit."
		exit $RETURN
	fi
else
	echo "[INFO]: Arduino CMake Toolchain installation exists. Skip."
fi

# Install Adafruit NeoPixel library
echo "[INFO]: Installing Adafruit NeoPixel $ADAFRUIT_NEOPIXEL_VER_MAJ.$ADAFRUIT_NEOPIXEL_VER_MIN.$ADAFRUIT_NEOPIXEL_VER_PAT..."
if [ ! -d "$ADAFRUIT_NEOPIXEL_DIR_INSTALL" ]
then
	echo "[INFO]: Downloading Adafruit NeoPixel $ADAFRUIT_NEOPIXEL_VER_MAJ.$ADAFRUIT_NEOPIXEL_VER_MIN.$ADAFRUIT_NEOPIXEL_VER_PAT..."
	cd "$PROJECT_DIR_TEMP"
	curl -L --progress-bar "$ADAFRUIT_NEOPIXEL_URL" -o "$ADAFRUIT_NEOPIXEL_FILE"

	echo "[INFO]: Extracting Adafruit NeoPixel $ADAFRUIT_NEOPIXEL_VER_MAJ.$ADAFRUIT_NEOPIXEL_VER_MIN.$ADAFRUIT_NEOPIXEL_VER_PAT..."
	tar -xf "$ADAFRUIT_NEOPIXEL_FILE"

	mv "$ADAFRUIT_NEOPIXEL_DIR" "$ADAFRUIT_NEOPIXEL_DIR_INSTALL"

	RETURN=$?
	if [ $RETURN -ne 0 ]
	then
		echo "[ERROR]: Setup failed. Quit."
		exit $RETURN
	fi
else
	echo "[INFO]: Adafruit NeoPixel installation exists. Skip."
fi

# Install Eigen library
echo "[INFO]: Installing Eigen $EIGEN_VER_MAJ.$EIGEN_VER_MIN.$EIGEN_VER_PAT..."
if [ ! -d "$EIGEN_DIR_INSTALL" ]
then
	echo "[INFO]: Downloading Eigen $EIGEN_VER_MAJ.$EIGEN_VER_MIN.$EIGEN_VER_PAT..."
	cd "$PROJECT_DIR_TEMP"
	curl -L --progress-bar "$EIGEN_URL" -o "$EIGEN_FILE"

	echo "[INFO]: Extracting Eigen $EIGEN_VER_MAJ.$EIGEN_VER_MIN.$EIGEN_VER_PAT..."
	tar -xf "$EIGEN_FILE"

	mv "$EIGEN_DIR" "$EIGEN_DIR_INSTALL"

	RETURN=$?
	if [ $RETURN -ne 0 ]
	then
		echo "[ERROR]: Setup failed. Quit."
		exit $RETURN
	fi
else
	echo "[INFO]: Eigen installation exists. Skip."
fi

# Remove temporary folder
if [ -d "$PROJECT_DIR_TEMP" ]
then
	echo "[INFO]: Removing project temporary directory..."
	rm -rf "$PROJECT_DIR_TEMP"
fi

# Create project debug build directory
echo "[INFO]: Creating project debug build directory..."
if [ ! -d "$PROJECT_DIR_BUILD_DEBUG" ]
then
	mkdir -p "$PROJECT_DIR_BUILD_DEBUG"
	cd "$PROJECT_DIR_BUILD_DEBUG"

	cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=$BUILD_TYPE_DEBUG -DCMAKE_ECLIPSE_MAKE_ARGUMENTS=-j$CORES -DCMAKE_ECLIPSE_VERSION=$ECLIPSE_VERSION -DCMAKE_TOOLCHAIN_FILE="$ARDUINO_CMAKE_TOOLCHAIN_DIR_INSTALL/Arduino-toolchain.cmake" -DARDUINO_BOARD_OPTIONS_FILE="$PROJECT_DIR_CMAKE/$PROJECT_NAME/BoardOptions.cmake" "$PROJECT_DIR_SRC/$PROJECT_NAME"

	RETURN=$?
	if [ $RETURN -ne 0 ]
	then
		echo "[ERROR]: Setup failed. Quit."
		exit $RETURN
	fi
else
	echo "[INFO]: Project debug build directory exists. Skip."
fi

# Create project release build directory
echo "[INFO]: Creating project release build directory..."
if [ ! -d "$PROJECT_DIR_BUILD_RELEASE" ]
then
	mkdir -p "$PROJECT_DIR_BUILD_RELEASE"
	cd "$PROJECT_DIR_BUILD_RELEASE"

	cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=$BUILD_TYPE_RELEASE -DCMAKE_ECLIPSE_MAKE_ARGUMENTS=-j$CORES -DCMAKE_ECLIPSE_VERSION=$ECLIPSE_VERSION -DCMAKE_TOOLCHAIN_FILE="$ARDUINO_CMAKE_TOOLCHAIN_DIR_INSTALL/Arduino-toolchain.cmake" -DARDUINO_BOARD_OPTIONS_FILE="$PROJECT_DIR_CMAKE/$PROJECT_NAME/BoardOptions.cmake" "$PROJECT_DIR_SRC/$PROJECT_NAME"

	RETURN=$?
	if [ $RETURN -ne 0 ]
	then
		echo "[ERROR]: Setup failed. Quit."
		exit $RETURN
	fi
else
	echo "[INFO]: Project release build directory exists. Skip."
fi

echo "[INFO]: Setup complete."
