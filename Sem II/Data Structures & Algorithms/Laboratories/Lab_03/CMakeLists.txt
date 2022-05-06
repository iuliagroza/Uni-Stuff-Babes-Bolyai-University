cmake_minimum_required(VERSION 3.16)
project(Lab-03)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_HEADERS
        ExtendedTest.h
        MultiMap.h
        MultiMapIterator.h
        ShortTest.h
        )
set(PROJECT_SOURCES
        App.cpp
        ExtendedTest.cpp
        MultiMap.cpp
        MultiMapIterator.cpp
        ShortTest.cpp
        )

add_executable(Lab-03 ${PROJECT_SOURCES} ${PROJECT_HEADERS})
