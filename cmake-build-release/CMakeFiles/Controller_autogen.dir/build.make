# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/niyaz/Desktop/MazeCaveGenerator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/niyaz/Desktop/MazeCaveGenerator/cmake-build-release

# Utility rule file for Controller_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/Controller_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Controller_autogen.dir/progress.make

CMakeFiles/Controller_autogen: Controller_autogen/timestamp

Controller_autogen/timestamp: /usr/lib/qt5/bin/moc
Controller_autogen/timestamp: /usr/lib/qt5/bin/uic
Controller_autogen/timestamp: CMakeFiles/Controller_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/mnt/c/Users/niyaz/Desktop/MazeCaveGenerator/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target Controller"
	/usr/bin/cmake -E cmake_autogen /mnt/c/Users/niyaz/Desktop/MazeCaveGenerator/cmake-build-release/CMakeFiles/Controller_autogen.dir/AutogenInfo.json Release
	/usr/bin/cmake -E touch /mnt/c/Users/niyaz/Desktop/MazeCaveGenerator/cmake-build-release/Controller_autogen/timestamp

Controller_autogen: CMakeFiles/Controller_autogen
Controller_autogen: Controller_autogen/timestamp
Controller_autogen: CMakeFiles/Controller_autogen.dir/build.make
.PHONY : Controller_autogen

# Rule to build all files generated by this target.
CMakeFiles/Controller_autogen.dir/build: Controller_autogen
.PHONY : CMakeFiles/Controller_autogen.dir/build

CMakeFiles/Controller_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Controller_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Controller_autogen.dir/clean

CMakeFiles/Controller_autogen.dir/depend:
	cd /mnt/c/Users/niyaz/Desktop/MazeCaveGenerator/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/niyaz/Desktop/MazeCaveGenerator /mnt/c/Users/niyaz/Desktop/MazeCaveGenerator /mnt/c/Users/niyaz/Desktop/MazeCaveGenerator/cmake-build-release /mnt/c/Users/niyaz/Desktop/MazeCaveGenerator/cmake-build-release /mnt/c/Users/niyaz/Desktop/MazeCaveGenerator/cmake-build-release/CMakeFiles/Controller_autogen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Controller_autogen.dir/depend

