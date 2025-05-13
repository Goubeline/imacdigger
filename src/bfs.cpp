#include "bfs.hpp"

#include <queue>
#include <tuple>
void bfs(std::vector<std::vector<Bloc>> carte, int x, int y)
{
    std::tuple<int, int> origin = {x, y};
    std::queue<std::tuple<int, int>> frontiere {};
    Bloc current;
    frontiere.push(origin);

    while(!frontiere.empty())
    {

    }
}