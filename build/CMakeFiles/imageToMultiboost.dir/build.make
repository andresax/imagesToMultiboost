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
CMAKE_SOURCE_DIR = /home/andrea/workspaceC/imagesToMultiboost

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/andrea/workspaceC/imagesToMultiboost/build

# Include any dependencies generated for this target.
include CMakeFiles/imageToMultiboost.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/imageToMultiboost.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/imageToMultiboost.dir/flags.make

CMakeFiles/imageToMultiboost.dir/src/Main.cpp.o: CMakeFiles/imageToMultiboost.dir/flags.make
CMakeFiles/imageToMultiboost.dir/src/Main.cpp.o: ../src/Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrea/workspaceC/imagesToMultiboost/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/imageToMultiboost.dir/src/Main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/imageToMultiboost.dir/src/Main.cpp.o -c /home/andrea/workspaceC/imagesToMultiboost/src/Main.cpp

CMakeFiles/imageToMultiboost.dir/src/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imageToMultiboost.dir/src/Main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrea/workspaceC/imagesToMultiboost/src/Main.cpp > CMakeFiles/imageToMultiboost.dir/src/Main.cpp.i

CMakeFiles/imageToMultiboost.dir/src/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imageToMultiboost.dir/src/Main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrea/workspaceC/imagesToMultiboost/src/Main.cpp -o CMakeFiles/imageToMultiboost.dir/src/Main.cpp.s

CMakeFiles/imageToMultiboost.dir/src/Main.cpp.o.requires:

.PHONY : CMakeFiles/imageToMultiboost.dir/src/Main.cpp.o.requires

CMakeFiles/imageToMultiboost.dir/src/Main.cpp.o.provides: CMakeFiles/imageToMultiboost.dir/src/Main.cpp.o.requires
	$(MAKE) -f CMakeFiles/imageToMultiboost.dir/build.make CMakeFiles/imageToMultiboost.dir/src/Main.cpp.o.provides.build
.PHONY : CMakeFiles/imageToMultiboost.dir/src/Main.cpp.o.provides

CMakeFiles/imageToMultiboost.dir/src/Main.cpp.o.provides.build: CMakeFiles/imageToMultiboost.dir/src/Main.cpp.o


# Object files for target imageToMultiboost
imageToMultiboost_OBJECTS = \
"CMakeFiles/imageToMultiboost.dir/src/Main.cpp.o"

# External object files for target imageToMultiboost
imageToMultiboost_EXTERNAL_OBJECTS =

imageToMultiboost: CMakeFiles/imageToMultiboost.dir/src/Main.cpp.o
imageToMultiboost: CMakeFiles/imageToMultiboost.dir/build.make
imageToMultiboost: /usr/local/lib/libopencv_cudabgsegm.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_cudaobjdetect.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_cudastereo.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_stitching.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_superres.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_videostab.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_aruco.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_bgsegm.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_bioinspired.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_ccalib.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_dpm.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_freetype.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_fuzzy.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_hdf.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_line_descriptor.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_optflow.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_reg.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_saliency.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_stereo.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_structured_light.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_surface_matching.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_tracking.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_xfeatures2d.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_ximgproc.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_xobjdetect.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_xphoto.so.3.2.0
imageToMultiboost: /usr/lib/x86_64-linux-gnu/libboost_system.so
imageToMultiboost: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
imageToMultiboost: /usr/local/lib/libopencv_cudafeatures2d.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_shape.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_cudacodec.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_cudaoptflow.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_cudalegacy.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_cudawarping.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_phase_unwrapping.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_rgbd.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_calib3d.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_video.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_datasets.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_dnn.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_face.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_plot.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_text.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_features2d.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_flann.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_objdetect.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_ml.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_highgui.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_photo.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_cudaimgproc.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_cudafilters.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_cudaarithm.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_videoio.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_imgcodecs.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_imgproc.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_core.so.3.2.0
imageToMultiboost: /usr/local/lib/libopencv_cudev.so.3.2.0
imageToMultiboost: CMakeFiles/imageToMultiboost.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/andrea/workspaceC/imagesToMultiboost/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable imageToMultiboost"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/imageToMultiboost.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/imageToMultiboost.dir/build: imageToMultiboost

.PHONY : CMakeFiles/imageToMultiboost.dir/build

CMakeFiles/imageToMultiboost.dir/requires: CMakeFiles/imageToMultiboost.dir/src/Main.cpp.o.requires

.PHONY : CMakeFiles/imageToMultiboost.dir/requires

CMakeFiles/imageToMultiboost.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/imageToMultiboost.dir/cmake_clean.cmake
.PHONY : CMakeFiles/imageToMultiboost.dir/clean

CMakeFiles/imageToMultiboost.dir/depend:
	cd /home/andrea/workspaceC/imagesToMultiboost/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andrea/workspaceC/imagesToMultiboost /home/andrea/workspaceC/imagesToMultiboost /home/andrea/workspaceC/imagesToMultiboost/build /home/andrea/workspaceC/imagesToMultiboost/build /home/andrea/workspaceC/imagesToMultiboost/build/CMakeFiles/imageToMultiboost.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/imageToMultiboost.dir/depend
