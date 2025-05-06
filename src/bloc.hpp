#pragma once

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
    Bloc* direction;
};