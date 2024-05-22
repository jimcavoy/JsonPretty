# JsonPretty
__JsonPretty__ is a console application that will pretty-print a json file to standard console output.
Most of the code is attributed to the Boost JSON __Pretty__ example code, 
https://www.boost.org/doc/libs/1_84_0/libs/json/doc/html/json/examples.html#json.examples.pretty

## Usage

### 1. Read a file
    JsonPretty <jsonfile> > pretty.json

### 2. Pipe input
    SomeApp | JsonPretty > pretty.json

## Prerequisites
This project requires the following:

1. Install CMake, https://cmake.org/
2. Install and configure vcpkg, https://github.com/microsoft/vcpkg, which is a packet management system.  If Visual Studio 2022 is installed, __vcpkg__ maybe already installed.
3. Configure `VCPKG_ROOT` environment variable to the path where you installed __vcpkg__.  If Visual Studio 2022 is installed, this environment variable maybe already set.

## To Build and Install
In __JsonPretty__ root directory, build and install this project using CMake with the following commmands on a terminal:

### 1. Generate the build environment
    cmake --preset=<windows-base|linux-base>

For Windows platform, use `window-base` and for Linux platform use `linux-base` preset.

### 2. Build the library and test application
    cmake --build ./build

### 3. Install the JsonPretty application
    cmake --install ./build

Add additional CMake parameters as required depending on your host development envirnoment.

## Run Test
To run the projects build-in test, enter the following:

    ctest --test-dir ./build
