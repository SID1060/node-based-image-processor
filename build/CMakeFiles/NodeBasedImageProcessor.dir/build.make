# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_SOURCE_DIR = /home/siddharth/node-based-image-processor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/siddharth/node-based-image-processor/build

# Include any dependencies generated for this target.
include CMakeFiles/NodeBasedImageProcessor.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/NodeBasedImageProcessor.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/NodeBasedImageProcessor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/NodeBasedImageProcessor.dir/flags.make

CMakeFiles/NodeBasedImageProcessor.dir/src/BlendNode.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/flags.make
CMakeFiles/NodeBasedImageProcessor.dir/src/BlendNode.cpp.o: /home/siddharth/node-based-image-processor/src/BlendNode.cpp
CMakeFiles/NodeBasedImageProcessor.dir/src/BlendNode.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/siddharth/node-based-image-processor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/NodeBasedImageProcessor.dir/src/BlendNode.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeBasedImageProcessor.dir/src/BlendNode.cpp.o -MF CMakeFiles/NodeBasedImageProcessor.dir/src/BlendNode.cpp.o.d -o CMakeFiles/NodeBasedImageProcessor.dir/src/BlendNode.cpp.o -c /home/siddharth/node-based-image-processor/src/BlendNode.cpp

CMakeFiles/NodeBasedImageProcessor.dir/src/BlendNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeBasedImageProcessor.dir/src/BlendNode.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/siddharth/node-based-image-processor/src/BlendNode.cpp > CMakeFiles/NodeBasedImageProcessor.dir/src/BlendNode.cpp.i

CMakeFiles/NodeBasedImageProcessor.dir/src/BlendNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeBasedImageProcessor.dir/src/BlendNode.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/siddharth/node-based-image-processor/src/BlendNode.cpp -o CMakeFiles/NodeBasedImageProcessor.dir/src/BlendNode.cpp.s

CMakeFiles/NodeBasedImageProcessor.dir/src/ImageProcessor.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/flags.make
CMakeFiles/NodeBasedImageProcessor.dir/src/ImageProcessor.cpp.o: /home/siddharth/node-based-image-processor/src/ImageProcessor.cpp
CMakeFiles/NodeBasedImageProcessor.dir/src/ImageProcessor.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/siddharth/node-based-image-processor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/NodeBasedImageProcessor.dir/src/ImageProcessor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeBasedImageProcessor.dir/src/ImageProcessor.cpp.o -MF CMakeFiles/NodeBasedImageProcessor.dir/src/ImageProcessor.cpp.o.d -o CMakeFiles/NodeBasedImageProcessor.dir/src/ImageProcessor.cpp.o -c /home/siddharth/node-based-image-processor/src/ImageProcessor.cpp

CMakeFiles/NodeBasedImageProcessor.dir/src/ImageProcessor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeBasedImageProcessor.dir/src/ImageProcessor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/siddharth/node-based-image-processor/src/ImageProcessor.cpp > CMakeFiles/NodeBasedImageProcessor.dir/src/ImageProcessor.cpp.i

CMakeFiles/NodeBasedImageProcessor.dir/src/ImageProcessor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeBasedImageProcessor.dir/src/ImageProcessor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/siddharth/node-based-image-processor/src/ImageProcessor.cpp -o CMakeFiles/NodeBasedImageProcessor.dir/src/ImageProcessor.cpp.s

CMakeFiles/NodeBasedImageProcessor.dir/src/NodeEditor.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/flags.make
CMakeFiles/NodeBasedImageProcessor.dir/src/NodeEditor.cpp.o: /home/siddharth/node-based-image-processor/src/NodeEditor.cpp
CMakeFiles/NodeBasedImageProcessor.dir/src/NodeEditor.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/siddharth/node-based-image-processor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/NodeBasedImageProcessor.dir/src/NodeEditor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeBasedImageProcessor.dir/src/NodeEditor.cpp.o -MF CMakeFiles/NodeBasedImageProcessor.dir/src/NodeEditor.cpp.o.d -o CMakeFiles/NodeBasedImageProcessor.dir/src/NodeEditor.cpp.o -c /home/siddharth/node-based-image-processor/src/NodeEditor.cpp

CMakeFiles/NodeBasedImageProcessor.dir/src/NodeEditor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeBasedImageProcessor.dir/src/NodeEditor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/siddharth/node-based-image-processor/src/NodeEditor.cpp > CMakeFiles/NodeBasedImageProcessor.dir/src/NodeEditor.cpp.i

CMakeFiles/NodeBasedImageProcessor.dir/src/NodeEditor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeBasedImageProcessor.dir/src/NodeEditor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/siddharth/node-based-image-processor/src/NodeEditor.cpp -o CMakeFiles/NodeBasedImageProcessor.dir/src/NodeEditor.cpp.s

CMakeFiles/NodeBasedImageProcessor.dir/src/Nodes.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/flags.make
CMakeFiles/NodeBasedImageProcessor.dir/src/Nodes.cpp.o: /home/siddharth/node-based-image-processor/src/Nodes.cpp
CMakeFiles/NodeBasedImageProcessor.dir/src/Nodes.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/siddharth/node-based-image-processor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/NodeBasedImageProcessor.dir/src/Nodes.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeBasedImageProcessor.dir/src/Nodes.cpp.o -MF CMakeFiles/NodeBasedImageProcessor.dir/src/Nodes.cpp.o.d -o CMakeFiles/NodeBasedImageProcessor.dir/src/Nodes.cpp.o -c /home/siddharth/node-based-image-processor/src/Nodes.cpp

CMakeFiles/NodeBasedImageProcessor.dir/src/Nodes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeBasedImageProcessor.dir/src/Nodes.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/siddharth/node-based-image-processor/src/Nodes.cpp > CMakeFiles/NodeBasedImageProcessor.dir/src/Nodes.cpp.i

CMakeFiles/NodeBasedImageProcessor.dir/src/Nodes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeBasedImageProcessor.dir/src/Nodes.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/siddharth/node-based-image-processor/src/Nodes.cpp -o CMakeFiles/NodeBasedImageProcessor.dir/src/Nodes.cpp.s

CMakeFiles/NodeBasedImageProcessor.dir/src/OutputNode.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/flags.make
CMakeFiles/NodeBasedImageProcessor.dir/src/OutputNode.cpp.o: /home/siddharth/node-based-image-processor/src/OutputNode.cpp
CMakeFiles/NodeBasedImageProcessor.dir/src/OutputNode.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/siddharth/node-based-image-processor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/NodeBasedImageProcessor.dir/src/OutputNode.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeBasedImageProcessor.dir/src/OutputNode.cpp.o -MF CMakeFiles/NodeBasedImageProcessor.dir/src/OutputNode.cpp.o.d -o CMakeFiles/NodeBasedImageProcessor.dir/src/OutputNode.cpp.o -c /home/siddharth/node-based-image-processor/src/OutputNode.cpp

CMakeFiles/NodeBasedImageProcessor.dir/src/OutputNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeBasedImageProcessor.dir/src/OutputNode.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/siddharth/node-based-image-processor/src/OutputNode.cpp > CMakeFiles/NodeBasedImageProcessor.dir/src/OutputNode.cpp.i

CMakeFiles/NodeBasedImageProcessor.dir/src/OutputNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeBasedImageProcessor.dir/src/OutputNode.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/siddharth/node-based-image-processor/src/OutputNode.cpp -o CMakeFiles/NodeBasedImageProcessor.dir/src/OutputNode.cpp.s

CMakeFiles/NodeBasedImageProcessor.dir/src/main.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/flags.make
CMakeFiles/NodeBasedImageProcessor.dir/src/main.cpp.o: /home/siddharth/node-based-image-processor/src/main.cpp
CMakeFiles/NodeBasedImageProcessor.dir/src/main.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/siddharth/node-based-image-processor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/NodeBasedImageProcessor.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeBasedImageProcessor.dir/src/main.cpp.o -MF CMakeFiles/NodeBasedImageProcessor.dir/src/main.cpp.o.d -o CMakeFiles/NodeBasedImageProcessor.dir/src/main.cpp.o -c /home/siddharth/node-based-image-processor/src/main.cpp

CMakeFiles/NodeBasedImageProcessor.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeBasedImageProcessor.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/siddharth/node-based-image-processor/src/main.cpp > CMakeFiles/NodeBasedImageProcessor.dir/src/main.cpp.i

CMakeFiles/NodeBasedImageProcessor.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeBasedImageProcessor.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/siddharth/node-based-image-processor/src/main.cpp -o CMakeFiles/NodeBasedImageProcessor.dir/src/main.cpp.s

CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/flags.make
CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui.cpp.o: /home/siddharth/node-based-image-processor/lib/imgui/imgui.cpp
CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/siddharth/node-based-image-processor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui.cpp.o -MF CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui.cpp.o.d -o CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui.cpp.o -c /home/siddharth/node-based-image-processor/lib/imgui/imgui.cpp

CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/siddharth/node-based-image-processor/lib/imgui/imgui.cpp > CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui.cpp.i

CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/siddharth/node-based-image-processor/lib/imgui/imgui.cpp -o CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui.cpp.s

CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_draw.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/flags.make
CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_draw.cpp.o: /home/siddharth/node-based-image-processor/lib/imgui/imgui_draw.cpp
CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_draw.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/siddharth/node-based-image-processor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_draw.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_draw.cpp.o -MF CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_draw.cpp.o.d -o CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_draw.cpp.o -c /home/siddharth/node-based-image-processor/lib/imgui/imgui_draw.cpp

CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_draw.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/siddharth/node-based-image-processor/lib/imgui/imgui_draw.cpp > CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_draw.cpp.i

CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_draw.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/siddharth/node-based-image-processor/lib/imgui/imgui_draw.cpp -o CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_draw.cpp.s

CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_tables.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/flags.make
CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_tables.cpp.o: /home/siddharth/node-based-image-processor/lib/imgui/imgui_tables.cpp
CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_tables.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/siddharth/node-based-image-processor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_tables.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_tables.cpp.o -MF CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_tables.cpp.o.d -o CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_tables.cpp.o -c /home/siddharth/node-based-image-processor/lib/imgui/imgui_tables.cpp

CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_tables.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_tables.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/siddharth/node-based-image-processor/lib/imgui/imgui_tables.cpp > CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_tables.cpp.i

CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_tables.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_tables.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/siddharth/node-based-image-processor/lib/imgui/imgui_tables.cpp -o CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_tables.cpp.s

CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_widgets.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/flags.make
CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_widgets.cpp.o: /home/siddharth/node-based-image-processor/lib/imgui/imgui_widgets.cpp
CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_widgets.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/siddharth/node-based-image-processor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_widgets.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_widgets.cpp.o -MF CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_widgets.cpp.o.d -o CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_widgets.cpp.o -c /home/siddharth/node-based-image-processor/lib/imgui/imgui_widgets.cpp

CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_widgets.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/siddharth/node-based-image-processor/lib/imgui/imgui_widgets.cpp > CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_widgets.cpp.i

CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_widgets.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/siddharth/node-based-image-processor/lib/imgui/imgui_widgets.cpp -o CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_widgets.cpp.s

CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_sdl2.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/flags.make
CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_sdl2.cpp.o: /home/siddharth/node-based-image-processor/lib/imgui/backends/imgui_impl_sdl2.cpp
CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_sdl2.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/siddharth/node-based-image-processor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_sdl2.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_sdl2.cpp.o -MF CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_sdl2.cpp.o.d -o CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_sdl2.cpp.o -c /home/siddharth/node-based-image-processor/lib/imgui/backends/imgui_impl_sdl2.cpp

CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_sdl2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_sdl2.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/siddharth/node-based-image-processor/lib/imgui/backends/imgui_impl_sdl2.cpp > CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_sdl2.cpp.i

CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_sdl2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_sdl2.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/siddharth/node-based-image-processor/lib/imgui/backends/imgui_impl_sdl2.cpp -o CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_sdl2.cpp.s

CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/flags.make
CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.o: /home/siddharth/node-based-image-processor/lib/imgui/backends/imgui_impl_opengl3.cpp
CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/siddharth/node-based-image-processor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.o -MF CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.o.d -o CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.o -c /home/siddharth/node-based-image-processor/lib/imgui/backends/imgui_impl_opengl3.cpp

CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/siddharth/node-based-image-processor/lib/imgui/backends/imgui_impl_opengl3.cpp > CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.i

CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/siddharth/node-based-image-processor/lib/imgui/backends/imgui_impl_opengl3.cpp -o CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.s

CMakeFiles/NodeBasedImageProcessor.dir/lib/imnodes/imnodes.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/flags.make
CMakeFiles/NodeBasedImageProcessor.dir/lib/imnodes/imnodes.cpp.o: /home/siddharth/node-based-image-processor/lib/imnodes/imnodes.cpp
CMakeFiles/NodeBasedImageProcessor.dir/lib/imnodes/imnodes.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/siddharth/node-based-image-processor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/NodeBasedImageProcessor.dir/lib/imnodes/imnodes.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeBasedImageProcessor.dir/lib/imnodes/imnodes.cpp.o -MF CMakeFiles/NodeBasedImageProcessor.dir/lib/imnodes/imnodes.cpp.o.d -o CMakeFiles/NodeBasedImageProcessor.dir/lib/imnodes/imnodes.cpp.o -c /home/siddharth/node-based-image-processor/lib/imnodes/imnodes.cpp

CMakeFiles/NodeBasedImageProcessor.dir/lib/imnodes/imnodes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeBasedImageProcessor.dir/lib/imnodes/imnodes.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/siddharth/node-based-image-processor/lib/imnodes/imnodes.cpp > CMakeFiles/NodeBasedImageProcessor.dir/lib/imnodes/imnodes.cpp.i

CMakeFiles/NodeBasedImageProcessor.dir/lib/imnodes/imnodes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeBasedImageProcessor.dir/lib/imnodes/imnodes.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/siddharth/node-based-image-processor/lib/imnodes/imnodes.cpp -o CMakeFiles/NodeBasedImageProcessor.dir/lib/imnodes/imnodes.cpp.s

CMakeFiles/NodeBasedImageProcessor.dir/lib/ImGuiFileDialog/ImGuiFileDialog.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/flags.make
CMakeFiles/NodeBasedImageProcessor.dir/lib/ImGuiFileDialog/ImGuiFileDialog.cpp.o: /home/siddharth/node-based-image-processor/lib/ImGuiFileDialog/ImGuiFileDialog.cpp
CMakeFiles/NodeBasedImageProcessor.dir/lib/ImGuiFileDialog/ImGuiFileDialog.cpp.o: CMakeFiles/NodeBasedImageProcessor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/siddharth/node-based-image-processor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/NodeBasedImageProcessor.dir/lib/ImGuiFileDialog/ImGuiFileDialog.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeBasedImageProcessor.dir/lib/ImGuiFileDialog/ImGuiFileDialog.cpp.o -MF CMakeFiles/NodeBasedImageProcessor.dir/lib/ImGuiFileDialog/ImGuiFileDialog.cpp.o.d -o CMakeFiles/NodeBasedImageProcessor.dir/lib/ImGuiFileDialog/ImGuiFileDialog.cpp.o -c /home/siddharth/node-based-image-processor/lib/ImGuiFileDialog/ImGuiFileDialog.cpp

CMakeFiles/NodeBasedImageProcessor.dir/lib/ImGuiFileDialog/ImGuiFileDialog.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeBasedImageProcessor.dir/lib/ImGuiFileDialog/ImGuiFileDialog.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/siddharth/node-based-image-processor/lib/ImGuiFileDialog/ImGuiFileDialog.cpp > CMakeFiles/NodeBasedImageProcessor.dir/lib/ImGuiFileDialog/ImGuiFileDialog.cpp.i

CMakeFiles/NodeBasedImageProcessor.dir/lib/ImGuiFileDialog/ImGuiFileDialog.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeBasedImageProcessor.dir/lib/ImGuiFileDialog/ImGuiFileDialog.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/siddharth/node-based-image-processor/lib/ImGuiFileDialog/ImGuiFileDialog.cpp -o CMakeFiles/NodeBasedImageProcessor.dir/lib/ImGuiFileDialog/ImGuiFileDialog.cpp.s

CMakeFiles/NodeBasedImageProcessor.dir/lib/tinyfiledialogs.c.o: CMakeFiles/NodeBasedImageProcessor.dir/flags.make
CMakeFiles/NodeBasedImageProcessor.dir/lib/tinyfiledialogs.c.o: /home/siddharth/node-based-image-processor/lib/tinyfiledialogs.c
CMakeFiles/NodeBasedImageProcessor.dir/lib/tinyfiledialogs.c.o: CMakeFiles/NodeBasedImageProcessor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/siddharth/node-based-image-processor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building C object CMakeFiles/NodeBasedImageProcessor.dir/lib/tinyfiledialogs.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/NodeBasedImageProcessor.dir/lib/tinyfiledialogs.c.o -MF CMakeFiles/NodeBasedImageProcessor.dir/lib/tinyfiledialogs.c.o.d -o CMakeFiles/NodeBasedImageProcessor.dir/lib/tinyfiledialogs.c.o -c /home/siddharth/node-based-image-processor/lib/tinyfiledialogs.c

CMakeFiles/NodeBasedImageProcessor.dir/lib/tinyfiledialogs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/NodeBasedImageProcessor.dir/lib/tinyfiledialogs.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/siddharth/node-based-image-processor/lib/tinyfiledialogs.c > CMakeFiles/NodeBasedImageProcessor.dir/lib/tinyfiledialogs.c.i

CMakeFiles/NodeBasedImageProcessor.dir/lib/tinyfiledialogs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/NodeBasedImageProcessor.dir/lib/tinyfiledialogs.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/siddharth/node-based-image-processor/lib/tinyfiledialogs.c -o CMakeFiles/NodeBasedImageProcessor.dir/lib/tinyfiledialogs.c.s

# Object files for target NodeBasedImageProcessor
NodeBasedImageProcessor_OBJECTS = \
"CMakeFiles/NodeBasedImageProcessor.dir/src/BlendNode.cpp.o" \
"CMakeFiles/NodeBasedImageProcessor.dir/src/ImageProcessor.cpp.o" \
"CMakeFiles/NodeBasedImageProcessor.dir/src/NodeEditor.cpp.o" \
"CMakeFiles/NodeBasedImageProcessor.dir/src/Nodes.cpp.o" \
"CMakeFiles/NodeBasedImageProcessor.dir/src/OutputNode.cpp.o" \
"CMakeFiles/NodeBasedImageProcessor.dir/src/main.cpp.o" \
"CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui.cpp.o" \
"CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_draw.cpp.o" \
"CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_tables.cpp.o" \
"CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_widgets.cpp.o" \
"CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_sdl2.cpp.o" \
"CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.o" \
"CMakeFiles/NodeBasedImageProcessor.dir/lib/imnodes/imnodes.cpp.o" \
"CMakeFiles/NodeBasedImageProcessor.dir/lib/ImGuiFileDialog/ImGuiFileDialog.cpp.o" \
"CMakeFiles/NodeBasedImageProcessor.dir/lib/tinyfiledialogs.c.o"

# External object files for target NodeBasedImageProcessor
NodeBasedImageProcessor_EXTERNAL_OBJECTS =

NodeBasedImageProcessor: CMakeFiles/NodeBasedImageProcessor.dir/src/BlendNode.cpp.o
NodeBasedImageProcessor: CMakeFiles/NodeBasedImageProcessor.dir/src/ImageProcessor.cpp.o
NodeBasedImageProcessor: CMakeFiles/NodeBasedImageProcessor.dir/src/NodeEditor.cpp.o
NodeBasedImageProcessor: CMakeFiles/NodeBasedImageProcessor.dir/src/Nodes.cpp.o
NodeBasedImageProcessor: CMakeFiles/NodeBasedImageProcessor.dir/src/OutputNode.cpp.o
NodeBasedImageProcessor: CMakeFiles/NodeBasedImageProcessor.dir/src/main.cpp.o
NodeBasedImageProcessor: CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui.cpp.o
NodeBasedImageProcessor: CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_draw.cpp.o
NodeBasedImageProcessor: CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_tables.cpp.o
NodeBasedImageProcessor: CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/imgui_widgets.cpp.o
NodeBasedImageProcessor: CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_sdl2.cpp.o
NodeBasedImageProcessor: CMakeFiles/NodeBasedImageProcessor.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.o
NodeBasedImageProcessor: CMakeFiles/NodeBasedImageProcessor.dir/lib/imnodes/imnodes.cpp.o
NodeBasedImageProcessor: CMakeFiles/NodeBasedImageProcessor.dir/lib/ImGuiFileDialog/ImGuiFileDialog.cpp.o
NodeBasedImageProcessor: CMakeFiles/NodeBasedImageProcessor.dir/lib/tinyfiledialogs.c.o
NodeBasedImageProcessor: CMakeFiles/NodeBasedImageProcessor.dir/build.make
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_alphamat.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_aruco.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_barcode.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_bgsegm.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_bioinspired.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_ccalib.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_cvv.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_dnn_objdetect.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_dnn_superres.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_dpm.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_face.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_freetype.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_fuzzy.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_hdf.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_hfs.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_img_hash.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_intensity_transform.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_line_descriptor.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_mcc.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_quality.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_rapid.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_reg.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_rgbd.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_saliency.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_shape.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_stereo.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_structured_light.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_surface_matching.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_tracking.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_viz.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_wechat_qrcode.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_xobjdetect.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_xphoto.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libSDL2.so
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libOpenGL.so
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libGLX.so
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libGLU.so
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_datasets.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_plot.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_text.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_phase_unwrapping.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_optflow.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_ximgproc.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_video.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_videoio.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_imgcodecs.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_dnn.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.4.6.0
NodeBasedImageProcessor: /usr/lib/x86_64-linux-gnu/libopencv_core.so.4.6.0
NodeBasedImageProcessor: CMakeFiles/NodeBasedImageProcessor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/siddharth/node-based-image-processor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking CXX executable NodeBasedImageProcessor"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/NodeBasedImageProcessor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/NodeBasedImageProcessor.dir/build: NodeBasedImageProcessor
.PHONY : CMakeFiles/NodeBasedImageProcessor.dir/build

CMakeFiles/NodeBasedImageProcessor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/NodeBasedImageProcessor.dir/cmake_clean.cmake
.PHONY : CMakeFiles/NodeBasedImageProcessor.dir/clean

CMakeFiles/NodeBasedImageProcessor.dir/depend:
	cd /home/siddharth/node-based-image-processor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/siddharth/node-based-image-processor /home/siddharth/node-based-image-processor /home/siddharth/node-based-image-processor/build /home/siddharth/node-based-image-processor/build /home/siddharth/node-based-image-processor/build/CMakeFiles/NodeBasedImageProcessor.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/NodeBasedImageProcessor.dir/depend

