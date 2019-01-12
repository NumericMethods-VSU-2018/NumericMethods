cmake_minimum_required(VERSION 3.2)

project(NumericMethods CXX)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_subdirectory(common)
add_subdirectory(GUI)
add_subdirectory(BandMatrix)
add_subdirectory(BorderRules)
add_subdirectory(Gauss)
add_subdirectory(parser)
add_subdirectory(HeatConductivityMatrix)
add_subdirectory(HeatEquationSolver)
