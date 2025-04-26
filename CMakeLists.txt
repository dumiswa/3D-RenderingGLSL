cmake_minimum_required(VERSION 3.26)
project(MGE_CLion)

set(CMAKE_CXX_STANDARD 17)

# Collect all source files
file(GLOB_RECURSE SOURCES
        mge/*.h
        mge/*.cpp
)

# Add the executable
add_executable(MGE_CLion ${SOURCES} main.cpp
        MovingStructure.cpp
        MovingStructure.h
        FollowCamera.cpp
        FollowCamera.h
        mge/materials/TerrainMaterial.h
        mge/materials/TerrainMaterial.cpp
)

# 🔹 Ensure OpenGL and GLEW headers are included
include_directories(${CMAKE_SOURCE_DIR})
include_directories("C:/GLEW/include")

# 🔹 Find and link OpenGL
find_package(OpenGL REQUIRED)

# Set SFML directory and find package
set(SFML_DIR "C:/SFML/lib/cmake/SFML")
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(MGE_CLion PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

# 🔹 Use `glew32.lib` instead of `glew32s.lib` for dynamic linking
set(GLEW_LIBRARY "C:/GLEW/lib/Release/x64/glew32.lib")
link_directories("C:/GLEW/lib/Release/x64")

# 🔹 Link in the **correct order** (important for MinGW)
target_link_libraries(MGE_CLion PRIVATE ${GLEW_LIBRARY} opengl32 glu32)
