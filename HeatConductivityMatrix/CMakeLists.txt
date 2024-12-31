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

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PUBLIC common)

find_package(cppunit)

if (${CPPUNIT_FOUND})
    add_executable(${PROJECT_NAME}_test
        test/main.cpp
        test/HeatTest.cpp
        test/HeatTest.h
    )

    target_link_libraries(${PROJECT_NAME}_test
        PRIVATE
        ${PROJECT_NAME}
        ${CPPUNIT_LIBRARIES}
    )

    target_include_directories(${PROJECT_NAME}_test
        PRIVATE
        test
        ${CPPUNIT_INCLUDE_DIRS}
    )
else()
    message(WARNING "CppUnit not found. Tests will be disabled.")
endif()
