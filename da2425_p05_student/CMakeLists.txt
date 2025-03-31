
cmake_minimum_required(VERSION 3.26)
project(da2324_p05_sol)
set(CMAKE_CXX_STANDARD 14)

# Build the Google tests
set(GOOGLETEST_PATH lib/googletest)
add_subdirectory(${GOOGLETEST_PATH})
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)

# Add the source files of each TP class
file(GLOB DATA_STRUCTURES_FILES CONFIGURE_DEPENDS "data_structures/*.h" "data_structures/*.cpp")
file(GLOB TP5_FILES CONFIGURE_DEPENDS "TP5/*.cpp")

# Create a library for the support data structures
add_library(DATA_STRUCTURES ${DATA_STRUCTURES_FILES})
add_executable(TP5 ${TP5_FILES})

# Link the libraries for each TP class executable
target_link_libraries(TP5 DATA_STRUCTURES gtest_main gmock_main)
