cmake_minimum_required(VERSION 3.26)

# Project name
project(DA_Project)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the source files
set(SOURCES
        main.cpp
)

# Define the header files
set(HEADERS
        Graph.h
        loadGraph.h
)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/Code)

# Create the executable
add_executable(DA_Project ${SOURCES} ${HEADERS})