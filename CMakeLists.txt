cmake_minimum_required(VERSION 3.10)
project(NodeBasedImageProcessor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenCV REQUIRED)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

# === Include paths ===
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/lib/imgui
    ${CMAKE_SOURCE_DIR}/lib/imgui/backends    # for imgui_impl_opengl3_loader.h
    ${CMAKE_SOURCE_DIR}/lib/imnodes
    ${CMAKE_SOURCE_DIR}/lib/ImGuiFileDialog
    ${CMAKE_SOURCE_DIR}/lib                  # for tinyfiledialogs.h
    ${SDL2_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
)

add_definitions(-DIMGUI_DEFINE_MATH_OPERATORS)

# === Gather your own src/ files ===
file(GLOB_RECURSE SRC_SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)
# Exclude the duplicated backends in src/
list(REMOVE_ITEM SRC_SOURCES
    "${CMAKE_SOURCE_DIR}/src/imgui_impl_sdl2.cpp"
    "${CMAKE_SOURCE_DIR}/src/imgui_impl_opengl3.cpp"
)

# === ImGui core ===
file(GLOB IMGUI_CORE
    "${CMAKE_SOURCE_DIR}/lib/imgui/imgui.cpp"
    "${CMAKE_SOURCE_DIR}/lib/imgui/imgui_draw.cpp"
    "${CMAKE_SOURCE_DIR}/lib/imgui/imgui_widgets.cpp"
    "${CMAKE_SOURCE_DIR}/lib/imgui/imgui_tables.cpp"
)

# === Exactly one set of backends ===
set(IMGUI_BACKENDS
    "${CMAKE_SOURCE_DIR}/lib/imgui/backends/imgui_impl_sdl2.cpp"
    "${CMAKE_SOURCE_DIR}/lib/imgui/backends/imgui_impl_opengl3.cpp"
)

# === ImNodes ===
file(GLOB IMNODES_SOURCES
    "${CMAKE_SOURCE_DIR}/lib/imnodes/imnodes.cpp"
)

# === File dialogs ===
file(GLOB IMGUIFILEDIALOG_SOURCES
    "${CMAKE_SOURCE_DIR}/lib/ImGuiFileDialog/ImGuiFileDialog.cpp"
)
file(GLOB TINYFILEDIALOGS
    "${CMAKE_SOURCE_DIR}/lib/tinyfiledialogs.c"
)

# === Combine everything ===
set(PROJECT_SOURCES
    ${SRC_SOURCES}
    ${IMGUI_CORE}
    ${IMGUI_BACKENDS}
    ${IMNODES_SOURCES}
    ${IMGUIFILEDIALOG_SOURCES}
    ${TINYFILEDIALOGS}
)

# === Build ===
add_executable(NodeBasedImageProcessor ${PROJECT_SOURCES})

target_link_libraries(NodeBasedImageProcessor
    ${OpenCV_LIBS}
    ${SDL2_LIBRARIES}
    ${OPENGL_LIBRARIES}
)

