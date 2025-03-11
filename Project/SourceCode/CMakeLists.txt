cmake_minimum_required(VERSION 3.26)

# Project name
project(DA_Project)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the source files
set(SOURCES
        main.cpp
        GraphStructure/graph.cpp
        GraphStructure/loadGraph.cpp
        BatchModeReader/batchReader.cpp

)

# Define the header files
set(HEADERS
        GraphStructure/graph.h
        GraphStructure/loadGraph.h
        BatchModeReader/batchReader.h
)

# Include directories
include_directories(
        ${CMAKE_SOURCE_DIR}/GraphStructure
        ${CMAKE_SOURCE_DIR}/BatchModeReader
)

# Create the executable
add_executable(DA_Project ${SOURCES})