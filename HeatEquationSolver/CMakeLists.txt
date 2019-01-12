cmake_minimum_required(VERSION 3.2)

project(HeatEquationSolver CXX)

add_library(${PROJECT_NAME}
    STATIC
    src/heatequationsolver.cpp
    include/heatequationsolver.h
)

target_include_directories(${PROJECT_NAME} PUBLIC include)

find_package(OpenGL REQUIRED)
find_package(Qt5 COMPONENTS Core Gui REQUIRED)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    BandMatrix
    HeatConductivityMatrix
    Gauss
    BorderRules
    PUBLIC
    Qt5::Core
    Qt5::Gui
    common
    parser
)

find_package(cppunit)

if (${CPPUNIT_FOUND})
    add_executable(${PROJECT_NAME}_test
        test/main.cpp
        test/SolverTest.cpp
        test/SolverTest.h
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
