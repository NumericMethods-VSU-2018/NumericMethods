cmake_minimum_required(VERSION 3.2)

project(common CXX)

add_library(${PROJECT_NAME}
    SHARED
    include/common.h
    src/common.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC include)