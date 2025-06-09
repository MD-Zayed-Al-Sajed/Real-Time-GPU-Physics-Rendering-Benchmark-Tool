#include <iostream>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "PhysicsEngine.h"
#include "VulkanRenderer.h"

// Global Vulkan renderer
VulkanRenderer* renderer = nullptr;

// Window dimensions
const uint32_t WIDTH = 1280;
const uint32_t HEIGHT = 720;
GLFWwindow* window = nullptr;

// -------------------------
// Initialize GLFW window
// -------------------------
void initWindow() {
    if (!glfwInit()) {
        throw std::runtime_error("❌ Failed to initialize GLFW!");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);  // No OpenGL context
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "GPU Physics Benchmark Tool", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("❌ Failed to create GLFW window!");
    }
}

// -------------------------
// Main render loop
// -------------------------
void mainLoop() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // (In the future) Render frame
         renderer->drawFrame();
    }
}

// -------------------------
// Clean up resources
// -------------------------
void cleanup() {
    delete renderer;

    glfwDestroyWindow(window);
    glfwTerminate();
}

// -------------------------
// Entry Point
// -------------------------
int main() {
    try {
        std::cout << "🚀 Running GPU Physics Benchmark...\n";

        // Step 1: Initialize Window
        initWindow();

        // Step 2: Run CUDA benchmark (1M particles)
        runPhysicsBenchmark(1'000'000);  // Optional: move this to ImGui later

        // Step 3: Initialize Vulkan renderer
        renderer = new VulkanRenderer(window);

        // Step 4: Start event/render loop
        mainLoop();

        // Step 5: Clean shutdown
        cleanup();

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "❌ Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
