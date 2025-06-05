#include "handle_events.hpp"
#include "default_value.hpp"
#include <iostream>

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
    }
    if (map[int(pos_joueur_y)][(int)pos_joueur_x].graal == true)
    {
        if (num_treasures == trésor_obtenu)
        {
            gagne = true;
        }
        else
        {
            std::cout << "Il vous manque " << num_treasures - trésor_obtenu << " clef a trouver avant d'obtenir le graal" << std::endl;
        }
        
    }
    
}