# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\CPP\2020_5\Compiler\Experience\Tiny

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\CPP\2020_5\Compiler\Experience\Tiny\build

# Include any dependencies generated for this target.
include CMakeFiles/tiny.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tiny.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tiny.dir/flags.make

CMakeFiles/tiny.dir/tinyparsertest.cpp.obj: CMakeFiles/tiny.dir/flags.make
CMakeFiles/tiny.dir/tinyparsertest.cpp.obj: CMakeFiles/tiny.dir/includes_CXX.rsp
CMakeFiles/tiny.dir/tinyparsertest.cpp.obj: ../tinyparsertest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\CPP\2020_5\Compiler\Experience\Tiny\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tiny.dir/tinyparsertest.cpp.obj"
	C:\BC\C\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\tiny.dir\tinyparsertest.cpp.obj -c C:\CPP\2020_5\Compiler\Experience\Tiny\tinyparsertest.cpp

CMakeFiles/tiny.dir/tinyparsertest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tiny.dir/tinyparsertest.cpp.i"
	C:\BC\C\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\CPP\2020_5\Compiler\Experience\Tiny\tinyparsertest.cpp > CMakeFiles\tiny.dir\tinyparsertest.cpp.i

CMakeFiles/tiny.dir/tinyparsertest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tiny.dir/tinyparsertest.cpp.s"
	C:\BC\C\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\CPP\2020_5\Compiler\Experience\Tiny\tinyparsertest.cpp -o CMakeFiles\tiny.dir\tinyparsertest.cpp.s

# Object files for target tiny
tiny_OBJECTS = \
"CMakeFiles/tiny.dir/tinyparsertest.cpp.obj"

# External object files for target tiny
tiny_EXTERNAL_OBJECTS =

tiny.exe: CMakeFiles/tiny.dir/tinyparsertest.cpp.obj
tiny.exe: CMakeFiles/tiny.dir/build.make
tiny.exe: libtinyParser.a
tiny.exe: libtinyLexer.a
tiny.exe: CMakeFiles/tiny.dir/linklibs.rsp
tiny.exe: CMakeFiles/tiny.dir/objects1.rsp
tiny.exe: CMakeFiles/tiny.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\CPP\2020_5\Compiler\Experience\Tiny\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tiny.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\tiny.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tiny.dir/build: tiny.exe

.PHONY : CMakeFiles/tiny.dir/build

CMakeFiles/tiny.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\tiny.dir\cmake_clean.cmake
.PHONY : CMakeFiles/tiny.dir/clean

CMakeFiles/tiny.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\CPP\2020_5\Compiler\Experience\Tiny C:\CPP\2020_5\Compiler\Experience\Tiny C:\CPP\2020_5\Compiler\Experience\Tiny\build C:\CPP\2020_5\Compiler\Experience\Tiny\build C:\CPP\2020_5\Compiler\Experience\Tiny\build\CMakeFiles\tiny.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tiny.dir/depend

