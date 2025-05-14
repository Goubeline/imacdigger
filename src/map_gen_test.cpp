#include <iostream>
#include "map_gen.hpp"
#include "default_value.hpp"

// On affiche la carte dans le terminal pour tester
void printMap(const std::vector<std::vector<Bloc>>& map)
{
    for (int y = 0; y < MAP_HEIGHT; y++) 
    {
        for (int x = 0; x < MAP_WIDTH; x++) 
        {
            if (map[y][x].type == Mur)
            {
                std::cout << "##"; // On représente un mur par deux hashtags
            }
            else 
            {
                std::cout << "  ";  // On représente un vide par deux espaces
            }
        }
        std::cout << std::endl;
    }
}

int test_map()
{
    auto map = generateMap();
    printMap(map);
    
    return 0;
}