#include <iostream>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "PhysicsEngine.h"

// Forward declaration of our future Vulkan system
class VulkanRenderer;
VulkanRenderer* renderer = nullptr;

// Window dimensions
const uint32_t WIDTH = 1280;
const uint32_t HEIGHT = 720;

GLFWwindow* window = nullptr;

// -------------------------
// Initialize GLFW + window
// -------------------------
void initWindow() {
    // Initialize GLFW library
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW!");
    }

    // We use Vulkan, so disable OpenGL
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    // Create the application window
    window = glfwCreateWindow(WIDTH, HEIGHT, "GPU Physics Benchmark Tool", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window!");
    }
}

// -------------------------
// Main render loop
// -------------------------
void mainLoop() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // In the future: ImGui update → Physics tick → Vulkan render
        // For now: just render one color
    }
}

// -------------------------
// Clean up memory
// -------------------------
void cleanup() {
    // Delete Vulkan renderer (if exists)
    if (renderer) {
        delete renderer;
    }

    // Destroy window and terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
}

// -------------------------
// Entry point
// -------------------------
int main() {
    try {
        std::cout << "Running GPU Physics Benchmark...\n";
        runPhysicsBenchmark(1'000'000); // 1 million particles
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
