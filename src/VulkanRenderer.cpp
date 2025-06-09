#include "VulkanRenderer.h"
#include <stdexcept>
#include <iostream>
#include <vector>

VulkanRenderer::VulkanRenderer(GLFWwindow* win) : window(win) {
    initVulkan();
}

VulkanRenderer::~VulkanRenderer() {
    vkDestroyInstance(instance, nullptr);
}

// Initialize all Vulkan parts
void VulkanRenderer::initVulkan() {
    createInstance();
}

// Create Vulkan instance (basic)
void VulkanRenderer::createInstance() {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "GPU Benchmark Tool";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "CustomEngine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_3;

    // Required extensions from GLFW
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Vulkan instance!");
    }

    std::cout << "✅ Vulkan instance created.\n";
}

void VulkanRenderer::drawFrame() {
    // Temporary stub (we'll fill this in later with Vulkan draw commands)
    std::cout << "[Frame] drawFrame() called.\n";
}