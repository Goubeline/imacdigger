#include "bfs.hpp"

#include <cmath>
#include <limits>
#include <queue>

#include "default_value.hpp"

bool inbound(int x, int y) { return (x >= 0 && x < MAP_WIDTH) && (y >= 0 && y < MAP_HEIGHT); }

float cos_angle(std::pair<int, int> center, std::pair<int, int> direction_1, std::pair<int, int> direction_2)
{
    //création des deux vecteurs
    std::pair<float, float> vec1 = {get<0>(direction_1) - get<0>(center), get<1>(direction_1) - get<1>(center)};
    std::pair<float, float> vec2 = {get<0>(direction_2) - get<0>(center), get<1>(direction_2) - get<1>(center)};

    //normalisation des vecteurs
    // norm_vec1
    // return direnction_1 - center / direction_2 - center / normalize
    // x1 * x2 / y1 * y2
}

void find_flow(std::vector<int>& distance, std::vector<std::vector<Bloc>>& map, std::pair<int, int> start, std::pair<int, int> current)
{
    int current_x = get<0>(current);
    int current_y = get<1>(current);
    int min = distance[current_y * MAP_WIDTH + current_x];

    for (int y = current_y - 1; y < current_y + 1; y++)
    {
        for (int x = current_x - 1; x < current_x + 1; x++)
        {
            if (inbound(x, y))
            {
                
            }
            
        }
    }
    
}

    ///// Disrance from start (player position) for all tile (max int if not reachable) /////
std::vector<std::vector<int>> dist_vec(std::vector<std::vector<Bloc>>& map, int start_x, int start_y)
{
    int current_x;
    int current_y;
    std::vector<std::vector<int>> distance (MAP_HEIGHT, std::vector<int> (MAP_WIDTH , std::numeric_limits<int>::max()));

    std::queue<std::pair<int, int>> frontiere {};
    frontiere.push({start_x, start_y});
    distance[start_y][start_x] = 0;

    while(!frontiere.empty())
    {
        current_x = get<0>(frontiere.front());
        current_y = get<1>(frontiere.front());
        frontiere.pop();
        for (int y = -1; y <= 1; y++)
        {
            int neighbor_y = current_y + y;
            for (int x = std::abs(y) - 1; x <= std::abs(y) + 1; x++)
            {
                int neighbor_x = current_x + x;
                if (inbound(neighbor_x, neighbor_y) && distance[neighbor_y][neighbor_x] == std::numeric_limits<int>::max()
                                                    && map[neighbor_y][neighbor_x].type == Vide)
                {
                    frontiere.push({neighbor_x, neighbor_y});
                    distance[neighbor_y][neighbor_x] = distance[current_y][current_x] + 1;
                }
            }
        }
    }
    return distance;
}

void flow_field(std::vector<std::vector<int>>& distance, std::vector<std::vector<Bloc>>& map, int start_x, int start_y)
{
    int min;
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            if (distance[y][x] != std::numeric_limits<int>::max())
            {

            }
            
        }
        
    }
    
}

void bfs(std::vector<std::vector<Bloc>>& map, int start_x, int start_y)
{
    std::vector<std::vector<int>> distance = dist_vec(map, start_x, start_y);

}