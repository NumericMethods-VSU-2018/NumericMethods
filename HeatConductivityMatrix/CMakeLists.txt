cmake_minimum_required(VERSION 3.9)
project(HeatConductivityMatrix)

set(CMAKE_CXX_STANDARD 11)

add_library(HeatConductivityMatrix include/Point.h include/HeatMatrix.h src/HeatMatrix.cpp src/Point.cpp)