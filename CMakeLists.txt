# Set CMake minimum version and project info
cmake_minimum_required(VERSION 3.21)
project(GPUBenchmarkTool LANGUAGES C CXX CUDA)

# Set C++ standard and CUDA architecture
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)

# Optional: Show all compile commands in the build folder (great for debugging)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set paths to Vulkan SDK using environment variable
set(VULKAN_SDK $ENV{VULKAN_SDK})

# ------------------------------
# Include GLFW from third_party
# ------------------------------
add_subdirectory(third_party/glfw)

# ------------------------------
# Add ImGui manually
# ------------------------------
file(GLOB IMGUI_SRC
     third_party/imgui/*.cpp
     third_party/imgui/backends/imgui_impl_glfw.cpp
     third_party/imgui/backends/imgui_impl_vulkan.cpp)

add_library(imgui STATIC ${IMGUI_SRC})
target_include_directories(imgui PUBLIC
  third_party/imgui
  third_party/imgui/backends
)

# ------------------------------
# Set up include directories
# ------------------------------
include_directories(
  ${VULKAN_SDK}/Include
  third_party/glfw/include
  third_party/imgui
  third_party/imgui/backends
  ${CMAKE_SOURCE_DIR}/src
)

# ------------------------------
# Link Vulkan and GLFW
# ------------------------------
link_directories(${VULKAN_SDK}/Lib)

# ------------------------------
# Source files
# ------------------------------
file(GLOB_RECURSE SRC_FILES
     src/*.cpp
     src/*.cu
     src/*.h
)

# ------------------------------
# Define main executable
# ------------------------------
add_executable(GPUBenchmarkTool ${SRC_FILES})

# ------------------------------
# Link all dependencies
# ------------------------------
target_link_libraries(GPUBenchmarkTool
  glfw
  imgui
  ${VULKAN_SDK}/Lib/vulkan-1.lib
)

# ------------------------------
# Compile options
# ------------------------------
target_compile_definitions(GPUBenchmarkTool PRIVATE IMGUI_IMPL_VULKAN_NO_PROTOTYPES)

# Ensure CUDA code compiles properly
set_target_properties(GPUBenchmarkTool PROPERTIES
  CUDA_SEPARABLE_COMPILATION ON
  CUDA_STANDARD 17
  CUDA_ARCHITECTURES "75;86;89;90"
)


