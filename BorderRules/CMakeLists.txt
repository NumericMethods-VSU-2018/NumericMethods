cmake_minimum_required(VERSION 3.2)

project(BorderRules CXX)

add_library(${PROJECT_NAME}
    STATIC
    include/BorderRules.h
    src/BorderRules.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PUBLIC common)
