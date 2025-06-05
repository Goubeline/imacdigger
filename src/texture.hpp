#pragma once
#include <iostream>
#include <array>
#include "glbasimac/glbi_texture.hpp"
#include "bloc.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "glbasimac/glbi_engine.hpp"
#include "draw.hpp"

using namespace glbasimac;

extern unsigned char *H,* P,* P_H,* P_G,* P_GH,* P_D,* P_DH,* P_DG,* P_DGH,* P_B,* P_BH,* P_BG,* P_BGH,* P_BD,* P_BDH,* P_BDG,* P_BDGH;
extern GLBI_Texture myTextureH, myTexture0, myTexture1, myTexture2, myTexture3, myTexture4, myTexture5, myTexture6, myTexture7, myTexture8, myTexture9, myTexture10, myTexture11, myTexture12, myTexture13, myTexture14, myTexture15;
extern unsigned char* C_b1,* C_b2,* C_d1,* C_d2,* C_g1,* C_g2,* C_h1,* C_h2;
extern GLBI_Texture TP_b1,TP_b2,TP_d1,TP_d2,TP_g1,TP_g2,TP_h1,TP_h2;

void Textures();
std::array<bool,4> existences(std::vector<std::vector<Bloc>>& map,int x,int y);
int define_texture (std::vector<std::vector<Bloc>>& map,int x, int y);
void appli_Texture_sol (GLBI_Engine myEngine,StandardMesh* bloc);
void appli_Texture_pierre (GLBI_Engine myEngine,StandardMesh* bloc, int texture);
void texture_perso(GLBI_Engine myEngine,PlayerMove player,StandardMesh* bloc);