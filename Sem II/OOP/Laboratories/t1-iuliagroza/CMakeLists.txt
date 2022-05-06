cmake_minimum_required(VERSION 3.16)
project(t1_iuliagroza)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_HEADERS
        domain/Bill.h
        repository/Repository.h
        controller/Controller.h
        ui/UI.h
        utils/DynamicArray.h
        tests/Tests.h
        )
set(PROJECT_SOURCES
        main.cpp
        domain/Bill.cpp
        repository/Repository.cpp
        controller/Controller.cpp
        ui/UI.cpp
        tests/Tests.cpp
        )

add_executable(t1_iuliagroza ${PROJECT_SOURCES} ${PROJECT_HEADERS})