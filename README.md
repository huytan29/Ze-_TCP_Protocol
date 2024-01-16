# TCP Socket Example

This is a simple example of a client-server application using the TCP protocol in C++. The project consists of two programs: `client.cpp` and `server.cpp`.

## Prerequisites

- C++ compiler (supporting C++14 or later)
- CMake (minimum version 3.12)
- (For Windows) Visual Studio or GCC
- (For UNIX) GCC or Clang

## Building the Project

1. Download Visual Studio (if using windows) 
+ download Windows SDK
+ download Windows WDK
+ Cmake for Visual Studio
2. Download gcc/g++ (if using Linux)
+ sudo apt-get update && sudo apt-get upgrade
+ sudo apt-get install gcc & g++
3. Build Project
+ mkdir build
+ cd build
+ cmake -G "Visual Studio 17 2022" .. (if Windows Visual Studio)
+ cmake .. (if Msys2 on Windows and Linux)
+ cmake --build .
4. Run
+ server.exe
+ client.exe
