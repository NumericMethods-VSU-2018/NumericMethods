cmake_minimum_required(VERSION 3.2)

project(Gauss)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)

add_library(${PROJECT_NAME}
    include/gausssolver.h
    src/gausssolver.cpp
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Core)
