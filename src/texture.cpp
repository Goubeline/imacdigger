#include <iostream>
#include <array>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "tools/stb_image.h"
#include "glbasimac/glbi_texture.hpp"
#include "texture.hpp"

#include "glbasimac/glbi_set_of_points.hpp"

#include "tools/basic_mesh.hpp"


using namespace glbasimac;

unsigned char *H{},* P{},* P_H{},* P_G{},* P_GH{},* P_D{},* P_DH{},* P_DG{},* P_DGH{},* P_B{},* P_BH{},* P_BG{},* P_BGH{},* P_BD{},* P_BDH{},* P_BDG{},* P_BDGH{};
GLBI_Texture myTextureH{}, myTexture0{}, myTexture1{}, myTexture2{}, myTexture3{}, myTexture4{}, myTexture5{}, myTexture6{}, myTexture7{}, myTexture8{}, myTexture9{}, myTexture10{}, myTexture11{}, myTexture12{}, myTexture13{}, myTexture14{}, myTexture15{};


void Textures(){
    stbi_set_flip_vertically_on_load(true);

    myTextureH.createTexture();
    myTextureH.attachTexture();
	myTextureH.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	int widthH, heightH, nrChannelsH;
    H = stbi_load("../../assets/textures/H.png", &widthH, &heightH, &nrChannelsH, 0);
    std::cout << "Image " << (H != nullptr ? "" : " not") << " loaded." << std::endl;

    myTextureH.loadImage(widthH, heightH, nrChannelsH, H);
    myTextureH.detachTexture();

    myTexture0.createTexture();
    myTexture0.attachTexture();
	myTexture0.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	int width0, height0, nrChannels0;
    P = stbi_load("../../assets/textures/P_.png", &width0, &height0, &nrChannels0, 0);
    myTexture0.loadImage(width0, height0, nrChannels0, P);
    myTexture0.detachTexture();

    myTexture1.createTexture();
    myTexture1.attachTexture();
	myTexture1.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    int width1, height1, nrChannels1;
    unsigned char* P_H = stbi_load("../../assets/textures/P_h.png", &width1, &height1, &nrChannels1, 0);
    myTexture1.loadImage(width1, height1, nrChannels1, P_H);
    myTexture1.detachTexture();

    myTexture2.createTexture();
    myTexture2.attachTexture();
	myTexture2.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    int width2, height2, nrChannels2;
    unsigned char* P_G = stbi_load("../../assets/textures/P_g.png", &width2, &height2, &nrChannels2, 0);
    myTexture2.loadImage(width2, height2, nrChannels2, P_G);
    myTexture2.detachTexture();

    myTexture3.createTexture();
    myTexture3.attachTexture();
	myTexture3.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    int width3, height3, nrChannels3;
    unsigned char* P_GH = stbi_load("../../assets/textures/P_gh.png", &width3, &height3, &nrChannels3, 0);
    myTexture3.loadImage(width3, height3, nrChannels3, P_GH);
    myTexture3.detachTexture();

    myTexture4.createTexture();
    myTexture4.attachTexture();
	myTexture4.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    int width4, height4, nrChannels4;
    unsigned char* P_D = stbi_load("../../assets/textures/P_d.png", &width4, &height4, &nrChannels4, 0);
    myTexture4.loadImage(width4, height4, nrChannels4, P_D);
    myTexture4.detachTexture();

    myTexture5.createTexture();
    myTexture5.attachTexture();
	myTexture5.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    int width5, height5, nrChannels5;
    unsigned char* P_DH = stbi_load("../../assets/textures/P_dh.png", &width5, &height5, &nrChannels5, 0);
    myTexture5.loadImage(width5, height5, nrChannels5, P_DH);
    myTexture5.detachTexture();

    myTexture6.createTexture();
    myTexture6.attachTexture();
	myTexture6.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    int width6, height6, nrChannels6;
    unsigned char* P_DG = stbi_load("../../assets/textures/P_dg.png", &width6, &height6, &nrChannels6, 0);
    myTexture6.loadImage(width6, height6, nrChannels6, P_DG);
    myTexture6.detachTexture();

    myTexture7.createTexture();
    myTexture7.attachTexture();
	myTexture7.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    int width7, height7, nrChannels7;
    unsigned char* P_DGH = stbi_load("../../assets/textures/P_dgh.png", &width7, &height7, &nrChannels7, 0);
    myTexture7.loadImage(width7, height7, nrChannels7, P_DGH);
    myTexture7.detachTexture();

    myTexture8.createTexture();
    myTexture8.attachTexture();
	myTexture8.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    int width8, height8, nrChannels8;
    unsigned char* P_B = stbi_load("../../assets/textures/P_b.png", &width8, &height8, &nrChannels8, 0);
    myTexture8.loadImage(width8, height8, nrChannels8, P_B);
    myTexture8.detachTexture();

    myTexture9.createTexture();
    myTexture9.attachTexture();
	myTexture9.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    int width9, height9, nrChannels9;
    unsigned char* P_BH = stbi_load("../../assets/textures/P_bh.png", &width9, &height9, &nrChannels9, 0);
    myTexture9.loadImage(width9, height9, nrChannels9, P_BH);
    myTexture9.detachTexture();

    myTexture10.createTexture();
    myTexture10.attachTexture();
	myTexture10.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    int width10, height10, nrChannels10;
    unsigned char* P_BG = stbi_load("../../assets/textures/P_bg.png", &width10, &height10, &nrChannels10, 0);
    myTexture10.loadImage(width10, height10, nrChannels10, P_BG);
    myTexture10.detachTexture();

    myTexture11.createTexture();
    myTexture11.attachTexture();
	myTexture11.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    int width11, height11, nrChannels11;
    unsigned char* P_BGH = stbi_load("../../assets/textures/P_bgh.png", &width11, &height11, &nrChannels11, 0);
    myTexture11.loadImage(width11, height11, nrChannels11, P_BGH);
    myTexture11.detachTexture();

    myTexture12.createTexture();
    myTexture12.attachTexture();
	myTexture12.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    int width12, height12, nrChannels12;
    unsigned char* P_BD = stbi_load("../../assets/textures/P_bd.png", &width12, &height12, &nrChannels12, 0);
    myTexture12.loadImage(width12, height12, nrChannels12, P_BD);
    myTexture12.detachTexture();

    myTexture13.createTexture();
    myTexture13.attachTexture();
	myTexture13.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    int width13, height13, nrChannels13;
    unsigned char* P_BDH = stbi_load("../../assets/textures/P_bdh.png", &width13, &height13, &nrChannels13, 0);
    myTexture13.loadImage(width13, height13, nrChannels13, P_BDH);
    myTexture13.detachTexture();

    myTexture14.createTexture();
    myTexture14.attachTexture();
	myTexture14.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    int width14, height14, nrChannels14;
    unsigned char* P_BDG = stbi_load("../../assets/textures/P_bdg.png", &width14, &height14, &nrChannels14, 0);
    myTexture14.loadImage(width14, height14, nrChannels14, P_BDG);
    myTexture14.detachTexture();

    myTexture15.createTexture();
    myTexture15.attachTexture();
	myTexture15.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    int width15, height15, nrChannels15;
    unsigned char* P_BDGH = stbi_load("../../assets/textures/P_bdgh.png", &width15, &height15, &nrChannels15, 0);
    myTexture15.loadImage(width15, height15, nrChannels15, P_BDGH);
    myTexture15.detachTexture();

    
    stbi_image_free(H);
	stbi_image_free(P);
	stbi_image_free(P_H);
    stbi_image_free(P_G);
    stbi_image_free(P_GH);
    stbi_image_free(P_D);
    stbi_image_free(P_DH);
    stbi_image_free(P_DG);
    stbi_image_free(P_DGH);
    stbi_image_free(P_B);
    stbi_image_free(P_BH);
    stbi_image_free(P_BG);
    stbi_image_free(P_BGH);
    stbi_image_free(P_BD);
    stbi_image_free(P_BDH);
    stbi_image_free(P_BDG);
    stbi_image_free(P_BDGH);
}

std::array<unsigned char*,16> liste {P,P_H,P_G,P_GH,P_D,P_DH,P_DG,P_DGH,P_B,P_BH,P_BG,P_BGH,P_BD,P_BDH,P_BDG,P_BDGH}; //liste des textures


std::array<bool,4> existences(std::vector<std::vector<Bloc>>& map,int x,int y){
    size_t max_x {map[0].size()};
    size_t max_y {map.size()};
    std::array<bool,4> existence {true, true,true, true};
    if (y==max_y){
        existence[0]=false;
    }
    if (x==max_x){
        existence[1]=false;
    }
    if (x==0){
        existence[2]=false;
    }
    if (y==0){
        existence[3]=false;
    }
    return existence;
}

int define_texture (std::vector<std::vector<Bloc>>& map,int x,int y){
    int value{0};
    std::array<bool,4> existence = existences(map, x, y);
    if (existence[0]){
        if (map[y+1][x].type == Vide){
            value+=8;
        }
    }
    if (existence[1]){
        if (map[y][x+1].type == Vide){
            value+=4;
        }
    }
    if (existence[2]){
        if (map[y][x-1].type == Vide){
            value+=2;
        }
    }
    if (existence[3]){
        if (map[y-1][x].type == Vide){
            value+=1;
        }
    }
    return value; //la value correspondra au numéro de la texture de la liste
}

void appli_Texture_sol (GLBI_Engine myEngine,StandardMesh* bloc){
    myEngine.activateTexturing(myTextureH.id_in_GL);
    myEngine.activateTexturing(true);
    myTextureH.attachTexture();
	bloc->draw();
	myTextureH.detachTexture();
}

void appli_Texture_pierre (GLBI_Engine myEngine, StandardMesh* bloc, int texture){
    myEngine.activateTexturing(liste[texture]);
    switch (texture)
    {
    case 0:
        myTexture0.attachTexture();
        bloc->draw();
        myTexture0.detachTexture();
        break;
    case 1:
        myTexture1.attachTexture();
        bloc->draw();
        myTexture1.detachTexture();
        break;
    case 2:
        myTexture2.attachTexture();
        bloc->draw();
        myTexture2.detachTexture();
        break;
    case 3:
        myTexture3.attachTexture();
        bloc->draw();
        myTexture3.detachTexture();
        break;
    case 4:
        myTexture4.attachTexture();
        bloc->draw();
        myTexture4.detachTexture();
        break;
    case 5:
        myTexture5.attachTexture();
        bloc->draw();
        myTexture5.detachTexture();
        break;
    case 6:
        myTexture6.attachTexture();
        bloc->draw();
        myTexture6.detachTexture();
        break;
    case 7:
        myTexture7.attachTexture();
        bloc->draw();
        myTexture7.detachTexture();
        break;
    case 8:
        myTexture8.attachTexture();
        bloc->draw();
        myTexture8.detachTexture();
        break;
    case 10:
        myTexture10.attachTexture();
        bloc->draw();
        myTexture10.detachTexture();
        break;
    case 11:
        myTexture11.attachTexture();
        bloc->draw();
        myTexture11.detachTexture();
        break;
    case 12:
        myTexture12.attachTexture();
        bloc->draw();
        myTexture12.detachTexture();
        break;
    case 13:
        myTexture13.attachTexture();
        bloc->draw();
        myTexture13.detachTexture();
        break;
    case 14:
        myTexture14.attachTexture();
        bloc->draw();
        myTexture14.detachTexture();
        break;
    case 15:
        myTexture15.attachTexture();
        bloc->draw();
        myTexture15.detachTexture();
        break;

    default:
        myEngine.activateTexturing(P);
        myTexture0.attachTexture();
        bloc->draw();
        myTexture0.detachTexture();
        break;
    }
}

