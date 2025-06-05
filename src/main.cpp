#include "map_gen.hpp"
#include "draw.hpp"

int main()
{
    auto map = generateMap();
    draw(map);
}