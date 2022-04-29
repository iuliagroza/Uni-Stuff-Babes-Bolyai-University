cmake_minimum_required(VERSION 3.16)
project(a8_9_iuliagroza)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_HEADERS
        domain/Movie.h
        repository/AdminRepository.h
        repository/UserRepository.h
        repository/CSVUserRepository.h
        repository/HTMLUserRepository.cpp
        controller/Controller.h
        ui/UI.h
        tests/Tests.h
        validators/Validators.h
        validators/Exceptions.h
        )
set(PROJECT_SOURCES
        main.cpp
        domain/Movie.cpp
        repository/AdminRepository.cpp
        repository/UserRepository.cpp
        repository/CSVUserRepository.cpp
        repository/HTMLUserRepository.cpp
        controller/Controller.cpp
        ui/UI.cpp
        tests/Tests.cpp
        validators/Validators.cpp
        validators/Exceptions.cpp
        )

add_executable(a8_9_iuliagroza ${PROJECT_SOURCES} ${PROJECT_HEADERS})
