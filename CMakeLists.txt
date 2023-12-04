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

# disable creating extra catch targets
set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)

# test registration
include(CTest)
include(Catch)
catch_discover_tests(tests)

function(add_test_incl_memcheck TARGET_NAME)
    # Set default values for SOURCE_FILES and LIBRARIES if not provided
    set(DEFAULT_SOURCE_FILES "")
    set(DEFAULT_LIBRARIES "")

    # Parse the arguments
    cmake_parse_arguments(CREATE_TARGET "" "" "SOURCE_FILES;LIBRARIES" ${ARGN})

    # If SOURCE_FILES or LIBRARIES were not provided, use default values
    if(NOT CREATE_TARGET_SOURCE_FILES)
        set(CREATE_TARGET_SOURCE_FILES ${DEFAULT_SOURCE_FILES})
    endif()

    if(NOT CREATE_TARGET_LIBRARIES)
        set(CREATE_TARGET_LIBRARIES ${DEFAULT_LIBRARIES})
    endif()

    add_executable(${TARGET_NAME}_test
            ${CREATE_TARGET_SOURCE_FILES}
    )
    target_link_libraries(${TARGET_NAME}_test PRIVATE
            Catch2::Catch2WithMain
            ${CREATE_TARGET_LIBRARIES})

    add_test(NAME ${TARGET_NAME}_test COMMAND ${TARGET_NAME}_test)
    add_test(NAME ${TARGET_NAME}_memchecked_test
            COMMAND valgrind
            --error-exitcode=1
            --tool=memcheck
            --leak-check=full
            --errors-for-leak-kinds=definite
            --show-leak-kinds=definite $<TARGET_FILE:${TARGET_NAME}_test>
            WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
endfunction()

add_test_incl_memcheck(tests
    SOURCE_FILES
        tests.cpp
    LIBRARIES
        Catch2::Catch2WithMain
)
