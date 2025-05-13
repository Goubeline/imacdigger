#pragma once

#include <vector>

enum Types
{
    Mur,
    Vide,
    Trésor,
    Piège
};

struct Bloc
{
    Types type;
    int directionx;
    int directiony;
};