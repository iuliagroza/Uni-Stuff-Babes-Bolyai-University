cmake_minimum_required(VERSION 3.17)
project(OOP)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "D:/Qt/6.2.4/mingw_64/lib/cmake")
set(QT_VERSION 6)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets)

add_executable(OOP
        Lectures/Lecture_1/Arrays.c
        Lectures/Lecture_1/Casting.cpp
        Lectures/Lecture_1/CStrings.c
        Lectures/Lecture_1/DataTypes.c
        Lectures/Lecture_1/Functions.cpp
        Lectures/Lecture_1/HelloWorld.cpp
        Lectures/Lecture_1/HelloWorldC.c
        Lectures/Lecture_1/Pointers.c
        Lectures/Lecture_1/ReadWrite.c
        Lectures/Lecture_1/Statements.c
        Lectures/Lecture_1/StructExample.c
        Lectures/Lecture_2/ConstPointers.c
        Lectures/Lecture_2/DynamicArray.h
        Lectures/Lecture_2/DynamicArray.c
        Lectures/Lecture_2/DynamicMemoryManagement.cpp
        Lectures/Lecture_2/DynamicMemoryManagementC.c
        Lectures/Lecture_2/main.c
        Lectures/Lecture_2/NullDanglingPointers.c
        Lectures/Lecture_2/Planet.c
        Lectures/Lecture_2/Planet.h
        Lectures/Lecture_2/PointersToFunctions.c
        Lectures/Lecture_3/c_plus.cpp
        Lectures/Lecture_3/vector_ex1.cpp
        Lectures/Lecture_3/vector_ex2.cpp
        Lectures/Lecture_3/vector_ex3.cpp
        Lectures/Lecture_3/vector_v1/Vector2D.h
        Lectures/Lecture_3/vector_v1/Vector2D.cpp
        Lectures/Lecture_3/vector_v2/Vector2D.h
        Lectures/Lecture_3/vector_v2/Vector2D.cpp
        Lectures/Lecture_3/vector_v3/Vector2D.h
        Lectures/Lecture_3/vector_v3/Vector2D.cpp
        Lectures/Lecture_3/vector_v3/DynamicVector.h
        Lectures/Lecture_3/vector_v3/DynamicVector.cpp
        Lectures/Lecture_4/FunctionTemplate.cpp
        Lectures/Lecture_4/DynamicVector.h
        Lectures/Lecture_4/DynamicVector_demo.cpp
        Lectures/Lecture_4/Pair.h
        Lectures/Lecture_4/stl_demo.cpp
        Lectures/Lecture_5/Animal.h
        Lectures/Lecture_5/Animal.cpp
        Lectures/Lecture_5/Dog.h
        Lectures/Lecture_5/Dog.cpp
        Lectures/Lecture_5/Penguin.h
        Lectures/Lecture_5/Penguin.cpp
        Lectures/Lecture_5/demo.cpp
        Lectures/Lecture_6_abstract_base_class/Animal.h
        Lectures/Lecture_6_abstract_base_class/Animal.cpp
        Lectures/Lecture_6_abstract_base_class/demo.cpp
        Lectures/Lecture_6_abstract_base_class/Dog.h
        Lectures/Lecture_6_abstract_base_class/Dog.cpp
        Lectures/Lecture_6_abstract_base_class/Filter.h
        Lectures/Lecture_6_abstract_base_class/Penguin.h
        Lectures/Lecture_6_abstract_base_class/Penguin.cpp
        Lectures/Lecture_6_abstract_base_class/Zoo.h
        Lectures/Lecture_6_abstract_base_class/Zoo.cpp
        Lectures/Lecture_6_polymorphism/Animal.h
        Lectures/Lecture_6_polymorphism/Animal.cpp
        Lectures/Lecture_6_polymorphism/demo.cpp
        Lectures/Lecture_6_polymorphism/Dog.h
        Lectures/Lecture_6_polymorphism/Dog.cpp
        Lectures/Lecture_6_polymorphism/Penguin.h
        Lectures/Lecture_6_polymorphism/Penguin.cpp
        Lectures/Lecture_7_streams/Animal.h
        Lectures/Lecture_7_streams/Animal.cpp
        Lectures/Lecture_7_streams/main.cpp
        Lectures/Lecture_7_streams/Penguin.h
        Lectures/Lecture_7_streams/Penguin.cpp
        Lectures/Lecture_7_files/main.cpp
        Lectures/Lecture_7_files/Spaceship.h
        Lectures/Lecture_7_files/Spaceship.cpp
        Lectures/Lecture_7_exceptions/main.cpp
        Lectures/Lecture_7_exceptions/Spaceship.h
        Lectures/Lecture_7_exceptions/Spaceship.cpp
        Lectures/Lecture_7_exceptions/SpaceshipValidator.h
        Lectures/Lecture_7_exceptions/SpaceshipValidator.cpp
        Lectures/Lecture_8/hello_world/lecture9_demo_hello_world.h
        Lectures/Lecture_8/hello_world/lecture9_demo_hello_world.cpp
        Lectures/Lecture_8/hello_world/main.cpp
        Lectures/Lecture_8/widgets/lecture9_demo_widgets.h
        Lectures/Lecture_8/widgets/lecture9_demo_widgets.cpp
        Lectures/Lecture_8/widgets/main.cpp
        Lectures/Lecture_8/qt_designer/lecture9_demo_qt_designer.h
        Lectures/Lecture_8/qt_designer/lecture9_demo_qt_designer.cpp
        Lectures/Lecture_8/qt_designer/programaticallydesignedwidget.hpp
        Lectures/Lecture_8/qt_designer/programaticallydesignedwidget.cpp
        Lectures/Lecture_8/qt_designer/main.cpp
        )

file(COPY Lectures/Lecture_10/genes/Ecoli_genes.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Lectures/Lecture_10/genes_custom_model/Ecoli.jpg
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Lectures/Lecture_10/genes_custom_model/Genes.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Lectures/Lecture_10/genes_custom_model/human.jpg
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Lectures/Lecture_12/iterator/chambord.jpg
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Lectures/Lecture_12/iterator/highclere.jpg
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Lectures/Lecture_12/iterator/neuschwanstein.jpg
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Lectures/Lecture_12/iterator/peles.jpg
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Lectures/Lecture_12/iterator/scaliger.jpg
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Lectures/Lecture_12/iterator/windsor.jpg
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})