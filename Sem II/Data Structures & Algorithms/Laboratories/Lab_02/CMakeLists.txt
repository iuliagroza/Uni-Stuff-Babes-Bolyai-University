cmake_minimum_required(VERSION 3.16)
project(Lab-02)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_HEADERS
        ExtendedTest.h
        ListIterator.h
        ShortTest.h
        SortedIndexedList.h
        )
set(PROJECT_SOURCES
        App.cpp
        ExtendedTest.cpp
        ListIterator.cpp
        ShortTest.cpp
        SortedIndexedList.cpp
        )

add_executable(Lab-02 ${PROJECT_SOURCES} ${PROJECT_HEADERS})
