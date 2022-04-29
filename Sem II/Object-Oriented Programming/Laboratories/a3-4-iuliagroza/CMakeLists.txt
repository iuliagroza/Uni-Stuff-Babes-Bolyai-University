cmake_minimum_required(VERSION 3.16)
project(a3_4_iuliagroza C)

set(CMAKE_C_STANDARD 99)

set(PROJECT_HEADERS
        domain/Offer.h
        repository/OfferRepo.h
        controller/Controller.h
        ui/Ui.h
        utils/DynamicArray.h
        tests/Tests.h
        undoredo/command.h
        undoredo/memento.h
        )
set(PROJECT_SOURCES
        main.c
        domain/Offer.c
        repository/OfferRepo.c
        controller/Controller.c
        ui/Ui.c
        utils/DynamicArray.c
        tests/Tests.c
        undoredo/command.c
        undoredo/memento.c
        )

add_executable(a3_4_iuliagroza ${PROJECT_SOURCES} ${PROJECT_HEADERS})
