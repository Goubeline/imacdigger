#include "bfs.hpp"

#include <queue>
#include <tuple>

void bfs(std::vector<std::vector<Bloc>> carte, int startx, int starty)
{
    std::tuple<int, int> origin = {startx, starty};
    std::queue<std::tuple<int, int>> frontiere {};
    Bloc current;
    frontiere.push(origin);
    std::vector<bool> visited (100 ,false);

    while(!frontiere.empty())
    {

    }
}