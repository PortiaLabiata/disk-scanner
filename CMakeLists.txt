cmake_minimum_required(VERSION 3.13)
project(disk_scanner VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
        worker.cpp
)
target_compile_options(${PROJECT_NAME}
    PRIVATE
        /W4
)
