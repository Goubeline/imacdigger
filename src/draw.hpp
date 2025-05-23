#pragma once
#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/basic_mesh.hpp"

#include "bloc.hpp"

using namespace glbasimac;

void initScene();
void renderScene();

void onError(int error, const char* description);

int draw(std::vector<std::vector<Bloc>>& map);