# Pixel

## Table of Contents

1. [Prerequisites](#prerequisites)
2. [Cloning the Project](#cloning-the-project)
3. [Setting Up the Project](#setting-up-the-project)
4. [Building the Project](#building-the-project)
5. [Uploading the Project](#uploading-the-project)
6. [Developing the Project](#developing-the-project)

## Prerequisites

Ensure the following prerequisites are present or satisfied:

* Kano Pixel Kit (retail version).
* Linux operating system.
* macOS operating system.
* Essential tools.
  - `cmake` (3.7.0 or higher)
  - `curl`
  - `git`
  - `grep`
  - `make`
  - `tar`

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

## Developing the Project

The Eclipse IDE for C++ is recommended for the development of the project.

With the project built, set up the project with Eclipse IDE as follows:

1. Go to `File->Import->General->Existing Projects into Workspace`.
2. Click `Browse...` to the right to `Select root directory:`.
3. Select `build/pixel/release` or `build/pixel/debug`.
4. Click `Finish`.

A Doxygen configuration is also provided for the project.

Under the project directory, generate the Doxygen documentation as follows:

```bash
doxygen doc/Doxyfile
```

The generated Doxygen documentation would be under `doc/html`.
