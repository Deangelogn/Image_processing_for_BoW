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
CMAKE_COMMAND = /home/eu/Desktop/clion-2017.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/eu/Desktop/clion-2017.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/eu/Desktop/C_C++/Image_processing_for_BoW

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/eu/Desktop/C_C++/Image_processing_for_BoW/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Clion.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Clion.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Clion.dir/flags.make

CMakeFiles/Clion.dir/main.c.o: CMakeFiles/Clion.dir/flags.make
CMakeFiles/Clion.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eu/Desktop/C_C++/Image_processing_for_BoW/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Clion.dir/main.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Clion.dir/main.c.o   -c /home/eu/Desktop/C_C++/Image_processing_for_BoW/main.c

CMakeFiles/Clion.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Clion.dir/main.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/eu/Desktop/C_C++/Image_processing_for_BoW/main.c > CMakeFiles/Clion.dir/main.c.i

CMakeFiles/Clion.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Clion.dir/main.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/eu/Desktop/C_C++/Image_processing_for_BoW/main.c -o CMakeFiles/Clion.dir/main.c.s

CMakeFiles/Clion.dir/main.c.o.requires:

.PHONY : CMakeFiles/Clion.dir/main.c.o.requires

CMakeFiles/Clion.dir/main.c.o.provides: CMakeFiles/Clion.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/Clion.dir/build.make CMakeFiles/Clion.dir/main.c.o.provides.build
.PHONY : CMakeFiles/Clion.dir/main.c.o.provides

CMakeFiles/Clion.dir/main.c.o.provides.build: CMakeFiles/Clion.dir/main.c.o


CMakeFiles/Clion.dir/src/image.c.o: CMakeFiles/Clion.dir/flags.make
CMakeFiles/Clion.dir/src/image.c.o: ../src/image.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eu/Desktop/C_C++/Image_processing_for_BoW/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Clion.dir/src/image.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Clion.dir/src/image.c.o   -c /home/eu/Desktop/C_C++/Image_processing_for_BoW/src/image.c

CMakeFiles/Clion.dir/src/image.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Clion.dir/src/image.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/eu/Desktop/C_C++/Image_processing_for_BoW/src/image.c > CMakeFiles/Clion.dir/src/image.c.i

CMakeFiles/Clion.dir/src/image.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Clion.dir/src/image.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/eu/Desktop/C_C++/Image_processing_for_BoW/src/image.c -o CMakeFiles/Clion.dir/src/image.c.s

CMakeFiles/Clion.dir/src/image.c.o.requires:

.PHONY : CMakeFiles/Clion.dir/src/image.c.o.requires

CMakeFiles/Clion.dir/src/image.c.o.provides: CMakeFiles/Clion.dir/src/image.c.o.requires
	$(MAKE) -f CMakeFiles/Clion.dir/build.make CMakeFiles/Clion.dir/src/image.c.o.provides.build
.PHONY : CMakeFiles/Clion.dir/src/image.c.o.provides

CMakeFiles/Clion.dir/src/image.c.o.provides.build: CMakeFiles/Clion.dir/src/image.c.o


CMakeFiles/Clion.dir/src/histogram.c.o: CMakeFiles/Clion.dir/flags.make
CMakeFiles/Clion.dir/src/histogram.c.o: ../src/histogram.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eu/Desktop/C_C++/Image_processing_for_BoW/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Clion.dir/src/histogram.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Clion.dir/src/histogram.c.o   -c /home/eu/Desktop/C_C++/Image_processing_for_BoW/src/histogram.c

CMakeFiles/Clion.dir/src/histogram.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Clion.dir/src/histogram.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/eu/Desktop/C_C++/Image_processing_for_BoW/src/histogram.c > CMakeFiles/Clion.dir/src/histogram.c.i

CMakeFiles/Clion.dir/src/histogram.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Clion.dir/src/histogram.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/eu/Desktop/C_C++/Image_processing_for_BoW/src/histogram.c -o CMakeFiles/Clion.dir/src/histogram.c.s

CMakeFiles/Clion.dir/src/histogram.c.o.requires:

.PHONY : CMakeFiles/Clion.dir/src/histogram.c.o.requires

CMakeFiles/Clion.dir/src/histogram.c.o.provides: CMakeFiles/Clion.dir/src/histogram.c.o.requires
	$(MAKE) -f CMakeFiles/Clion.dir/build.make CMakeFiles/Clion.dir/src/histogram.c.o.provides.build
.PHONY : CMakeFiles/Clion.dir/src/histogram.c.o.provides

CMakeFiles/Clion.dir/src/histogram.c.o.provides.build: CMakeFiles/Clion.dir/src/histogram.c.o


CMakeFiles/Clion.dir/src/adjRelation.c.o: CMakeFiles/Clion.dir/flags.make
CMakeFiles/Clion.dir/src/adjRelation.c.o: ../src/adjRelation.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eu/Desktop/C_C++/Image_processing_for_BoW/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/Clion.dir/src/adjRelation.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Clion.dir/src/adjRelation.c.o   -c /home/eu/Desktop/C_C++/Image_processing_for_BoW/src/adjRelation.c

CMakeFiles/Clion.dir/src/adjRelation.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Clion.dir/src/adjRelation.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/eu/Desktop/C_C++/Image_processing_for_BoW/src/adjRelation.c > CMakeFiles/Clion.dir/src/adjRelation.c.i

CMakeFiles/Clion.dir/src/adjRelation.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Clion.dir/src/adjRelation.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/eu/Desktop/C_C++/Image_processing_for_BoW/src/adjRelation.c -o CMakeFiles/Clion.dir/src/adjRelation.c.s

CMakeFiles/Clion.dir/src/adjRelation.c.o.requires:

.PHONY : CMakeFiles/Clion.dir/src/adjRelation.c.o.requires

CMakeFiles/Clion.dir/src/adjRelation.c.o.provides: CMakeFiles/Clion.dir/src/adjRelation.c.o.requires
	$(MAKE) -f CMakeFiles/Clion.dir/build.make CMakeFiles/Clion.dir/src/adjRelation.c.o.provides.build
.PHONY : CMakeFiles/Clion.dir/src/adjRelation.c.o.provides

CMakeFiles/Clion.dir/src/adjRelation.c.o.provides.build: CMakeFiles/Clion.dir/src/adjRelation.c.o


CMakeFiles/Clion.dir/src/morphology.c.o: CMakeFiles/Clion.dir/flags.make
CMakeFiles/Clion.dir/src/morphology.c.o: ../src/morphology.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eu/Desktop/C_C++/Image_processing_for_BoW/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/Clion.dir/src/morphology.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Clion.dir/src/morphology.c.o   -c /home/eu/Desktop/C_C++/Image_processing_for_BoW/src/morphology.c

CMakeFiles/Clion.dir/src/morphology.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Clion.dir/src/morphology.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/eu/Desktop/C_C++/Image_processing_for_BoW/src/morphology.c > CMakeFiles/Clion.dir/src/morphology.c.i

CMakeFiles/Clion.dir/src/morphology.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Clion.dir/src/morphology.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/eu/Desktop/C_C++/Image_processing_for_BoW/src/morphology.c -o CMakeFiles/Clion.dir/src/morphology.c.s

CMakeFiles/Clion.dir/src/morphology.c.o.requires:

.PHONY : CMakeFiles/Clion.dir/src/morphology.c.o.requires

CMakeFiles/Clion.dir/src/morphology.c.o.provides: CMakeFiles/Clion.dir/src/morphology.c.o.requires
	$(MAKE) -f CMakeFiles/Clion.dir/build.make CMakeFiles/Clion.dir/src/morphology.c.o.provides.build
.PHONY : CMakeFiles/Clion.dir/src/morphology.c.o.provides

CMakeFiles/Clion.dir/src/morphology.c.o.provides.build: CMakeFiles/Clion.dir/src/morphology.c.o


CMakeFiles/Clion.dir/src/math.c.o: CMakeFiles/Clion.dir/flags.make
CMakeFiles/Clion.dir/src/math.c.o: ../src/math.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eu/Desktop/C_C++/Image_processing_for_BoW/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/Clion.dir/src/math.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Clion.dir/src/math.c.o   -c /home/eu/Desktop/C_C++/Image_processing_for_BoW/src/math.c

CMakeFiles/Clion.dir/src/math.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Clion.dir/src/math.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/eu/Desktop/C_C++/Image_processing_for_BoW/src/math.c > CMakeFiles/Clion.dir/src/math.c.i

CMakeFiles/Clion.dir/src/math.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Clion.dir/src/math.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/eu/Desktop/C_C++/Image_processing_for_BoW/src/math.c -o CMakeFiles/Clion.dir/src/math.c.s

CMakeFiles/Clion.dir/src/math.c.o.requires:

.PHONY : CMakeFiles/Clion.dir/src/math.c.o.requires

CMakeFiles/Clion.dir/src/math.c.o.provides: CMakeFiles/Clion.dir/src/math.c.o.requires
	$(MAKE) -f CMakeFiles/Clion.dir/build.make CMakeFiles/Clion.dir/src/math.c.o.provides.build
.PHONY : CMakeFiles/Clion.dir/src/math.c.o.provides

CMakeFiles/Clion.dir/src/math.c.o.provides.build: CMakeFiles/Clion.dir/src/math.c.o


# Object files for target Clion
Clion_OBJECTS = \
"CMakeFiles/Clion.dir/main.c.o" \
"CMakeFiles/Clion.dir/src/image.c.o" \
"CMakeFiles/Clion.dir/src/histogram.c.o" \
"CMakeFiles/Clion.dir/src/adjRelation.c.o" \
"CMakeFiles/Clion.dir/src/morphology.c.o" \
"CMakeFiles/Clion.dir/src/math.c.o"

# External object files for target Clion
Clion_EXTERNAL_OBJECTS =

Clion: CMakeFiles/Clion.dir/main.c.o
Clion: CMakeFiles/Clion.dir/src/image.c.o
Clion: CMakeFiles/Clion.dir/src/histogram.c.o
Clion: CMakeFiles/Clion.dir/src/adjRelation.c.o
Clion: CMakeFiles/Clion.dir/src/morphology.c.o
Clion: CMakeFiles/Clion.dir/src/math.c.o
Clion: CMakeFiles/Clion.dir/build.make
Clion: CMakeFiles/Clion.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/eu/Desktop/C_C++/Image_processing_for_BoW/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable Clion"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Clion.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Clion.dir/build: Clion

.PHONY : CMakeFiles/Clion.dir/build

CMakeFiles/Clion.dir/requires: CMakeFiles/Clion.dir/main.c.o.requires
CMakeFiles/Clion.dir/requires: CMakeFiles/Clion.dir/src/image.c.o.requires
CMakeFiles/Clion.dir/requires: CMakeFiles/Clion.dir/src/histogram.c.o.requires
CMakeFiles/Clion.dir/requires: CMakeFiles/Clion.dir/src/adjRelation.c.o.requires
CMakeFiles/Clion.dir/requires: CMakeFiles/Clion.dir/src/morphology.c.o.requires
CMakeFiles/Clion.dir/requires: CMakeFiles/Clion.dir/src/math.c.o.requires

.PHONY : CMakeFiles/Clion.dir/requires

CMakeFiles/Clion.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Clion.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Clion.dir/clean

CMakeFiles/Clion.dir/depend:
	cd /home/eu/Desktop/C_C++/Image_processing_for_BoW/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/eu/Desktop/C_C++/Image_processing_for_BoW /home/eu/Desktop/C_C++/Image_processing_for_BoW /home/eu/Desktop/C_C++/Image_processing_for_BoW/cmake-build-debug /home/eu/Desktop/C_C++/Image_processing_for_BoW/cmake-build-debug /home/eu/Desktop/C_C++/Image_processing_for_BoW/cmake-build-debug/CMakeFiles/Clion.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Clion.dir/depend

