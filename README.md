# Pixel

## Table of Contents

1. [Prerequisites](#prerequisites)
2. [Cloning the Project](#cloning-the-project)
3. [Setting Up the Project](#setting-up-the-project)
4. [Building the Project](#building-the-project)
5. [Uploading the Project](#uploading-the-project)

## Prerequisites

* Kano Pixel Kit (retail version).
* Linux operating system.
* macOS operating system.
* Essential toolchain packages.
  - cmake (3.7.0 or higher)
  - curl
  - git
  - grep
  - make
  - tar

## Cloning the Project

Clone the project as follows:

```bash
git clone https://github.com/MacProSector/pixel.git
```

Ensure the project folder and its sub-directories and files all have write access.

## Setting Up the Project

With the project clone and prerequisites installed, set up the project as follows:

```bash
cd scripts/pixel
./setup.bash
```

The script automatically sets up the project by first installing all necessary tools and libraries. Then, the script creates the `build` directory containing two CMake build projects, `build/pixel/debug` and `build/pixel/release`, respectively.

Always run `setup.bash` under `scripts/pixel`. If everything was set up successfully, the script exits and prints `[INFO]: Setup complete.`

## Building the Project

With the project set up, build the project as follows:

```bash
cd build/pixel/release
make
```

If needed, build the debug project as follows:

```bash
cd build/pixel/debug
make
```

The compiled project libraries are available in `install/pixel/release/lib` and `install/pixel/debug/lib`, respectively.

## Uploading the Project

With the project built and the Kano Pixel Kit plugged in and powered on, upload the project as follows:

```bash
cd build/pixel/release
make upload SERIAL_PORT=<device>
```

If needed, upload the debug project as follows:

```bash
cd build/pixel/debug
make upload SERIAL_PORT=<device>
```