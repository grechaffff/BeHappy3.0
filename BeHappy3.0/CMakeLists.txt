cmake_minimum_required(VERSION 3.14)
project(BeHappy3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем исходники
file(GLOB_RECURSE SRC_FILES src/*.cpp src/*.h)
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Подключаем SDL3
add_subdirectory(external/SDL)
target_link_libraries(${PROJECT_NAME} SDL3::SDL3-shared)

# Подключаем OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)

# Подключаем ImGui
add_library(imgui STATIC
    external/ImGui/imgui.cpp
    external/ImGui/imgui_demo.cpp
    external/ImGui/imgui_draw.cpp
    external/ImGui/imgui_tables.cpp
    external/ImGui/imgui_widgets.cpp
)
target_include_directories(imgui PUBLIC external/ImGui)

