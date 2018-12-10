project(BandMatrix CXX)

cmake_minimum_required(VERSION 3.2)

add_library(${PROJECT_NAME}
    SHARED
    include/BandMatrix.h
    src/BandMatrix.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC include)

add_executable(${PROJECT_NAME}_app
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME}_app ${PROJECT_NAME})