# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /home/johann/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/171.4073.32/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/johann/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/171.4073.32/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/johann/Work/Othellov2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/johann/Work/Othellov2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Othellov2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Othellov2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Othellov2.dir/flags.make

CMakeFiles/Othellov2.dir/main.cpp.o: CMakeFiles/Othellov2.dir/flags.make
CMakeFiles/Othellov2.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/johann/Work/Othellov2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Othellov2.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Othellov2.dir/main.cpp.o -c /home/johann/Work/Othellov2/main.cpp

CMakeFiles/Othellov2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Othellov2.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/johann/Work/Othellov2/main.cpp > CMakeFiles/Othellov2.dir/main.cpp.i

CMakeFiles/Othellov2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Othellov2.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/johann/Work/Othellov2/main.cpp -o CMakeFiles/Othellov2.dir/main.cpp.s

CMakeFiles/Othellov2.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Othellov2.dir/main.cpp.o.requires

CMakeFiles/Othellov2.dir/main.cpp.o.provides: CMakeFiles/Othellov2.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Othellov2.dir/build.make CMakeFiles/Othellov2.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Othellov2.dir/main.cpp.o.provides

CMakeFiles/Othellov2.dir/main.cpp.o.provides.build: CMakeFiles/Othellov2.dir/main.cpp.o


# Object files for target Othellov2
Othellov2_OBJECTS = \
"CMakeFiles/Othellov2.dir/main.cpp.o"

# External object files for target Othellov2
Othellov2_EXTERNAL_OBJECTS =

Othellov2: CMakeFiles/Othellov2.dir/main.cpp.o
Othellov2: CMakeFiles/Othellov2.dir/build.make
Othellov2: CMakeFiles/Othellov2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/johann/Work/Othellov2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Othellov2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Othellov2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Othellov2.dir/build: Othellov2

.PHONY : CMakeFiles/Othellov2.dir/build

CMakeFiles/Othellov2.dir/requires: CMakeFiles/Othellov2.dir/main.cpp.o.requires

.PHONY : CMakeFiles/Othellov2.dir/requires

CMakeFiles/Othellov2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Othellov2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Othellov2.dir/clean

CMakeFiles/Othellov2.dir/depend:
	cd /home/johann/Work/Othellov2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/johann/Work/Othellov2 /home/johann/Work/Othellov2 /home/johann/Work/Othellov2/cmake-build-debug /home/johann/Work/Othellov2/cmake-build-debug /home/johann/Work/Othellov2/cmake-build-debug/CMakeFiles/Othellov2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Othellov2.dir/depend

