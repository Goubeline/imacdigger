#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/basic_mesh.hpp"

using namespace glbasimac;

static const double FRAMERATE_IN_SECONDS;
static float aspectRatio;
GLBI_Engine myEngine;

void initScene();
void renderScene();


void onError(int error, const char* description);
static const float GL_VIEW_SIZE = 20.;

void onWindowResized(GLFWwindow* /*window*/, int width, int height);
void key_callback(GLFWwindow* /*window*/, int key, int /*scancode*/, int action, int /*mods*/);

int draw();