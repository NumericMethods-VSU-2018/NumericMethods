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
    Qt5::Core
    Qt5::Gui
    BandMatrix
    HeatConductivityMatrix
    Gauss
    BorderRules
    parser
)