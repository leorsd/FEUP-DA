cmake_minimum_required(VERSION 3.26)

# Project1 name
project(DA_Project)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the source files
set(SOURCES
        main.cpp
        GraphStructure/graph.cpp
        GraphStructure/loadGraph.cpp
        GraphStructure/mutablePriorityQueue.cpp
        BatchMode/batch.cpp
        MenuMode/menu.cpp
        Algorithms/algorithms.cpp
        DisplayOutput/displayBatch.cpp
        DisplayOutput/displayMenu.cpp
)

# Define the header files
set(HEADERS
        GraphStructure/graph.h
        GraphStructure/loadGraph.h
        GraphStructure/mutablePriorityQueue.h
        BatchMode/batch.h
        MenuMode/menu.h
        Algorithms/algorithms.h
        DisplayOutput/displayBatch.h
        DisplayOutput/displayMenu.h
)

# Include directories
include_directories(
        ${CMAKE_SOURCE_DIR}/GraphStructure
        ${CMAKE_SOURCE_DIR}/BatchMode
        ${CMAKE_SOURCE_DIR}/MenuMode
        ${CMAKE_SOURCE_DIR}/Algorithms
        ${CMAKE_SOURCE_DIR}/DisplayOutput
)

# Create the executable
add_executable(DA_Project ${SOURCES})