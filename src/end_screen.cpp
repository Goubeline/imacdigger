#include "end_screen.hpp"
#include <GLFW/glfw3.h>
#include "stb_easy_font.h"
#include "default_value.hpp"

void drawText2D(const char* text, float x, float y, float r, float g, float b, float scale = 2.5f)
{
    char buffer[99999];
    int num_quads;
    glColor3f(r, g, b);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(scale, scale, 1.0f);
    num_quads = stb_easy_font_print(0, 0, (char*)text, NULL, buffer, sizeof(buffer));
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 16, buffer);
    glDrawArrays(GL_QUADS, 0, num_quads * 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
}

// Dessine un bouton (rectangle + texte)
void drawButton(float x, float y, float w, float h, const char* label, float r, float g, float b)
{
    // Rectangle du bouton
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();

    // Texte centré dans le bouton
    int text_width = stb_easy_font_width((char*)label);
    float scale = 3.0f;
    float text_x = x + (w - text_width * scale) / 2.0f;
    float text_y = y + (h - 13 * scale) / 2.0f + scale + 6;
    drawText2D(label, text_x, text_y, 1, 1, 1, scale);
}

void displayEndScreen(EndType type)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Ajoute cette configuration pour dessiner en pixels
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    int width = WINDOW_WIDTH, height = WINDOW_HEIGHT;
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Affiche le message dans la fenêtre
    if (type == Victoire)
    {
        drawText2D("VICTOIRE !", 125, 130, 1, 1, 1, 10.0f); // x, y, r, g, b, scale
        drawText2D("Bravo, preux chevalier ! Vous avez obtenu le Graal !", 110, 250, 1, 1, 1, 2.0f);
    }
    else
    {
        drawText2D("DEFAITE !", 150, 130, 1, 1, 1, 10.0f);
        drawText2D("Oh non ! Vous n'avez pas survecu a votre quete !", 118, 250, 1, 1, 1, 2.0f);
    }

    // Bouton Rejouer (vert)
    drawButton(250, 500, 300, 60, "REJOUER", 0.2f, 0.7f, 0.2f);
    // Bouton Quitter (rouge)
    drawButton(250, 600, 300, 60, "QUITTER", 0.7f, 0.2f, 0.2f);

    // Restaure les matrices
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}