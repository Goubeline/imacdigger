#include <random>
#include <algorithm>
#include <ctime>
#include <utility>
#include "map_gen.hpp"
#include "default_value.hpp"
#include "bfs.hpp"

const float wall_probability = 0.4f;

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

// On compte le nombre de voisins murs autour d’un bloc dans un rayon donné, y compris lui-même (version améliorée bonus)
int countWallNeighbors(const std::vector<std::vector<Bloc>>& map, int x, int y, int radius)
{
    int wall_count = 0;
    
    // On parcourt tous les voisins dans le carré de côté (2*radius)+1 centré sur (x, y)
    for (int dy = -radius; dy <= radius; dy++) 
    {
        for (int dx = -radius; dx <= radius; dx++) 
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

// Génération procédurale (version améliorée bonus)
std::vector<std::vector<Bloc>> applyCellularAutomata(const std::vector<std::vector<Bloc>>& map, int minWallsRadius1, int minWallsRadius2)
{
    std::vector<std::vector<Bloc>> new_map = map;

    for (int y = 0; y < MAP_HEIGHT; y++) 
    {
        for (int x = 0; x < MAP_WIDTH; x++) 
        {
            // Compte le nombre de murs dans un rayon de 1 autour du bloc (voisinage 3x3)
            int neighborWallsRadius1 = countWallNeighbors(map, x, y, 1);
            // Compte le nombre de murs dans un rayon de 2 autour du bloc (voisinage 5x5)
            int neighborWallsRadius2 = countWallNeighbors(map, x, y, 2);

            bool wall = false;

            // Si assez de murs dans le voisinage immédiat, on met un mur
            if (neighborWallsRadius1 >= minWallsRadius1) 
            {
                wall = true;
            }

            // Si le nombre de murs dans le grand voisinage est dans l'intervalle, on met aussi un mur
            if (neighborWallsRadius2 >= 0 && neighborWallsRadius2 <= minWallsRadius2) 
            {
                wall = true;
            }

            if (wall == true) 
            {
                new_map[y][x].type = Mur;
            } 
            else 
            {
                new_map[y][x].type = Vide;
            }
        }
    }

    return new_map;
}

// On ajoute des objets et pièges sur la carte
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
    
    // On ajoute des trésors sur 3% des cases vides
    int num_treasures = empty_positions.size() * 0.03;
    for (int i = 0; i < num_treasures && !empty_positions.empty(); i++)
    {
        auto [y, x] = empty_positions.back();
        empty_positions.pop_back();
        map[y][x].treasure = true;
    }

    // On ajoute des pièges sur 2% des cases vides
    int num_traps = empty_positions.size() * 0.02;
    for (int i = 0; i < num_traps && !empty_positions.empty(); i++)
    {
        auto [y, x] = empty_positions.back();
        empty_positions.pop_back();
        map[y][x].trap = true;
    }
}

// Effectue un flood fill pour déterminer la zone accessible
std::vector<std::vector<bool>> floodFill(const std::vector<std::vector<Bloc>>& map, int startX, int startY)
{
    std::vector<std::vector<Bloc>> mapCopy = map;

    // On calcule les distances depuis le point de départ avec la fonction de bfs.hpp
    auto distances = dist_vec(mapCopy, startX, startY);

    std::vector<std::vector<bool>> visited(MAP_HEIGHT, std::vector<bool>(MAP_WIDTH, false));

    // On parcourt toute la carte pour marquer comme visitées les cases accessibles
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            // Si la distance n'est pas infinie, la case est accessible depuis le point de départ
            visited[y][x] = (distances[y][x] != std::numeric_limits<int>::max());
        }
    }

    return visited;
}

// On cherche la plus grande zone accessible et on remplit les autres en murs
void keepLargestArea(std::vector<std::vector<Bloc>>& map)
{
    std::vector<std::vector<bool>> globalVisited(MAP_HEIGHT, std::vector<bool>(MAP_WIDTH, false));
    int maxAreaSize = 0;
    std::vector<std::vector<bool>> largestAreaVisited;

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            if (map[y][x].type == Vide && !globalVisited[y][x])
            {
                // Flood fill sur cette zone
                std::vector<std::vector<bool>> currentVisited = floodFill(map, x, y);

                // On compte la taille de cette zone
                int currentAreaSize = 0;
                for (int i = 0; i < MAP_HEIGHT; i++)
                {
                    for (int j = 0; j < MAP_WIDTH; j++)
                    {
                        if (currentVisited[i][j] == true)
                        {
                            currentAreaSize++;
                        }
                    }
                }

                // On marque comme visité dans globalVisited
                for (int i = 0; i < MAP_HEIGHT; i++)
                {
                    for (int j = 0; j < MAP_WIDTH; j++)
                    {
                        if (currentVisited[i][j] == true)
                        {
                            globalVisited[i][j] = true;
                        }
                    }
                }

                // On garde la plus grande zone trouvée
                if (currentAreaSize > maxAreaSize)
                {
                    maxAreaSize = currentAreaSize;
                    largestAreaVisited = std::move(currentVisited);
                }
            }
        }
    }

    // On remplit les zones non connectées en murs
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            if (map[y][x].type == Vide)
            {
                if (largestAreaVisited.empty() || !largestAreaVisited[y][x])
                {
                    map[y][x].type = Mur; // On supprime les zones isolées
                }
            }
        }
    }
}

// On génère la carte complète
std::vector<std::vector<Bloc>> generateMap()
{
    std::vector<std::vector<Bloc>> map;
    int maxAreaSize = 0;

    do {
        map = initializeMap();

        // Étape 1 : Nettoyage grossier avec minWallsRadius2
        for (int i = 0; i < 4; i++) 
        {
            map = applyCellularAutomata(map, 5, 2);
        }

        // Étape 2 : Nettoyage fin sans minWallsRadius2
        for (int i = 0; i < 3; i++) 
        {
            map = applyCellularAutomata(map, 5, -1);
        }

        populateMap(map);

        // On calcule la taille de la plus grande zone
        std::vector<std::vector<bool>> globalVisited(MAP_HEIGHT, std::vector<bool>(MAP_WIDTH, false));
        int maxArea = 0;

        // On parcourt toute la carte pour trouver toutes les zones accessibles (zones de vide connectées)
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            for (int x = 0; x < MAP_WIDTH; x++)
            {
            // Si la case est vide et pas encore visitée, on lance un flood fill pour explorer la zone
            if (map[y][x].type == Vide && !globalVisited[y][x])
            {
                auto visited = floodFill(map, x, y);
                int area = 0;

                // On compte la taille de la zone visitée et on marque les cases comme visitées
                for (int i = 0; i < MAP_HEIGHT; i++)
                {
                    for (int j = 0; j < MAP_WIDTH; j++)
                    {
                        if (visited[i][j] == true)
                        {
                        area++;
                        globalVisited[i][j] = true;
                        }
                    }
                }

                if (area > maxArea)
                {
                maxArea = area;
                }
            }
            }
        }
        
        maxAreaSize = maxArea;
    } while (maxAreaSize < (MAP_WIDTH * MAP_HEIGHT) * 0.45); // 45% minimum de vide

    keepLargestArea(map);
    
    return map;
}