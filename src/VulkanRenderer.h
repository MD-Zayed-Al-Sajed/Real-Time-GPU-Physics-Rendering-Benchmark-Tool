#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class VulkanRenderer {
public:
    VulkanRenderer(GLFWwindow* window);
    ~VulkanRenderer();

    void drawFrame(); // (Later) per-frame render

private:
    void initVulkan();
    void createInstance();

    GLFWwindow* window;
    VkInstance instance;
};
