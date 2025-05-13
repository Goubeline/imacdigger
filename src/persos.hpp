#pragma once
#include <array>

enum Direction /*enum temporaire, en attendant la mise en commun*/
{
    Haut,
    Bas,
    Gauche,
    Droite,
    Immobile
};

struct Joueur
{
    std::array<double,2> position_xy{}; // position en float du joueur
    std::array<int,2> position_grill{}; // numéro de la ligne et numéro de la colonne

    Direction direction{}; // direction vers le prochain mouvement (peiut être utile pour l'apparence du joueur)

    bool verif_board() const; // verifie que x et y ne dépasse pas le bord du plateau : false -> ils dépassent

    void xy_to_grill(); // calcul position_grill à partir de position_xy
};

struct Ennemi
{
    std::array<double,2> position_xy{}; // position en float de l'ennemi
    std::array<int,2> position_grill{}; // numéro de la ligne et numéro de la colonne

    void xy_to_grill(); // calcul position_grill à partir de position_xy
};