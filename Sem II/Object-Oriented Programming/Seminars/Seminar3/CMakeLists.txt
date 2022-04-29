cmake_minimum_required(VERSION 3.16)
project(Seminar3)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_HEADERS
        Controller.h
        DynamicVector.h
        Repository.h
        Song.h
        Tests.h
        UI.h
        )
set(PROJECT_SOURCES
        main.cpp
        Controller.cpp
        Repository.cpp
        Song.cpp
        Tests.cpp
        UI.cpp
        )

add_executable(Seminar3 ${PROJECT_SOURCES} ${PROJECT_HEADERS})
