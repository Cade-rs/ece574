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
CMAKE_COMMAND = "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\cader\Documents\school\ECE574\workspace\git\ece574\test\cmaketest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\cader\Documents\school\ECE574\workspace\git\ece574\test\cmaketest\build

# Include any dependencies generated for this target.
include CMakeFiles/cmaketest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cmaketest.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cmaketest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cmaketest.dir/flags.make

CMakeFiles/cmaketest.dir/src/main.cpp.obj: CMakeFiles/cmaketest.dir/flags.make
CMakeFiles/cmaketest.dir/src/main.cpp.obj: ../src/main.cpp
CMakeFiles/cmaketest.dir/src/main.cpp.obj: CMakeFiles/cmaketest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\cader\Documents\school\ECE574\workspace\git\ece574\test\cmaketest\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cmaketest.dir/src/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\X86_64~2.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cmaketest.dir/src/main.cpp.obj -MF CMakeFiles\cmaketest.dir\src\main.cpp.obj.d -o CMakeFiles\cmaketest.dir\src\main.cpp.obj -c C:\Users\cader\Documents\school\ECE574\workspace\git\ece574\test\cmaketest\src\main.cpp

CMakeFiles/cmaketest.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cmaketest.dir/src/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\X86_64~2.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\cader\Documents\school\ECE574\workspace\git\ece574\test\cmaketest\src\main.cpp > CMakeFiles\cmaketest.dir\src\main.cpp.i

CMakeFiles/cmaketest.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cmaketest.dir/src/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\X86_64~2.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\cader\Documents\school\ECE574\workspace\git\ece574\test\cmaketest\src\main.cpp -o CMakeFiles\cmaketest.dir\src\main.cpp.s

# Object files for target cmaketest
cmaketest_OBJECTS = \
"CMakeFiles/cmaketest.dir/src/main.cpp.obj"

# External object files for target cmaketest
cmaketest_EXTERNAL_OBJECTS =

cmaketest.exe: CMakeFiles/cmaketest.dir/src/main.cpp.obj
cmaketest.exe: CMakeFiles/cmaketest.dir/build.make
cmaketest.exe: CMakeFiles/cmaketest.dir/linklibs.rsp
cmaketest.exe: CMakeFiles/cmaketest.dir/objects1.rsp
cmaketest.exe: CMakeFiles/cmaketest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\cader\Documents\school\ECE574\workspace\git\ece574\test\cmaketest\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cmaketest.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\cmaketest.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cmaketest.dir/build: cmaketest.exe
.PHONY : CMakeFiles/cmaketest.dir/build

CMakeFiles/cmaketest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\cmaketest.dir\cmake_clean.cmake
.PHONY : CMakeFiles/cmaketest.dir/clean

CMakeFiles/cmaketest.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\cader\Documents\school\ECE574\workspace\git\ece574\test\cmaketest C:\Users\cader\Documents\school\ECE574\workspace\git\ece574\test\cmaketest C:\Users\cader\Documents\school\ECE574\workspace\git\ece574\test\cmaketest\build C:\Users\cader\Documents\school\ECE574\workspace\git\ece574\test\cmaketest\build C:\Users\cader\Documents\school\ECE574\workspace\git\ece574\test\cmaketest\build\CMakeFiles\cmaketest.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cmaketest.dir/depend

