cmake_minimum_required(VERSION 3.2)

project(NumericMethods CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/openglwidget.cpp
    src/openglwidget.h
    src/camera.cpp
    src/camera.h
    src/heatequationsolvergldata.cpp
    src/heatequationsolvergldata.h
    src/boundingbox.cpp
    src/boundingbox.h
)

find_package(OpenGL REQUIRED)
find_package(Qt5 COMPONENTS Core Gui OpenGL REQUIRED)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ${OPENGL_LIBRARIES}
    Qt5::Core
    Qt5::Gui
    Qt5::OpenGL
    parser
    HeatEquationSolver
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${OPENGL_INCLUDE_DIRS}
)

configure_file(res/test.txt test.txt COPYONLY)
configure_file(res/test1.txt test1.txt COPYONLY)
configure_file(res/test2.txt test2.txt COPYONLY)
configure_file(res/test3.txt test3.txt COPYONLY)
configure_file(res/test4.txt test4.txt COPYONLY)
configure_file(res/vert.glsl vert.glsl COPYONLY)
configure_file(res/frag.glsl frag.glsl COPYONLY)
