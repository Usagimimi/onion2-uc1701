# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /mnt/c/Project/!Mips/onion2-uc1701/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Project/!Mips/onion2-uc1701/src

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/gpio.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/gpio.c.o: gpio.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Project/!Mips/onion2-uc1701/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/main.dir/gpio.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/gpio.c.o   -c /mnt/c/Project/!Mips/onion2-uc1701/src/gpio.c

CMakeFiles/main.dir/gpio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/gpio.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Project/!Mips/onion2-uc1701/src/gpio.c > CMakeFiles/main.dir/gpio.c.i

CMakeFiles/main.dir/gpio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/gpio.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Project/!Mips/onion2-uc1701/src/gpio.c -o CMakeFiles/main.dir/gpio.c.s

CMakeFiles/main.dir/gpio.c.o.requires:

.PHONY : CMakeFiles/main.dir/gpio.c.o.requires

CMakeFiles/main.dir/gpio.c.o.provides: CMakeFiles/main.dir/gpio.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/gpio.c.o.provides.build
.PHONY : CMakeFiles/main.dir/gpio.c.o.provides

CMakeFiles/main.dir/gpio.c.o.provides.build: CMakeFiles/main.dir/gpio.c.o


CMakeFiles/main.dir/main.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/main.c.o: main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Project/!Mips/onion2-uc1701/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/main.dir/main.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/main.c.o   -c /mnt/c/Project/!Mips/onion2-uc1701/src/main.c

CMakeFiles/main.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/main.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Project/!Mips/onion2-uc1701/src/main.c > CMakeFiles/main.dir/main.c.i

CMakeFiles/main.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/main.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Project/!Mips/onion2-uc1701/src/main.c -o CMakeFiles/main.dir/main.c.s

CMakeFiles/main.dir/main.c.o.requires:

.PHONY : CMakeFiles/main.dir/main.c.o.requires

CMakeFiles/main.dir/main.c.o.provides: CMakeFiles/main.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/main.c.o.provides.build
.PHONY : CMakeFiles/main.dir/main.c.o.provides

CMakeFiles/main.dir/main.c.o.provides.build: CMakeFiles/main.dir/main.c.o


CMakeFiles/main.dir/uc1701.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/uc1701.c.o: uc1701.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Project/!Mips/onion2-uc1701/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/main.dir/uc1701.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/uc1701.c.o   -c /mnt/c/Project/!Mips/onion2-uc1701/src/uc1701.c

CMakeFiles/main.dir/uc1701.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/uc1701.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Project/!Mips/onion2-uc1701/src/uc1701.c > CMakeFiles/main.dir/uc1701.c.i

CMakeFiles/main.dir/uc1701.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/uc1701.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Project/!Mips/onion2-uc1701/src/uc1701.c -o CMakeFiles/main.dir/uc1701.c.s

CMakeFiles/main.dir/uc1701.c.o.requires:

.PHONY : CMakeFiles/main.dir/uc1701.c.o.requires

CMakeFiles/main.dir/uc1701.c.o.provides: CMakeFiles/main.dir/uc1701.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/uc1701.c.o.provides.build
.PHONY : CMakeFiles/main.dir/uc1701.c.o.provides

CMakeFiles/main.dir/uc1701.c.o.provides.build: CMakeFiles/main.dir/uc1701.c.o


CMakeFiles/main.dir/ugpio.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/ugpio.c.o: ugpio.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Project/!Mips/onion2-uc1701/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/main.dir/ugpio.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/ugpio.c.o   -c /mnt/c/Project/!Mips/onion2-uc1701/src/ugpio.c

CMakeFiles/main.dir/ugpio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/ugpio.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Project/!Mips/onion2-uc1701/src/ugpio.c > CMakeFiles/main.dir/ugpio.c.i

CMakeFiles/main.dir/ugpio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/ugpio.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Project/!Mips/onion2-uc1701/src/ugpio.c -o CMakeFiles/main.dir/ugpio.c.s

CMakeFiles/main.dir/ugpio.c.o.requires:

.PHONY : CMakeFiles/main.dir/ugpio.c.o.requires

CMakeFiles/main.dir/ugpio.c.o.provides: CMakeFiles/main.dir/ugpio.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/ugpio.c.o.provides.build
.PHONY : CMakeFiles/main.dir/ugpio.c.o.provides

CMakeFiles/main.dir/ugpio.c.o.provides.build: CMakeFiles/main.dir/ugpio.c.o


CMakeFiles/main.dir/ugpio-internal.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/ugpio-internal.c.o: ugpio-internal.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Project/!Mips/onion2-uc1701/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/main.dir/ugpio-internal.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/ugpio-internal.c.o   -c /mnt/c/Project/!Mips/onion2-uc1701/src/ugpio-internal.c

CMakeFiles/main.dir/ugpio-internal.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/ugpio-internal.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Project/!Mips/onion2-uc1701/src/ugpio-internal.c > CMakeFiles/main.dir/ugpio-internal.c.i

CMakeFiles/main.dir/ugpio-internal.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/ugpio-internal.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Project/!Mips/onion2-uc1701/src/ugpio-internal.c -o CMakeFiles/main.dir/ugpio-internal.c.s

CMakeFiles/main.dir/ugpio-internal.c.o.requires:

.PHONY : CMakeFiles/main.dir/ugpio-internal.c.o.requires

CMakeFiles/main.dir/ugpio-internal.c.o.provides: CMakeFiles/main.dir/ugpio-internal.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/ugpio-internal.c.o.provides.build
.PHONY : CMakeFiles/main.dir/ugpio-internal.c.o.provides

CMakeFiles/main.dir/ugpio-internal.c.o.provides.build: CMakeFiles/main.dir/ugpio-internal.c.o


CMakeFiles/main.dir/wrt-spi.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/wrt-spi.c.o: wrt-spi.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Project/!Mips/onion2-uc1701/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/main.dir/wrt-spi.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/wrt-spi.c.o   -c /mnt/c/Project/!Mips/onion2-uc1701/src/wrt-spi.c

CMakeFiles/main.dir/wrt-spi.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/wrt-spi.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Project/!Mips/onion2-uc1701/src/wrt-spi.c > CMakeFiles/main.dir/wrt-spi.c.i

CMakeFiles/main.dir/wrt-spi.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/wrt-spi.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Project/!Mips/onion2-uc1701/src/wrt-spi.c -o CMakeFiles/main.dir/wrt-spi.c.s

CMakeFiles/main.dir/wrt-spi.c.o.requires:

.PHONY : CMakeFiles/main.dir/wrt-spi.c.o.requires

CMakeFiles/main.dir/wrt-spi.c.o.provides: CMakeFiles/main.dir/wrt-spi.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/wrt-spi.c.o.provides.build
.PHONY : CMakeFiles/main.dir/wrt-spi.c.o.provides

CMakeFiles/main.dir/wrt-spi.c.o.provides.build: CMakeFiles/main.dir/wrt-spi.c.o


# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/gpio.c.o" \
"CMakeFiles/main.dir/main.c.o" \
"CMakeFiles/main.dir/uc1701.c.o" \
"CMakeFiles/main.dir/ugpio.c.o" \
"CMakeFiles/main.dir/ugpio-internal.c.o" \
"CMakeFiles/main.dir/wrt-spi.c.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/gpio.c.o
main: CMakeFiles/main.dir/main.c.o
main: CMakeFiles/main.dir/uc1701.c.o
main: CMakeFiles/main.dir/ugpio.c.o
main: CMakeFiles/main.dir/ugpio-internal.c.o
main: CMakeFiles/main.dir/wrt-spi.c.o
main: CMakeFiles/main.dir/build.make
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Project/!Mips/onion2-uc1701/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main

.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/requires: CMakeFiles/main.dir/gpio.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/main.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/uc1701.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/ugpio.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/ugpio-internal.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/wrt-spi.c.o.requires

.PHONY : CMakeFiles/main.dir/requires

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /mnt/c/Project/!Mips/onion2-uc1701/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Project/!Mips/onion2-uc1701/src /mnt/c/Project/!Mips/onion2-uc1701/src /mnt/c/Project/!Mips/onion2-uc1701/src /mnt/c/Project/!Mips/onion2-uc1701/src /mnt/c/Project/!Mips/onion2-uc1701/src/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend
