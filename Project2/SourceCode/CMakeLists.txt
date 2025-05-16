cmake_minimum_required(VERSION 3.26)

# Project2 name
project(DA_Project2)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the source files
set(SOURCES
        main.cpp
        DataStructures/loadTruck.cpp
        DataStructures/loadPallets.cpp
        Algorithms/algorithms.cpp
        DisplayResults/displayResults.cpp
)

# Define the header files
set(HEADERS
        DataStructures/truck.h
        DataStructures/pallet.h
        DataStructures/loadTruck.h
        DataStructures/loadPallets.h
        Algorithms/algorithms.h
        DisplayResults/displayResults.h
)

# Include directories
include_directories(
        ${CMAKE_SOURCE_DIR}/
        ${CMAKE_SOURCE_DIR}/DataStructures
        ${CMAKE_SOURCE_DIR}/Algorithms
        ${CMAKE_SOURCE_DIR}/DisplayResults
)

# Create the executable
add_executable(DA_Project ${SOURCES})