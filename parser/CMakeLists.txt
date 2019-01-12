cmake_minimum_required(VERSION 3.2)

project(parser CXX)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_library(${PROJECT_NAME}
    STATIC
    include/parser.h
    src/parser.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PUBLIC common)

find_package(cppunit)

if (${CPPUNIT_FOUND})
    add_executable(${PROJECT_NAME}_test
        test/main.cpp
        test/ParserTest.cpp
        test/ParserTest.h
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
