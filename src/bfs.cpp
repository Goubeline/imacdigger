#include "bfs.hpp"

#include <queue>

#include "default_value.hpp"

bool inbound(int x, int y)
{
}

void bfs(std::vector<std::vector<Bloc>>* map, int startx, int starty)
{
    std::pair<int, int> coordCurrent;
    Bloc current;
    std::vector<int> visited (MAP_HEIGHT * MAP_WIDTH , -1);

    std::queue<std::pair<int, int>> frontiere {};
    std::pair<int, int> origin = {startx, starty};
    frontiere.push(origin);
    visited[starty * MAP_WIDTH + startx] = 0;

    while(!frontiere.empty())
    {
        coordCurrent = frontiere.front();
        frontiere.pop();
        for (int y = std::get<1>(coordCurrent) - 1; y <= std::get<1>(coordCurrent) + 1; y++)
        {
            for (int x = std::get<0>(coordCurrent) - 1; x <= std::get<0>(coordCurrent) + 1; x++)
            {
                if (visited[y * MAP_WIDTH + x] == -1 || )
                {
                    /* code */
                }
                
            }
        }
        
    }
}