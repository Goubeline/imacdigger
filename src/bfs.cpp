#include "bfs.hpp"

#include <cmath>
#include <limits>
#include <queue>

#include "default_value.hpp"

bool inbound(int x, int y) { return (x >= 0 && x < MAP_WIDTH) && (y >= 0 && y < MAP_HEIGHT); }

float calculateAngle(std::vector<float> vec1, std::vector<float> vec2)
{
    double dotProduct = vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2];
    double magnitudeU = sqrt(vec1[0] * vec1[0] + vec1[1] * vec1[1] + vec1[2] * vec1[2]);
    double magnitudeV = sqrt(vec2[0] * vec2[0] + vec2[1] * vec2[1] + vec2[2] * vec2[2]);

    double cosineTheta = dotProduct / (magnitudeU * magnitudeV);
    return acos(cosineTheta);
}

void find_flow(std::vector<std::vector<int>>& distances, std::vector<std::vector<Bloc>>& map, std::pair<int, int> start, std::pair<int, int> current)
{
    int current_x = get<0>(current);
    int current_y = get<1>(current);
    float min = distances[current_y][current_x];
    float to_test;
    int min_dir_y;
    int min_dir_x;

    for (int y = current_y - 1; y <= current_y + 1; y++)
    {
        for (int x = current_x - 1; x <= current_x + 1; x++)
        {
            if (inbound(x, y))
            {
                to_test = distances[y][x];

                //diagonale ?
                if (x - current_x != 0 && y - current_y != 0)
                {
                    //diagonale non atteignable
                    if (distances[y][current_x] == std::numeric_limits<int>::max()
                        && distances[current_y][x] == std::numeric_limits<int>::max())
                        continue;
                    to_test += 0.5;
                }

                //angle entre start, current et le bloc en cours de test
                std::vector<float> vecDir = {static_cast<float>(current_x) - x, static_cast<float>(current_y) - y};
                std::vector<float> vecStart = {static_cast<float>(current_x) - get<0>(start), static_cast<float>(current_y) - get<1>(start)};
                if (std::abs(calculateAngle(vecDir, vecStart)) > M_PI / 6)
                    to_test ++;
                               
                if (to_test < min)
                {
                    min = to_test;
                    min_dir_x = x - current_x;
                    min_dir_y = y - current_y;
                }
            }
        }
    }
    map[current_y][current_x].directionx = min_dir_x;    
    map[current_y][current_x].directiony = min_dir_y;    
}

    ///// Disrance from start (player position) for all tiles (max int if not reachable) /////
std::vector<std::vector<int>> dist_vec(std::vector<std::vector<Bloc>>& map, int start_x, int start_y)
{
    int current_x;
    int current_y;
    std::vector<std::vector<int>> distances (MAP_HEIGHT, std::vector<int> (MAP_WIDTH , std::numeric_limits<int>::max()));

    std::queue<std::pair<int, int>> frontiere {};
    frontiere.push({start_x, start_y});
    distances[start_y][start_x] = 0;

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
                if (inbound(neighbor_x, neighbor_y) && distances[neighbor_y][neighbor_x] == std::numeric_limits<int>::max()
                                                    && map[neighbor_y][neighbor_x].type == Vide)
                {
                    frontiere.push({neighbor_x, neighbor_y});
                    distances[neighbor_y][neighbor_x] = distances[current_y][current_x] + 1;
                }
            }
        }
    }
    return distances;
}

void flow_field(std::vector<std::vector<int>>& distances, std::vector<std::vector<Bloc>>& map, std::pair<int, int> start)
{
    int min;
    std::pair<int, int> current;
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            if (distances[y][x] != std::numeric_limits<int>::max())
            {
                current = {x, y};
                find_flow(distances, map, start, current);
            }
            
        }   
    }
}

void bfs_flow_field(std::vector<std::vector<Bloc>>& map, int start_x, int start_y)
{
    std::vector<std::vector<int>> distances = dist_vec(map, start_x, start_y);
    std::pair<int, int> start = {start_x, start_y};
    flow_field(distances, map, start);
}