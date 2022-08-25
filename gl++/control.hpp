#ifndef CONTROL_HPP
#define CONTROL_HPP
#include <GLFW/glfw3.h>

namespace control {

void processInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
}

void initControl(GLFWwindow* window) {
    glfwSetKeyCallback(window, (GLFWkeyfun)control::processInput);
}

#endif