#pragma once

enum EndType { 
    Victoire, 
    Defaite 
};

void drawText2D(const char* text, float x, float y, float r, float g, float b, float scale);
void drawButton(float x, float y, float w, float h, const char* label, float r, float g, float b);
void displayEndScreen(EndType type);