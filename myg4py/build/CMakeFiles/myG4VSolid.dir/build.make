# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/keith/FreeCAD_Geant4/myg4py

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/keith/FreeCAD_Geant4/myg4py/build

# Include any dependencies generated for this target.
include CMakeFiles/myG4VSolid.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/myG4VSolid.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/myG4VSolid.dir/flags.make

CMakeFiles/myG4VSolid.dir/myG4VSolid.cc.o: CMakeFiles/myG4VSolid.dir/flags.make
CMakeFiles/myG4VSolid.dir/myG4VSolid.cc.o: ../myG4VSolid.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/keith/FreeCAD_Geant4/myg4py/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/myG4VSolid.dir/myG4VSolid.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/myG4VSolid.dir/myG4VSolid.cc.o -c /home/keith/FreeCAD_Geant4/myg4py/myG4VSolid.cc

CMakeFiles/myG4VSolid.dir/myG4VSolid.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myG4VSolid.dir/myG4VSolid.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/keith/FreeCAD_Geant4/myg4py/myG4VSolid.cc > CMakeFiles/myG4VSolid.dir/myG4VSolid.cc.i

CMakeFiles/myG4VSolid.dir/myG4VSolid.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myG4VSolid.dir/myG4VSolid.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/keith/FreeCAD_Geant4/myg4py/myG4VSolid.cc -o CMakeFiles/myG4VSolid.dir/myG4VSolid.cc.s

CMakeFiles/myG4VSolid.dir/myG4VSolid.cc.o.requires:

.PHONY : CMakeFiles/myG4VSolid.dir/myG4VSolid.cc.o.requires

CMakeFiles/myG4VSolid.dir/myG4VSolid.cc.o.provides: CMakeFiles/myG4VSolid.dir/myG4VSolid.cc.o.requires
	$(MAKE) -f CMakeFiles/myG4VSolid.dir/build.make CMakeFiles/myG4VSolid.dir/myG4VSolid.cc.o.provides.build
.PHONY : CMakeFiles/myG4VSolid.dir/myG4VSolid.cc.o.provides

CMakeFiles/myG4VSolid.dir/myG4VSolid.cc.o.provides.build: CMakeFiles/myG4VSolid.dir/myG4VSolid.cc.o


# Object files for target myG4VSolid
myG4VSolid_OBJECTS = \
"CMakeFiles/myG4VSolid.dir/myG4VSolid.cc.o"

# External object files for target myG4VSolid
myG4VSolid_EXTERNAL_OBJECTS =

myG4VSolid.so: CMakeFiles/myG4VSolid.dir/myG4VSolid.cc.o
myG4VSolid.so: CMakeFiles/myG4VSolid.dir/build.make
myG4VSolid.so: /usr/lib/x86_64-linux-gnu/libboost_python-py36.so
myG4VSolid.so: /usr/lib/x86_64-linux-gnu/libpython3.6m.so
myG4VSolid.so: CMakeFiles/myG4VSolid.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/keith/FreeCAD_Geant4/myg4py/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module myG4VSolid.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/myG4VSolid.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/myG4VSolid.dir/build: myG4VSolid.so

.PHONY : CMakeFiles/myG4VSolid.dir/build

CMakeFiles/myG4VSolid.dir/requires: CMakeFiles/myG4VSolid.dir/myG4VSolid.cc.o.requires

.PHONY : CMakeFiles/myG4VSolid.dir/requires

CMakeFiles/myG4VSolid.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/myG4VSolid.dir/cmake_clean.cmake
.PHONY : CMakeFiles/myG4VSolid.dir/clean

CMakeFiles/myG4VSolid.dir/depend:
	cd /home/keith/FreeCAD_Geant4/myg4py/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/keith/FreeCAD_Geant4/myg4py /home/keith/FreeCAD_Geant4/myg4py /home/keith/FreeCAD_Geant4/myg4py/build /home/keith/FreeCAD_Geant4/myg4py/build /home/keith/FreeCAD_Geant4/myg4py/build/CMakeFiles/myG4VSolid.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/myG4VSolid.dir/depend

