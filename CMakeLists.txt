cmake_minimum_required(VERSION 3.26)
project(example_cmake)

set(CMAKE_CXX_STANDARD 23)

add_executable(example_cmake main.cpp)

# Add Catch2
Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

# test registration
include(CTest)
include(Catch)
catch_discover_tests(tests)
