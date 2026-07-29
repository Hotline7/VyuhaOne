cmake_minimum_required(VERSION 3.28)

project(
    VyuhaOne
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#===============================================================================
# Production targets
#===============================================================================

add_subdirectory(engine)
add_subdirectory(apps/uci)

#===============================================================================
# Testing support
#===============================================================================
include(CTest)

if(BUILD_TESTING)
    include(FetchContent)

    FetchContent_Declare(
        googletest
        URL
            https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )

    if(MSVC)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()

    FetchContent_MakeAvailable(googletest)

    add_subdirectory(tests/cpp)
endif()