# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Apps Setup\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Apps Setup\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/a5_6_iuliagroza.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/a5_6_iuliagroza.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/a5_6_iuliagroza.dir/flags.make

CMakeFiles/a5_6_iuliagroza.dir/main.cpp.obj: CMakeFiles/a5_6_iuliagroza.dir/flags.make
CMakeFiles/a5_6_iuliagroza.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/a5_6_iuliagroza.dir/main.cpp.obj"
	"D:\Apps Setup\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\a5_6_iuliagroza.dir\main.cpp.obj -c "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\main.cpp"

CMakeFiles/a5_6_iuliagroza.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a5_6_iuliagroza.dir/main.cpp.i"
	"D:\Apps Setup\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\main.cpp" > CMakeFiles\a5_6_iuliagroza.dir\main.cpp.i

CMakeFiles/a5_6_iuliagroza.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a5_6_iuliagroza.dir/main.cpp.s"
	"D:\Apps Setup\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\main.cpp" -o CMakeFiles\a5_6_iuliagroza.dir\main.cpp.s

CMakeFiles/a5_6_iuliagroza.dir/domain/Movie.cpp.obj: CMakeFiles/a5_6_iuliagroza.dir/flags.make
CMakeFiles/a5_6_iuliagroza.dir/domain/Movie.cpp.obj: ../domain/Movie.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/a5_6_iuliagroza.dir/domain/Movie.cpp.obj"
	"D:\Apps Setup\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\a5_6_iuliagroza.dir\domain\Movie.cpp.obj -c "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\domain\Movie.cpp"

CMakeFiles/a5_6_iuliagroza.dir/domain/Movie.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a5_6_iuliagroza.dir/domain/Movie.cpp.i"
	"D:\Apps Setup\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\domain\Movie.cpp" > CMakeFiles\a5_6_iuliagroza.dir\domain\Movie.cpp.i

CMakeFiles/a5_6_iuliagroza.dir/domain/Movie.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a5_6_iuliagroza.dir/domain/Movie.cpp.s"
	"D:\Apps Setup\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\domain\Movie.cpp" -o CMakeFiles\a5_6_iuliagroza.dir\domain\Movie.cpp.s

CMakeFiles/a5_6_iuliagroza.dir/repository/AdminRepository.cpp.obj: CMakeFiles/a5_6_iuliagroza.dir/flags.make
CMakeFiles/a5_6_iuliagroza.dir/repository/AdminRepository.cpp.obj: ../repository/AdminRepository.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/a5_6_iuliagroza.dir/repository/AdminRepository.cpp.obj"
	"D:\Apps Setup\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\a5_6_iuliagroza.dir\repository\AdminRepository.cpp.obj -c "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\repository\AdminRepository.cpp"

CMakeFiles/a5_6_iuliagroza.dir/repository/AdminRepository.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a5_6_iuliagroza.dir/repository/AdminRepository.cpp.i"
	"D:\Apps Setup\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\repository\AdminRepository.cpp" > CMakeFiles\a5_6_iuliagroza.dir\repository\AdminRepository.cpp.i

CMakeFiles/a5_6_iuliagroza.dir/repository/AdminRepository.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a5_6_iuliagroza.dir/repository/AdminRepository.cpp.s"
	"D:\Apps Setup\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\repository\AdminRepository.cpp" -o CMakeFiles\a5_6_iuliagroza.dir\repository\AdminRepository.cpp.s

CMakeFiles/a5_6_iuliagroza.dir/repository/UserRepository.cpp.obj: CMakeFiles/a5_6_iuliagroza.dir/flags.make
CMakeFiles/a5_6_iuliagroza.dir/repository/UserRepository.cpp.obj: ../repository/UserRepository.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/a5_6_iuliagroza.dir/repository/UserRepository.cpp.obj"
	"D:\Apps Setup\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\a5_6_iuliagroza.dir\repository\UserRepository.cpp.obj -c "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\repository\UserRepository.cpp"

CMakeFiles/a5_6_iuliagroza.dir/repository/UserRepository.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a5_6_iuliagroza.dir/repository/UserRepository.cpp.i"
	"D:\Apps Setup\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\repository\UserRepository.cpp" > CMakeFiles\a5_6_iuliagroza.dir\repository\UserRepository.cpp.i

CMakeFiles/a5_6_iuliagroza.dir/repository/UserRepository.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a5_6_iuliagroza.dir/repository/UserRepository.cpp.s"
	"D:\Apps Setup\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\repository\UserRepository.cpp" -o CMakeFiles\a5_6_iuliagroza.dir\repository\UserRepository.cpp.s

CMakeFiles/a5_6_iuliagroza.dir/controller/Controller.cpp.obj: CMakeFiles/a5_6_iuliagroza.dir/flags.make
CMakeFiles/a5_6_iuliagroza.dir/controller/Controller.cpp.obj: ../controller/Controller.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/a5_6_iuliagroza.dir/controller/Controller.cpp.obj"
	"D:\Apps Setup\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\a5_6_iuliagroza.dir\controller\Controller.cpp.obj -c "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\controller\Controller.cpp"

CMakeFiles/a5_6_iuliagroza.dir/controller/Controller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a5_6_iuliagroza.dir/controller/Controller.cpp.i"
	"D:\Apps Setup\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\controller\Controller.cpp" > CMakeFiles\a5_6_iuliagroza.dir\controller\Controller.cpp.i

CMakeFiles/a5_6_iuliagroza.dir/controller/Controller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a5_6_iuliagroza.dir/controller/Controller.cpp.s"
	"D:\Apps Setup\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\controller\Controller.cpp" -o CMakeFiles\a5_6_iuliagroza.dir\controller\Controller.cpp.s

CMakeFiles/a5_6_iuliagroza.dir/ui/UI.cpp.obj: CMakeFiles/a5_6_iuliagroza.dir/flags.make
CMakeFiles/a5_6_iuliagroza.dir/ui/UI.cpp.obj: ../ui/UI.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/a5_6_iuliagroza.dir/ui/UI.cpp.obj"
	"D:\Apps Setup\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\a5_6_iuliagroza.dir\ui\UI.cpp.obj -c "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\ui\UI.cpp"

CMakeFiles/a5_6_iuliagroza.dir/ui/UI.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a5_6_iuliagroza.dir/ui/UI.cpp.i"
	"D:\Apps Setup\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\ui\UI.cpp" > CMakeFiles\a5_6_iuliagroza.dir\ui\UI.cpp.i

CMakeFiles/a5_6_iuliagroza.dir/ui/UI.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a5_6_iuliagroza.dir/ui/UI.cpp.s"
	"D:\Apps Setup\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\ui\UI.cpp" -o CMakeFiles\a5_6_iuliagroza.dir\ui\UI.cpp.s

CMakeFiles/a5_6_iuliagroza.dir/tests/Tests.cpp.obj: CMakeFiles/a5_6_iuliagroza.dir/flags.make
CMakeFiles/a5_6_iuliagroza.dir/tests/Tests.cpp.obj: ../tests/Tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/a5_6_iuliagroza.dir/tests/Tests.cpp.obj"
	"D:\Apps Setup\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\a5_6_iuliagroza.dir\tests\Tests.cpp.obj -c "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\tests\Tests.cpp"

CMakeFiles/a5_6_iuliagroza.dir/tests/Tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a5_6_iuliagroza.dir/tests/Tests.cpp.i"
	"D:\Apps Setup\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\tests\Tests.cpp" > CMakeFiles\a5_6_iuliagroza.dir\tests\Tests.cpp.i

CMakeFiles/a5_6_iuliagroza.dir/tests/Tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a5_6_iuliagroza.dir/tests/Tests.cpp.s"
	"D:\Apps Setup\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\tests\Tests.cpp" -o CMakeFiles\a5_6_iuliagroza.dir\tests\Tests.cpp.s

# Object files for target a5_6_iuliagroza
a5_6_iuliagroza_OBJECTS = \
"CMakeFiles/a5_6_iuliagroza.dir/main.cpp.obj" \
"CMakeFiles/a5_6_iuliagroza.dir/domain/Movie.cpp.obj" \
"CMakeFiles/a5_6_iuliagroza.dir/repository/AdminRepository.cpp.obj" \
"CMakeFiles/a5_6_iuliagroza.dir/repository/UserRepository.cpp.obj" \
"CMakeFiles/a5_6_iuliagroza.dir/controller/Controller.cpp.obj" \
"CMakeFiles/a5_6_iuliagroza.dir/ui/UI.cpp.obj" \
"CMakeFiles/a5_6_iuliagroza.dir/tests/Tests.cpp.obj"

# External object files for target a5_6_iuliagroza
a5_6_iuliagroza_EXTERNAL_OBJECTS =

a5_6_iuliagroza.exe: CMakeFiles/a5_6_iuliagroza.dir/main.cpp.obj
a5_6_iuliagroza.exe: CMakeFiles/a5_6_iuliagroza.dir/domain/Movie.cpp.obj
a5_6_iuliagroza.exe: CMakeFiles/a5_6_iuliagroza.dir/repository/AdminRepository.cpp.obj
a5_6_iuliagroza.exe: CMakeFiles/a5_6_iuliagroza.dir/repository/UserRepository.cpp.obj
a5_6_iuliagroza.exe: CMakeFiles/a5_6_iuliagroza.dir/controller/Controller.cpp.obj
a5_6_iuliagroza.exe: CMakeFiles/a5_6_iuliagroza.dir/ui/UI.cpp.obj
a5_6_iuliagroza.exe: CMakeFiles/a5_6_iuliagroza.dir/tests/Tests.cpp.obj
a5_6_iuliagroza.exe: CMakeFiles/a5_6_iuliagroza.dir/build.make
a5_6_iuliagroza.exe: CMakeFiles/a5_6_iuliagroza.dir/linklibs.rsp
a5_6_iuliagroza.exe: CMakeFiles/a5_6_iuliagroza.dir/objects1.rsp
a5_6_iuliagroza.exe: CMakeFiles/a5_6_iuliagroza.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable a5_6_iuliagroza.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\a5_6_iuliagroza.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/a5_6_iuliagroza.dir/build: a5_6_iuliagroza.exe
.PHONY : CMakeFiles/a5_6_iuliagroza.dir/build

CMakeFiles/a5_6_iuliagroza.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\a5_6_iuliagroza.dir\cmake_clean.cmake
.PHONY : CMakeFiles/a5_6_iuliagroza.dir/clean

CMakeFiles/a5_6_iuliagroza.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza" "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza" "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\cmake-build-debug" "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\cmake-build-debug" "D:\Moveable-Personal\CS Work\College\Facultate\Sem II\OOP\Laboratories\a5-6-iuliagroza\cmake-build-debug\CMakeFiles\a5_6_iuliagroza.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/a5_6_iuliagroza.dir/depend

