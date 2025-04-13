cmake_minimum_required(VERSION 3.10)
project(NodeBasedImageProcessor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenCV REQUIRED)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/lib/imgui
    ${CMAKE_SOURCE_DIR}/lib/imgui/backends
    ${CMAKE_SOURCE_DIR}/lib/imnodes
    ${CMAKE_SOURCE_DIR}/lib/ImGuiFileDialog         # <--- For ImGuiFileDialog.h
    ${CMAKE_SOURCE_DIR}/lib                         # For tinyfiledialogs.h
    ${OpenCV_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
)

add_definitions(-DIMGUI_DEFINE_MATH_OPERATORS)

set(SOURCES
    src/main.cpp
    src/NodeEditor.cpp
    src/ImageProcessor.cpp
    src/Nodes.cpp
    src/OutputNode.cpp
    src/BlendNode.cpp
    src/imgui_impl_sdl2.cpp
    src/imgui_impl_opengl3.cpp

    lib/imgui/imgui.cpp
    lib/imgui/imgui_draw.cpp
    lib/imgui/imgui_widgets.cpp
    lib/imgui/imgui_tables.cpp

    lib/imnodes/imnodes.cpp

    lib/tinyfiledialogs.c
    lib/ImGuiFileDialog/ImGuiFileDialog.cpp         # <--- Add ImGuiFileDialog source
)

add_executable(NodeBasedImageProcessor ${SOURCES})

target_link_libraries(NodeBasedImageProcessor
    ${OpenCV_LIBS}
    ${SDL2_LIBRARIES}
    ${OPENGL_LIBRARIES}
)
