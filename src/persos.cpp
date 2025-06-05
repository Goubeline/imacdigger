#include <iostream>
#include <cmath>
#include "persos.hpp"
#include "default_value.hpp"

bool Joueur::verif_board() const{
    if (position_xy[0]<0 || position_xy[0]>MAP_WIDTH){
        return false;
    }
    if (position_xy[1]<0 || position_xy[1]>MAP_HEIGHT){
        return false;
    }
    return true;
}

void Joueur::xy_to_grill(){
    position_grill= {static_cast<int>(std::floor(position_xy[0])),static_cast<int>(std::floor(position_xy[1])) };
}
void Ennemi::xy_to_grill(){
    position_grill= {static_cast<int>(std::floor(position_xy[0])),static_cast<int>(std::floor(position_xy[1])) };
}

