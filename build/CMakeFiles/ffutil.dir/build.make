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
CMAKE_SOURCE_DIR = /home/egor/PWDLab/Lab2/project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/egor/PWDLab/Lab2/project/build

# Include any dependencies generated for this target.
include CMakeFiles/ffutil.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ffutil.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ffutil.dir/flags.make

CMakeFiles/ffutil.dir/src/common/basename.c.o: CMakeFiles/ffutil.dir/flags.make
CMakeFiles/ffutil.dir/src/common/basename.c.o: ../src/common/basename.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/egor/PWDLab/Lab2/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ffutil.dir/src/common/basename.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ffutil.dir/src/common/basename.c.o   -c /home/egor/PWDLab/Lab2/project/src/common/basename.c

CMakeFiles/ffutil.dir/src/common/basename.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ffutil.dir/src/common/basename.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/egor/PWDLab/Lab2/project/src/common/basename.c > CMakeFiles/ffutil.dir/src/common/basename.c.i

CMakeFiles/ffutil.dir/src/common/basename.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ffutil.dir/src/common/basename.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/egor/PWDLab/Lab2/project/src/common/basename.c -o CMakeFiles/ffutil.dir/src/common/basename.c.s

CMakeFiles/ffutil.dir/src/common/error.c.o: CMakeFiles/ffutil.dir/flags.make
CMakeFiles/ffutil.dir/src/common/error.c.o: ../src/common/error.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/egor/PWDLab/Lab2/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/ffutil.dir/src/common/error.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ffutil.dir/src/common/error.c.o   -c /home/egor/PWDLab/Lab2/project/src/common/error.c

CMakeFiles/ffutil.dir/src/common/error.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ffutil.dir/src/common/error.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/egor/PWDLab/Lab2/project/src/common/error.c > CMakeFiles/ffutil.dir/src/common/error.c.i

CMakeFiles/ffutil.dir/src/common/error.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ffutil.dir/src/common/error.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/egor/PWDLab/Lab2/project/src/common/error.c -o CMakeFiles/ffutil.dir/src/common/error.c.s

CMakeFiles/ffutil.dir/src/decoder.c.o: CMakeFiles/ffutil.dir/flags.make
CMakeFiles/ffutil.dir/src/decoder.c.o: ../src/decoder.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/egor/PWDLab/Lab2/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/ffutil.dir/src/decoder.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ffutil.dir/src/decoder.c.o   -c /home/egor/PWDLab/Lab2/project/src/decoder.c

CMakeFiles/ffutil.dir/src/decoder.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ffutil.dir/src/decoder.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/egor/PWDLab/Lab2/project/src/decoder.c > CMakeFiles/ffutil.dir/src/decoder.c.i

CMakeFiles/ffutil.dir/src/decoder.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ffutil.dir/src/decoder.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/egor/PWDLab/Lab2/project/src/decoder.c -o CMakeFiles/ffutil.dir/src/decoder.c.s

CMakeFiles/ffutil.dir/src/encoder.c.o: CMakeFiles/ffutil.dir/flags.make
CMakeFiles/ffutil.dir/src/encoder.c.o: ../src/encoder.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/egor/PWDLab/Lab2/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/ffutil.dir/src/encoder.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ffutil.dir/src/encoder.c.o   -c /home/egor/PWDLab/Lab2/project/src/encoder.c

CMakeFiles/ffutil.dir/src/encoder.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ffutil.dir/src/encoder.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/egor/PWDLab/Lab2/project/src/encoder.c > CMakeFiles/ffutil.dir/src/encoder.c.i

CMakeFiles/ffutil.dir/src/encoder.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ffutil.dir/src/encoder.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/egor/PWDLab/Lab2/project/src/encoder.c -o CMakeFiles/ffutil.dir/src/encoder.c.s

CMakeFiles/ffutil.dir/src/frame.c.o: CMakeFiles/ffutil.dir/flags.make
CMakeFiles/ffutil.dir/src/frame.c.o: ../src/frame.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/egor/PWDLab/Lab2/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/ffutil.dir/src/frame.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ffutil.dir/src/frame.c.o   -c /home/egor/PWDLab/Lab2/project/src/frame.c

CMakeFiles/ffutil.dir/src/frame.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ffutil.dir/src/frame.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/egor/PWDLab/Lab2/project/src/frame.c > CMakeFiles/ffutil.dir/src/frame.c.i

CMakeFiles/ffutil.dir/src/frame.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ffutil.dir/src/frame.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/egor/PWDLab/Lab2/project/src/frame.c -o CMakeFiles/ffutil.dir/src/frame.c.s

CMakeFiles/ffutil.dir/src/main.c.o: CMakeFiles/ffutil.dir/flags.make
CMakeFiles/ffutil.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/egor/PWDLab/Lab2/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/ffutil.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ffutil.dir/src/main.c.o   -c /home/egor/PWDLab/Lab2/project/src/main.c

CMakeFiles/ffutil.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ffutil.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/egor/PWDLab/Lab2/project/src/main.c > CMakeFiles/ffutil.dir/src/main.c.i

CMakeFiles/ffutil.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ffutil.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/egor/PWDLab/Lab2/project/src/main.c -o CMakeFiles/ffutil.dir/src/main.c.s

CMakeFiles/ffutil.dir/src/resampler.c.o: CMakeFiles/ffutil.dir/flags.make
CMakeFiles/ffutil.dir/src/resampler.c.o: ../src/resampler.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/egor/PWDLab/Lab2/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/ffutil.dir/src/resampler.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ffutil.dir/src/resampler.c.o   -c /home/egor/PWDLab/Lab2/project/src/resampler.c

CMakeFiles/ffutil.dir/src/resampler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ffutil.dir/src/resampler.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/egor/PWDLab/Lab2/project/src/resampler.c > CMakeFiles/ffutil.dir/src/resampler.c.i

CMakeFiles/ffutil.dir/src/resampler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ffutil.dir/src/resampler.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/egor/PWDLab/Lab2/project/src/resampler.c -o CMakeFiles/ffutil.dir/src/resampler.c.s

CMakeFiles/ffutil.dir/src/rescaler.c.o: CMakeFiles/ffutil.dir/flags.make
CMakeFiles/ffutil.dir/src/rescaler.c.o: ../src/rescaler.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/egor/PWDLab/Lab2/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/ffutil.dir/src/rescaler.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ffutil.dir/src/rescaler.c.o   -c /home/egor/PWDLab/Lab2/project/src/rescaler.c

CMakeFiles/ffutil.dir/src/rescaler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ffutil.dir/src/rescaler.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/egor/PWDLab/Lab2/project/src/rescaler.c > CMakeFiles/ffutil.dir/src/rescaler.c.i

CMakeFiles/ffutil.dir/src/rescaler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ffutil.dir/src/rescaler.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/egor/PWDLab/Lab2/project/src/rescaler.c -o CMakeFiles/ffutil.dir/src/rescaler.c.s

# Object files for target ffutil
ffutil_OBJECTS = \
"CMakeFiles/ffutil.dir/src/common/basename.c.o" \
"CMakeFiles/ffutil.dir/src/common/error.c.o" \
"CMakeFiles/ffutil.dir/src/decoder.c.o" \
"CMakeFiles/ffutil.dir/src/encoder.c.o" \
"CMakeFiles/ffutil.dir/src/frame.c.o" \
"CMakeFiles/ffutil.dir/src/main.c.o" \
"CMakeFiles/ffutil.dir/src/resampler.c.o" \
"CMakeFiles/ffutil.dir/src/rescaler.c.o"

# External object files for target ffutil
ffutil_EXTERNAL_OBJECTS =

ffutil: CMakeFiles/ffutil.dir/src/common/basename.c.o
ffutil: CMakeFiles/ffutil.dir/src/common/error.c.o
ffutil: CMakeFiles/ffutil.dir/src/decoder.c.o
ffutil: CMakeFiles/ffutil.dir/src/encoder.c.o
ffutil: CMakeFiles/ffutil.dir/src/frame.c.o
ffutil: CMakeFiles/ffutil.dir/src/main.c.o
ffutil: CMakeFiles/ffutil.dir/src/resampler.c.o
ffutil: CMakeFiles/ffutil.dir/src/rescaler.c.o
ffutil: CMakeFiles/ffutil.dir/build.make
ffutil: /usr/lib/x86_64-linux-gnu/libavformat.so
ffutil: /usr/lib/x86_64-linux-gnu/libavcodec.so
ffutil: /usr/lib/x86_64-linux-gnu/libavutil.so
ffutil: /usr/lib/x86_64-linux-gnu/libswscale.so
ffutil: /usr/lib/x86_64-linux-gnu/libswresample.so
ffutil: /usr/lib/x86_64-linux-gnu/libm.so
ffutil: /usr/lib/x86_64-linux-gnu/libpthread.so
ffutil: CMakeFiles/ffutil.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/egor/PWDLab/Lab2/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking C executable ffutil"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ffutil.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ffutil.dir/build: ffutil

.PHONY : CMakeFiles/ffutil.dir/build

CMakeFiles/ffutil.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ffutil.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ffutil.dir/clean

CMakeFiles/ffutil.dir/depend:
	cd /home/egor/PWDLab/Lab2/project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/egor/PWDLab/Lab2/project /home/egor/PWDLab/Lab2/project /home/egor/PWDLab/Lab2/project/build /home/egor/PWDLab/Lab2/project/build /home/egor/PWDLab/Lab2/project/build/CMakeFiles/ffutil.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ffutil.dir/depend
