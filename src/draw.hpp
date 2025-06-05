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

struct PlayerMove
{
    bool left;
    bool right;
    bool down;
    bool up;
};

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

void initScene();
void renderScene();

void onError(int error, const char* description);

int draw(std::vector<std::vector<Bloc>>& map);