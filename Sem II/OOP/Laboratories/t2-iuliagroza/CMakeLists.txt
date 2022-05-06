cmake_minimum_required(VERSION 3.16)
project(a8_9_iuliagroza)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_HEADERS
        headers/Client.h
        headers/Company.h
        headers/Dwelling.h
        headers/Person.h
        headers/realestate.h
        headers/UI.h
        )
set(PROJECT_SOURCES
        sources/main.cpp
        sources/Client.cpp
        sources/Company.cpp
        sources/Dwelling.cpp
        sources/Person.cpp
        sources/realestate.cpp
        sources/UI.cpp
        )

add_executable(a8_9_iuliagroza ${PROJECT_SOURCES} ${PROJECT_HEADERS})
