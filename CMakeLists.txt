cmake_minimum_required(VERSION 3.13)
project(disk_scanner VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)

if (NOT MSVC)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 
endif()

set(RAYLIB_VERSION 6.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
        raylib
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_MakeAvailable(raylib)
    endif()
endif()

include(cmake/imgui.cmake)
include(cmake/rlimgui.cmake)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
        worker.cpp
        gui.cpp
)

if (MSVC)
    target_compile_options(${PROJECT_NAME}
        PRIVATE
            /W4
    )
else()
    target_compile_options(${PROJECT_NAME}
        PRIVATE
            -Wall -Wextra -Wpedantic
    )
endif()

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        rlimgui
)
