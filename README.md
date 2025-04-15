# Node-Based Image Processor

## Overview
This project is a node-based image manipulation interface developed for the "Node-Based Image Manipulation Interface Assignment." Implemented in C++ using OpenCV for image processing, ImGui for the UI, and ImNodes for the node editor, the application allows users to load images, process them through a configurable pipeline of nodes, and save the results. The interface mirrors node-based editors like Substance Designer, offering a visual and flexible workflow for image manipulation.

## Features Implemented

### Core Functionality
- **Canvas Area**: A node editor canvas for creating and connecting nodes.
- **Properties Panel**: Adjustable parameters for each node (e.g., sliders for brightness, threshold).
- **File Operations**: Load images (JPG, PNG, BMP) and save processed results with format/quality options.
- **Real-Time Preview**: Updates node outputs as parameters change.

### Node System
- **Input Node**: Loads images with metadata.
- **Output Node**: Saves and previews results.
- **Processing Nodes**: Connectable pipeline with 10 required nodes.

### Required Nodes
#### Basic Nodes
1. **Image Input Node**
   - Loads images from the filesystem (JPG, PNG, BMP).
   - Displays metadata (dimensions).
   - Features a "Browse" button for file selection.
2. **Output Node**
   - Saves processed images (PNG, JPG) with quality settings (1-100).
   - Displays a real-time preview.
3. **Brightness/Contrast Node**
   - Adjusts brightness (-100 to +100) and contrast (0 to 3) with sliders.
   - Includes reset buttons for each parameter.
4. **Color Channel Splitter**
   - Splits RGB/RGBA into separate channel outputs.
   - Option to output grayscale channel representations.

#### Intermediate Nodes
5. **Blur Node**
   - Applies Gaussian blur with configurable radius (1-20px).
   - Supports uniform or directional blur.
   - Previews the kernel effect.
6. **Threshold Node**
   - Converts to binary image with adjustable threshold.
   - Supports binary, adaptive, and Otsu methods.
   - Displays a histogram for threshold selection.
7. **Edge Detection Node**
   - Implements Sobel and Canny edge detection.
   - Configurable thresholds and kernel size.
   - Option to overlay edges on the original image.
8. **Blend Node**
   - Combines two images with modes (normal, multiply, screen, overlay, difference).
   - Includes an opacity/mix slider (0-1).
   - Supports manual image loading for the second input.

#### Advanced Nodes
9. **Noise Generation Node**
   - Generates Perlin, Simplex, or Worley noise.
   - Configurable scale, octaves, and persistence.
   - Option for displacement map or color output.
10. **Convolution Filter Node**
    - Supports 3x3 or 5x5 custom kernel definition.
    - Includes presets (sharpen, emboss, edge enhance).
    - Provides visual feedback of kernel effect.

### Technical Features
- **Graph Execution**: Detects circular dependencies, processes in order, and caches results.
- **Error Handling**: Manages invalid connections and operations (e.g., empty inputs).
- **Memory Management**: Uses `std::unique_ptr` for nodes and proper texture cleanup.

## Technical Requirements
- **Language**: C++ (C++17).
- **Libraries**:
  - **OpenCV**: Version 4.6.0+ for image processing.
    - **Installation Path**: `/usr/local/` (system-wide) or `~/opencv/build/` (local build).
    - **GitHub**: [https://github.com/opencv/opencv](https://github.com/opencv/opencv)
    - **Install Command**: `sudo apt-get install libopencv-dev` or build from source with `cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local .. && sudo make install`.
  - **ImGui**: Dear ImGui library for UI.
    - **Installation Path**: `lib/ImGui` (project directory) or `/usr/local/include/imgui`.
    - **GitHub**: [https://github.com/ocornut/imgui](https://github.com/ocornut/imgui)
    - **Install Command**: Clone to `lib/ImGui` with `git clone https://github.com/ocornut/imgui lib/ImGui`.
  - **ImNodes**: Node editor extension for ImGui.
    - **Installation Path**: `lib/ImNodes` (project directory).
    - **GitHub**: [https://github.com/Nelarius/imnodes](https://github.com/Nelarius/imnodes)
    - **Install Command**: Clone to `lib/ImNodes` with `git clone https://github.com/Nelarius/imnodes lib/ImNodes`.
  - **SDL2**: Windowing and input handling.
    - **Installation Path**: `/usr/lib/x86_64-linux-gnu/` (system-wide).
    - **GitHub**: [https://github.com/libsdl-org/SDL](https://github.com/libsdl-org/SDL)
    - **Install Command**: `sudo apt-get install libsdl2-dev`.
  - **GLEW**: OpenGL Extension Wrangler Library.
    - **Installation Path**: `/usr/lib/x86_64-linux-gnu/` (system-wide).
    - **GitHub**: [https://github.com/nigels-com/glew](https://github.com/nigels-com/glew)
    - **Install Command**: `sudo apt-get install libglew-dev`.
  - **ImGuiFileDialog**: File dialog library for ImGui.
    - **Installation Path**: `lib/ImGuiFileDialog` (project directory).
    - **GitHub**: [https://github.com/aiekick/ImGuiFileDialog](https://github.com/aiekick/ImGuiFileDialog)
    - **Install Command**: Clone to `lib/ImGuiFileDialog` with `git clone https://github.com/aiekick/ImGuiFileDialog lib/ImGuiFileDialog`.
  - **tinyfiledialogs**: Alternative file dialog library.
    - **Installation Path**: `lib/` (project directory).
    - **GitHub**: [https://github.com/native-toolkit/tinyfiledialogs](https://github.com/native-toolkit/tinyfiledialogs)
    - **Install Command**: Download `tinyfiledialogs.c` and `tinyfiledialogs.h` to `lib/` with `wget https://raw.githubusercontent.com/native-toolkit/tinyfiledialogs/master/tinyfiledialogs.c -P lib/ && wget https://raw.githubusercontent.com/native-toolkit/tinyfiledialogs/master/tinyfiledialogs.h -P lib/`.
- **Graph System**:
  - Circular dependency detection via graph traversal.
  - Topological sorting for node evaluation.
  - Result caching to optimize performance.

## Installation

### Prerequisites
- **Kubuntu/Ubuntu**:
  ```bash
  sudo apt-get update
  sudo apt-get install cmake g++ libopencv-dev libsdl2-dev libglew-dev