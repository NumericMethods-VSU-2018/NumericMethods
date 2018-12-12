cmake_minimum_required(VERSION 3.2)

project(NumericMethods CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

add_executable(${PROJECT_NAME}
    main.cpp
    mainwindow.cpp
    openglwidget.cpp
    heatequationsolver.cpp
    camera.cpp
    heatequationsolvergldata.cpp
    boundingbox.cpp
    mainwindow.h
    openglwidget.h
    heatequationsolver.h
    camera.h
    heatequationsolvergldata.h
    boundingbox.h

)

find_package(OpenGL REQUIRED)
find_package(Qt5 COMPONENTS Core Gui OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ${OPENGL_LIBRARIES}
    Qt5::Core
    Qt5::Gui
    Qt5::OpenGL
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${OPENGL_INCLUDE_DIRS}
)

configure_file(test.txt test.txt COPYONLY)
configure_file(vert.glsl vert.glsl COPYONLY)
configure_file(frag.glsl frag.glsl COPYONLY)
