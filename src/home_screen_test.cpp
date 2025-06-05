#include <GLFW/glfw3.h>
#include "home_screen.hpp"
#include "default_value.hpp"

int main() 
{
    if (!glfwInit())
    {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Test Home Screen", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Boucle d'affichage
    while (!glfwWindowShouldClose(window)) 
    {
        displayHomeScreen();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}