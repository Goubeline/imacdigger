#include "map_gen_test.hpp"
#include "map_gen.hpp"
#include "draw.hpp"

int main()
{
    auto map = generateMap();
    draw(map);
}