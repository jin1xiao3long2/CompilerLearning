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
include CMakeFiles/tinyLexer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tinyLexer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tinyLexer.dir/flags.make

CMakeFiles/tinyLexer.dir/Tiny_Lexer.cpp.obj: CMakeFiles/tinyLexer.dir/flags.make
CMakeFiles/tinyLexer.dir/Tiny_Lexer.cpp.obj: CMakeFiles/tinyLexer.dir/includes_CXX.rsp
CMakeFiles/tinyLexer.dir/Tiny_Lexer.cpp.obj: ../Tiny_Lexer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\CPP\2020_5\Compiler\Experience\Tiny\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tinyLexer.dir/Tiny_Lexer.cpp.obj"
	C:\BC\C\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\tinyLexer.dir\Tiny_Lexer.cpp.obj -c C:\CPP\2020_5\Compiler\Experience\Tiny\Tiny_Lexer.cpp

CMakeFiles/tinyLexer.dir/Tiny_Lexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tinyLexer.dir/Tiny_Lexer.cpp.i"
	C:\BC\C\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\CPP\2020_5\Compiler\Experience\Tiny\Tiny_Lexer.cpp > CMakeFiles\tinyLexer.dir\Tiny_Lexer.cpp.i

CMakeFiles/tinyLexer.dir/Tiny_Lexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tinyLexer.dir/Tiny_Lexer.cpp.s"
	C:\BC\C\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\CPP\2020_5\Compiler\Experience\Tiny\Tiny_Lexer.cpp -o CMakeFiles\tinyLexer.dir\Tiny_Lexer.cpp.s

CMakeFiles/tinyLexer.dir/Tiny_Signal.cpp.obj: CMakeFiles/tinyLexer.dir/flags.make
CMakeFiles/tinyLexer.dir/Tiny_Signal.cpp.obj: CMakeFiles/tinyLexer.dir/includes_CXX.rsp
CMakeFiles/tinyLexer.dir/Tiny_Signal.cpp.obj: ../Tiny_Signal.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\CPP\2020_5\Compiler\Experience\Tiny\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tinyLexer.dir/Tiny_Signal.cpp.obj"
	C:\BC\C\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\tinyLexer.dir\Tiny_Signal.cpp.obj -c C:\CPP\2020_5\Compiler\Experience\Tiny\Tiny_Signal.cpp

CMakeFiles/tinyLexer.dir/Tiny_Signal.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tinyLexer.dir/Tiny_Signal.cpp.i"
	C:\BC\C\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\CPP\2020_5\Compiler\Experience\Tiny\Tiny_Signal.cpp > CMakeFiles\tinyLexer.dir\Tiny_Signal.cpp.i

CMakeFiles/tinyLexer.dir/Tiny_Signal.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tinyLexer.dir/Tiny_Signal.cpp.s"
	C:\BC\C\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\CPP\2020_5\Compiler\Experience\Tiny\Tiny_Signal.cpp -o CMakeFiles\tinyLexer.dir\Tiny_Signal.cpp.s

# Object files for target tinyLexer
tinyLexer_OBJECTS = \
"CMakeFiles/tinyLexer.dir/Tiny_Lexer.cpp.obj" \
"CMakeFiles/tinyLexer.dir/Tiny_Signal.cpp.obj"

# External object files for target tinyLexer
tinyLexer_EXTERNAL_OBJECTS =

libtinyLexer.a: CMakeFiles/tinyLexer.dir/Tiny_Lexer.cpp.obj
libtinyLexer.a: CMakeFiles/tinyLexer.dir/Tiny_Signal.cpp.obj
libtinyLexer.a: CMakeFiles/tinyLexer.dir/build.make
libtinyLexer.a: CMakeFiles/tinyLexer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\CPP\2020_5\Compiler\Experience\Tiny\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libtinyLexer.a"
	$(CMAKE_COMMAND) -P CMakeFiles\tinyLexer.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\tinyLexer.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tinyLexer.dir/build: libtinyLexer.a

.PHONY : CMakeFiles/tinyLexer.dir/build

CMakeFiles/tinyLexer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\tinyLexer.dir\cmake_clean.cmake
.PHONY : CMakeFiles/tinyLexer.dir/clean

CMakeFiles/tinyLexer.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\CPP\2020_5\Compiler\Experience\Tiny C:\CPP\2020_5\Compiler\Experience\Tiny C:\CPP\2020_5\Compiler\Experience\Tiny\build C:\CPP\2020_5\Compiler\Experience\Tiny\build C:\CPP\2020_5\Compiler\Experience\Tiny\build\CMakeFiles\tinyLexer.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tinyLexer.dir/depend
