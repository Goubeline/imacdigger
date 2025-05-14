#include <random>
#include <algorithm>
#include <ctime>
#include <utility>
#include "map_gen.hpp"
#include "default_value.hpp"

const int iterations = 4;
const float wall_probability = 0.5f;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, 1);

// On initialise la carte avec des murs et des vides aléatoires
std::vector<std::vector<Bloc>> initializeMap()
{
    std::vector<std::vector<Bloc>> map(MAP_HEIGHT, std::vector<Bloc>(MAP_WIDTH));

    for (int y = 0; y < MAP_HEIGHT; y++) 
    {
        for (int x = 0; x < MAP_WIDTH; x++) 
        {
            if (dis(gen) < wall_probability) 
            {
                map[y][x].type = Mur;
            } 
            else 
            {
                map[y][x].type = Vide;
            }
        }
    }

    return map;
}

// On compte le nombre de voisins murs autour d’une bloc (y compris lui-même)
int countWallNeighbors(const std::vector<std::vector<Bloc>>& map, int x, int y)
{
    int wall_count = 0;
    
    // On vérifie les 8 voisins autour de (x, y)
    for (int dy = -1; dy <= 1; dy++) 
    {
        for (int dx = -1; dx <= 1; dx++) 
        {
            int nx = x + dx;
            int ny = y + dy;

            // Si on est à l'extérieur de la carte, on considère comme un mur
            if (nx < 0 || nx >= MAP_WIDTH || ny < 0 || ny >= MAP_HEIGHT) 
            {
                wall_count++;
            } 
            else if (map[ny][nx].type == Mur) 
            {
                wall_count++;
            }
        }
    }

    return wall_count;
}

std::vector<std::vector<Bloc>> applyCellularAutomata(const std::vector<std::vector<Bloc>>& map)
{
    std::vector<std::vector<Bloc>> new_map = map;

    for (int y = 0; y < MAP_HEIGHT; y++) 
    {
        for (int x = 0; x < MAP_WIDTH; x++) 
        {
            int walls = countWallNeighbors(map, x, y);
            if (map[y][x].type == Mur) 
            {
                walls -= 1; // Ne pas compter elle-même
            }

            if (map[y][x].type == Mur) 
            {
                // Si Mur et au moins 4 voisins pleins, reste Mur, sinon devient Vide
                if (walls >= 4) 
                {
                    new_map[y][x].type = Mur;
                } 
                else 
                {
                    new_map[y][x].type = Vide;
                }
            } 
            else 
            {
                // Si Vide et plus de 4 voisins pleins, devient Mur
                if (walls > 4) 
                {
                    new_map[y][x].type = Mur;
                } 
                else 
                {
                    new_map[y][x].type = Vide;
                }
            }
        }
    }

    return new_map;
}

// On ajoute des objets, pièges et ennemis sur la carte
void populateMap(std::vector<std::vector<Bloc>>& map)
{
    // On liste les positions vides
    std::vector<std::pair<int, int>> empty_positions;

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            if (map[y][x].type == Vide)
            {
                empty_positions.emplace_back(y, x);
            }
        }
    }

    // On mélange les positions vides pour une distribution aléatoire
    std::srand(std::time(nullptr));
    std::shuffle(empty_positions.begin(), empty_positions.end(), gen);
    
    // On ajoute des trésors sur 5% des cases vides
    int num_treasures = empty_positions.size() * 0.05;
    for (int i = 0; i < num_treasures && !empty_positions.empty(); i++)
    {
        auto [y, x] = empty_positions.back();
        empty_positions.pop_back();
        map[y][x].treasure = true;
    }

    // On ajoute des pièges sur 3% des cases vides
    int num_traps = empty_positions.size() * 0.03;
    for (int i = 0; i < num_traps && !empty_positions.empty(); i++)
    {
        auto [y, x] = empty_positions.back();
        empty_positions.pop_back();
        map[y][x].trap = true;
    }
}

// On génère la carte complète en appliquant plusieurs itérations de l'algo
std::vector<std::vector<Bloc>> generateMap()
{
    auto map = initializeMap();
    for (int i = 0; i < iterations; i++) 
    {
        map = applyCellularAutomata(map);
    }

    populateMap(map);
    
    return map;
}