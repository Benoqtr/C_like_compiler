# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\GithubProjects\C_like_compiler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\GithubProjects\C_like_compiler\build

# Include any dependencies generated for this target.
include test/CMakeFiles/test_config.exe.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/test_config.exe.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/test_config.exe.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/test_config.exe.dir/flags.make

test/CMakeFiles/test_config.exe.dir/test_config.cpp.obj: test/CMakeFiles/test_config.exe.dir/flags.make
test/CMakeFiles/test_config.exe.dir/test_config.cpp.obj: test/CMakeFiles/test_config.exe.dir/includes_CXX.rsp
test/CMakeFiles/test_config.exe.dir/test_config.cpp.obj: D:/GithubProjects/C_like_compiler/test/test_config.cpp
test/CMakeFiles/test_config.exe.dir/test_config.cpp.obj: test/CMakeFiles/test_config.exe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\GithubProjects\C_like_compiler\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/test_config.exe.dir/test_config.cpp.obj"
	cd /d D:\GithubProjects\C_like_compiler\build\test && C:\complier\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/test_config.exe.dir/test_config.cpp.obj -MF CMakeFiles\test_config.exe.dir\test_config.cpp.obj.d -o CMakeFiles\test_config.exe.dir\test_config.cpp.obj -c D:\GithubProjects\C_like_compiler\test\test_config.cpp

test/CMakeFiles/test_config.exe.dir/test_config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_config.exe.dir/test_config.cpp.i"
	cd /d D:\GithubProjects\C_like_compiler\build\test && C:\complier\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\GithubProjects\C_like_compiler\test\test_config.cpp > CMakeFiles\test_config.exe.dir\test_config.cpp.i

test/CMakeFiles/test_config.exe.dir/test_config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_config.exe.dir/test_config.cpp.s"
	cd /d D:\GithubProjects\C_like_compiler\build\test && C:\complier\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\GithubProjects\C_like_compiler\test\test_config.cpp -o CMakeFiles\test_config.exe.dir\test_config.cpp.s

# Object files for target test_config.exe
test_config_exe_OBJECTS = \
"CMakeFiles/test_config.exe.dir/test_config.cpp.obj"

# External object files for target test_config.exe
test_config_exe_EXTERNAL_OBJECTS =

test/test_config.exe.exe: test/CMakeFiles/test_config.exe.dir/test_config.cpp.obj
test/test_config.exe.exe: test/CMakeFiles/test_config.exe.dir/build.make
test/test_config.exe.exe: test/CMakeFiles/test_config.exe.dir/compiler_depend.ts
test/test_config.exe.exe: config/libconfig.a
test/test_config.exe.exe: test/CMakeFiles/test_config.exe.dir/linkLibs.rsp
test/test_config.exe.exe: test/CMakeFiles/test_config.exe.dir/objects1.rsp
test/test_config.exe.exe: test/CMakeFiles/test_config.exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\GithubProjects\C_like_compiler\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_config.exe.exe"
	cd /d D:\GithubProjects\C_like_compiler\build\test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\test_config.exe.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/test_config.exe.dir/build: test/test_config.exe.exe
.PHONY : test/CMakeFiles/test_config.exe.dir/build

test/CMakeFiles/test_config.exe.dir/clean:
	cd /d D:\GithubProjects\C_like_compiler\build\test && $(CMAKE_COMMAND) -P CMakeFiles\test_config.exe.dir\cmake_clean.cmake
.PHONY : test/CMakeFiles/test_config.exe.dir/clean

test/CMakeFiles/test_config.exe.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\GithubProjects\C_like_compiler D:\GithubProjects\C_like_compiler\test D:\GithubProjects\C_like_compiler\build D:\GithubProjects\C_like_compiler\build\test D:\GithubProjects\C_like_compiler\build\test\CMakeFiles\test_config.exe.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : test/CMakeFiles/test_config.exe.dir/depend

