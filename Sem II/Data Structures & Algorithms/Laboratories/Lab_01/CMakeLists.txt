cmake_minimum_required(VERSION 3.16)
project(Lab_01)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_HEADERS
        ExtendedTest.h
        Matrix.h
        ShortTest.h
        )
set(PROJECT_SOURCES
        App.cpp
        ExtendedTest.cpp
        Matrix.cpp
        ShortTest.cpp
        )

add_executable(Lab_01 ${PROJECT_SOURCES} ${PROJECT_HEADERS})
