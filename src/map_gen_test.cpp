#include <iostream>
#include "bfs.hpp"
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
            else if (map[y][x].treasure)
            {
                std::cout << "TT"; // On représente un trésor par deux T
            }
            else if (map[y][x].trap)
            {
                std::cout << "!!"; // On représente un piège par deux !
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


void printFlowField(const std::vector<std::vector<Bloc>>& map)
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
                switch (map[y][x].directionx)
                {
                case -1:
                    std::cout << "<";
                    break;
                case 1:
                    std::cout << ">";
                    break;                
                default:
                    std::cout << " ";
                    break;
                }
                switch (map[y][x].directiony)
                {
                case 1:
                    std::cout << "v";
                    break;
                case -1:
                    std::cout << "^";
                    break;                
                default:
                    std::cout << " ";
                    break;
                }
            }

        }
        std::cout << std::endl;
    }
}

void test_flow_field()
{
    std::vector<std::vector<Bloc>> map = generateMap();
    int start_x;
    int start_y;
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            if (map[i][j].type == Vide)
            {
                start_y = i;
                start_x = j;
            }
        }
    }
    inbound(start_x, start_y);
    bfs_flow_field(map, start_x, start_y);
    printMap(map);
    std::cout << std::endl;
    printFlowField(map);
}