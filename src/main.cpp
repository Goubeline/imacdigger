#include "map_gen.hpp"
#include "draw.hpp"

int main()
{
    auto map = generateMap();
    draw(map);

    // On trouve une position de départ valide pour le joueur
    auto pos = findValidStart(map);
    int startY = pos.first;
    int startX = pos.second;
    // Et on place le joueur à cette position (au centre du bloc)
    pos_joueur_x = startX + 0.5f;
    pos_joueur_y = startY + 0.5f;
}