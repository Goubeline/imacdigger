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
    std::vector<int, 2> direction;
};