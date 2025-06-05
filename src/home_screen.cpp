#include "home_screen.hpp"
#include "end_screen.hpp"
#include <GLFW/glfw3.h>
#include "default_value.hpp"

void displayHomeScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Projection en pixels
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    int width = WINDOW_WIDTH, height = WINDOW_HEIGHT;
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Titre du jeu
    // Première ligne du titre
    drawText2D("LA QUETE", 145, 100, 1, 1, 0.2f, 10.0f);
    // Deuxième ligne du titre
    drawText2D("DU GRAAL", 150, 180, 1, 1, 0.2f, 10.0f);

    // Bouton Jouer (vert)
    drawButton(250, 500, 300, 60, "JOUER", 0.2f, 0.7f, 0.2f);
    // Bouton Quitter (rouge)
    drawButton(250, 600, 300, 60, "QUITTER", 0.7f, 0.2f, 0.2f);

    // Restaure les matrices
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}