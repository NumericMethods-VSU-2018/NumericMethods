cmake_minimum_required(VERSION 3.9)
project(HeatConductivityMatrix)

set(CMAKE_CXX_STANDARD 11)

add_library(${PROJECT_NAME}
    STATIC
    include/Point.h
    include/HeatMatrix.h
    src/HeatMatrix.cpp
    src/Point.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PUBLIC common)
