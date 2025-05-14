#define GLFW_INCLUDE_NONE
#include "draw.hpp"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "default_value.hpp"
#include "bloc.hpp"
#include "map_gen.hpp"
#include <iostream>
#include <cmath>

using namespace glbasimac;

std::vector<float> Coords_bloc{-10,10,-9,10,-9,9,-10,9};
GLBI_Convex_2D_Shape bloc {};

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;
static float aspectRatio = 1.0f;

/* OpenGL Engine */
GLBI_Engine myEngine;

void initScene(){
    bloc.initShape(Coords_bloc);
}

void draw_map(){
    //à faire
}

void renderScene(){
    //à faire
}

/* Error handling function */
void onError(int error, const char* description) {
	std::cout << "GLFW Error ("<<error<<") : " << description << std::endl;
}

/* Espace virtuel */
static const float GL_VIEW_SIZE = 20.;

void onWindowResized(GLFWwindow* window, int width, int height){
	aspectRatio = width / (float) height;
	 glViewport(0, 0, width, height);
	 if( aspectRatio > 1.0){
		myEngine.set2DProjection(-GL_VIEW_SIZE * aspectRatio/ 2., GL_VIEW_SIZE * aspectRatio / 2. ,-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
	}
	else {
		myEngine.set2DProjection(-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2., -GL_VIEW_SIZE / (2. * aspectRatio), GL_VIEW_SIZE / (2. * aspectRatio));
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	
}

int draw() {
    // Initialize the library
    if (!glfwInit()) {
        return -1;
    }
    /* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);
    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(MAP_WIDTH, MAP_HEIGHT, "", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    // Make the window's context current
    glfwMakeContextCurrent(window);
	// Intialize glad (loads the OpenGL functions)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}
	// Initialize Rendering Engine
	myEngine.initGL();
	initScene();
	glfwSetWindowSizeCallback(window, onWindowResized);
	onWindowResized(window, MAP_WIDTH, MAP_HEIGHT);
	// glfwSetKeyCallback(window, key_callback);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();
		/* Render here */
		glClearColor(0.1f,0.1f,0.1f,0.f);
		glClear(GL_COLOR_BUFFER_BIT);
        // render here
		renderScene();
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
		/* Elapsed time computation from loop begining */
		double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		while(elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
			elapsedTime = glfwGetTime() - startTime;
		}
	}
    glfwTerminate();
    return 0;
}