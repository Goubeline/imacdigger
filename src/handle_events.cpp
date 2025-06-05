#include "handle_events.hpp"
#include "default_value.hpp"

void handle_events(std::vector<std::vector<Bloc>>& map, float pos_joueur_x, float pos_joueur_y)
{
    if (map[int(pos_joueur_y)][(int)pos_joueur_x].trap)
    {
        perdu = true;
    }

    if (map[int(pos_joueur_y)][(int)pos_joueur_x].treasure)
    {
        map[int(pos_joueur_y)][(int)pos_joueur_x].treasure = false;
        trésor_obtenu ++;
        if (trésor_obtenu == num_treasures)
        {
            gagne = true;
        }
    }
}