
cmake_minimum_required(VERSION 3.26)
project(da2324_p07_sol)
set(CMAKE_CXX_STANDARD 14)

# Build the Google tests
set(GOOGLETEST_PATH lib/googletest)
add_subdirectory(${GOOGLETEST_PATH})
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)

# Add the source files of each TP class
file(GLOB TP7_FILES CONFIGURE_DEPENDS "TP7/*.cpp")

# Create a library for the support data structures
add_executable(TP7 ${TP7_FILES})

# Link the libraries for each TP class executable
target_link_libraries(TP7 gtest_main gmock_main)
