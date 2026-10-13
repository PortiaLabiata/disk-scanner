cmake_minimum_required(VERSION 3.13)
project(disk_scanner VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
)
target_compile_options(${PROJECT_NAME}
    PRIVATE
        /W4
)
