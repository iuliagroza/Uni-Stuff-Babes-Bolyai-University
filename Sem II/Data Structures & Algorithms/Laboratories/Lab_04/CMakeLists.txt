cmake_minimum_required(VERSION 3.16)
project(Lab-04)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_HEADERS
        ExtendedTest.h
        ShortTest.h
        SortedBag.h
        SortedBagIterator.h
        )
set(PROJECT_SOURCES
        App.cpp
        ExtendedTest.cpp
        ShortTest.cpp
        SortedBag.cpp
        SortedBagIterator.cpp
        )

add_executable(Lab-04 ${PROJECT_SOURCES} ${PROJECT_HEADERS})
