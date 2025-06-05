#include <GLFW/glfw3.h>
#include "end_screen.hpp"

int main() 
{
    if (!glfwInit())
    {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Test End Screen", NULL, NULL);
    if (!window) 
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Boucle d'affichage
    while (!glfwWindowShouldClose(window)) 
    {
        // Teste la victoire ou la défaite (on change le paramètre pour tester)
        displayEndScreen(Victoire); // ou Defaite

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}