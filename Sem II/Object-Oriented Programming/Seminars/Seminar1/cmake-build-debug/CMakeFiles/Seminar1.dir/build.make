# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/mnt/d/Moveable-Personal/CS Work/College/Facultate/Sem II/OOP/Seminars/Seminar1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/d/Moveable-Personal/CS Work/College/Facultate/Sem II/OOP/Seminars/Seminar1/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Seminar1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Seminar1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Seminar1.dir/flags.make

CMakeFiles/Seminar1.dir/main.c.o: CMakeFiles/Seminar1.dir/flags.make
CMakeFiles/Seminar1.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/d/Moveable-Personal/CS Work/College/Facultate/Sem II/OOP/Seminars/Seminar1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Seminar1.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Seminar1.dir/main.c.o   -c "/mnt/d/Moveable-Personal/CS Work/College/Facultate/Sem II/OOP/Seminars/Seminar1/main.c"

CMakeFiles/Seminar1.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Seminar1.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/mnt/d/Moveable-Personal/CS Work/College/Facultate/Sem II/OOP/Seminars/Seminar1/main.c" > CMakeFiles/Seminar1.dir/main.c.i

CMakeFiles/Seminar1.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Seminar1.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/mnt/d/Moveable-Personal/CS Work/College/Facultate/Sem II/OOP/Seminars/Seminar1/main.c" -o CMakeFiles/Seminar1.dir/main.c.s

# Object files for target Seminar1
Seminar1_OBJECTS = \
"CMakeFiles/Seminar1.dir/main.c.o"

# External object files for target Seminar1
Seminar1_EXTERNAL_OBJECTS =

Seminar1: CMakeFiles/Seminar1.dir/main.c.o
Seminar1: CMakeFiles/Seminar1.dir/build.make
Seminar1: CMakeFiles/Seminar1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/d/Moveable-Personal/CS Work/College/Facultate/Sem II/OOP/Seminars/Seminar1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Seminar1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Seminar1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Seminar1.dir/build: Seminar1

.PHONY : CMakeFiles/Seminar1.dir/build

CMakeFiles/Seminar1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Seminar1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Seminar1.dir/clean

CMakeFiles/Seminar1.dir/depend:
	cd "/mnt/d/Moveable-Personal/CS Work/College/Facultate/Sem II/OOP/Seminars/Seminar1/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/d/Moveable-Personal/CS Work/College/Facultate/Sem II/OOP/Seminars/Seminar1" "/mnt/d/Moveable-Personal/CS Work/College/Facultate/Sem II/OOP/Seminars/Seminar1" "/mnt/d/Moveable-Personal/CS Work/College/Facultate/Sem II/OOP/Seminars/Seminar1/cmake-build-debug" "/mnt/d/Moveable-Personal/CS Work/College/Facultate/Sem II/OOP/Seminars/Seminar1/cmake-build-debug" "/mnt/d/Moveable-Personal/CS Work/College/Facultate/Sem II/OOP/Seminars/Seminar1/cmake-build-debug/CMakeFiles/Seminar1.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Seminar1.dir/depend
