#pragma once

enum EndType { 
    Victoire, 
    Defaite 
};

void drawText2D(const char* text, float x, float y, float r, float g, float b, float scale);

void displayEndScreen(EndType type);