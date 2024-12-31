cmake_minimum_required(VERSION 3.2)

project(BandMatrix CXX)

add_library(${PROJECT_NAME}
    STATIC
    include/BandMatrix.h
    src/BandMatrix.cpp
    include/ReorderMatrix.h
    src/ReorderMatrix.cpp
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_generic_lambdas)
target_link_libraries(${PROJECT_NAME} PUBLIC common)

target_include_directories(${PROJECT_NAME} PUBLIC include)

find_package(cppunit)
if (${CPPUNIT_FOUND})
    add_executable(${PROJECT_NAME}_app
        test/main.cpp
        test/BandMatrixTest.cpp
        test/BandMatrixTest.h
        test/ReorderTest.cpp
        test/ReorderTest.h
    )

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
else()
    message(WARNING "CppUnit not found. Tests will be disabled.")
endif()
