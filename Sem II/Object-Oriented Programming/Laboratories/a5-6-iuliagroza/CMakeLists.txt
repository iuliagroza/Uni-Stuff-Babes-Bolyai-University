cmake_minimum_required(VERSION 3.16)
project(a5_6_iuliagroza)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_HEADERS
        domain/Movie.h
        repository/AdminRepository.h
        repository/UserRepository.h
        controller/Controller.h
        ui/UI.h
        utils/DynamicArray.h
        tests/Tests.h
        )
set(PROJECT_SOURCES
        main.cpp
        domain/Movie.cpp
        repository/AdminRepository.cpp
        repository/UserRepository.cpp
        controller/Controller.cpp
        ui/UI.cpp
        tests/Tests.cpp
        )

add_executable(a5_6_iuliagroza ${PROJECT_SOURCES} ${PROJECT_HEADERS})
