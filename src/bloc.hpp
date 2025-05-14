#pragma once

#include <vector>

enum Types
{
    Mur,
    Vide
};

struct Bloc
{
    Types type;
    int directionx;
    int directiony;
    bool trap;
    bool treasure;
};