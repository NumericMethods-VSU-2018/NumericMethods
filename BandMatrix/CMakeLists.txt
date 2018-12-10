cmake_minimum_required(VERSION 3.2)

project(BandMatrix CXX)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_library(${PROJECT_NAME}
    SHARED
    include/BandMatrix.h
    src/BandMatrix.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC include)

add_executable(${PROJECT_NAME}_app
    test/main.cpp
    test/BandMatrixTest.cpp
    test/BandMatrixTest.h
)

find_package(cppunit)

target_link_libraries(${PROJECT_NAME}_app
    PRIVATE
    ${PROJECT_NAME}
    ${CPPUNIT_LIBRARIES}
)

target_include_directories(${PROJECT_NAME}_app
    PRIVATE
    test
    ${CPPUNIT_INCLUDE_DIRS}
)
