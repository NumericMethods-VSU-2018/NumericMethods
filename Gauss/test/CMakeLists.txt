CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

PROJECT(Gauss_test
        LANGUAGES CXX)


find_package(Qt5Test)

if (Qt5Test_FOUND)
    SET(CMAKE_AUTOMOC ON)
    SET(CMAKE_INCLUDE_CURRENT_DIR ON)
    SET(CMAKE_CXX_STANDARD 11)
    SET(CMAKE_CXX_STANDARD_REQUIRED ON)
    ENABLE_TESTING()

    add_executable(${PROJECT_NAME}
        tst_gausstests.h
        tst_gausstests.cpp
    )
    add_test(${PROJECT_NAME} COMMAND ${PROJECT_NAME})

    target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Test)
else()
    message(WARNING "Qt5Test is not found. Tests will be disabled.")
endif()

