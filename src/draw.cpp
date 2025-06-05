#include "draw.hpp"
#include "texture.hpp"
#include "bfs.hpp"
#include "default_value.hpp"
#include "end_screen.hpp"
#include "handle_events.hpp"
#include "map_gen.hpp"
#include <iostream>
#include <cmath>
#include <utility>

PlayerMove player{};

using namespace glbasimac;

//std::vector<float> Coords_bloc{0.5,0.5,0.5,-0.5,-0.5,-0.5,-0.5,0.5};
//GLBI_Convex_2D_Shape bloc {};
StandardMesh* bloc{};
GLBI_Set_Of_Points axis;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 60.;
static float aspectRatio = 1.0f;
/* Espace virtuel */
static const float GL_VIEW_SIZE = 22.;
float vitesse_joueur = 3;

const int original_height = 800;
const int original_width = 800;

float pos_joueur_x;
float pos_joueur_y;
int prec_pos_x;
int prec_pos_y;

std::vector<std::pair<float, float>> ennemies{};
int nb_ennemis = 6;
/* OpenGL Engine */
GLBI_Engine myEngine;

inline StandardMesh* Basic_Bloc(float x,float y) {
		StandardMesh* bloc = new StandardMesh(4,GL_TRIANGLE_FAN);
		float coord[8] = {x/2.f,y/2.f,
		                   x/2.f,-y/2.f,
		                   -x/2.f,-y/2.f,
		                   -x/2.f,y/2.f};
		float uvs_bloc[8] = {0.0,1.0,
							0.0,0.0,
							1.0,1.0,
							1.0,0.0};
		bloc->addOneBuffer(0,2,coord,"coordinates",true);
		bloc->addOneBuffer(2,2,uvs_bloc,"uvs", true);
		return bloc;
}

void initScene(){
	std::vector<float> coords = {-GL_VIEW_SIZE/2, 0};
	float pointC[] = {0, -GL_VIEW_SIZE/2};
	float pointA[] = {GL_VIEW_SIZE/2, 0};
	float pointB[] = {0, GL_VIEW_SIZE/2};
	float whiteTable[] = {1, 1, 1};
	std::vector<float> white = {1, 1, 1};
	axis.initSet(coords, white);
	axis.addAPoint(pointA, whiteTable);
	axis.addAPoint(pointB, whiteTable);
	axis.addAPoint(pointC, whiteTable);
	axis.changeNature(GL_LINES);
	Textures();

    //bloc.initShape(Coords_bloc);
	bloc = Basic_Bloc(1.0,1.0);
	bloc->createVAO();
	myEngine.updateMvMatrix();
	bloc->changeType(GL_TRIANGLE_FAN);
}

void draw_map(std::vector<std::vector<Bloc>>& map)
{
	//myEngine.activateTexturing (false);
	float frac_x, whole_x, frac_y, whole_y;
	frac_x = std::modf(pos_joueur_x, &whole_x);
	frac_y = std::modf(pos_joueur_y, &whole_y);
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation({-GL_VIEW_SIZE / 2 - frac_x - 0.5, GL_VIEW_SIZE / 2 + frac_y + 0.5, 0});
	int texture;
    for (int y = whole_y - GL_VIEW_SIZE / 2 - 1; y <= whole_y + GL_VIEW_SIZE / 2 + 1; y++)
	{
		for (int x = whole_x - GL_VIEW_SIZE / 2 - 1; x <= whole_x + GL_VIEW_SIZE / 2 + 1; x++)
		{
			myEngine.updateMvMatrix();
			if (inbound(x, y))
			{
				if (map[y][x].type == Vide)
				{
					if (map[y][x].treasure)
					{	
						myEngine.activateTexturing (false);
						myEngine.mvMatrixStack.pushMatrix();
							myEngine.setFlatColor(0.8, 0.8, 0);
							bloc->draw();
						myEngine.mvMatrixStack.popMatrix();						
					}
					else if (map[y][x].trap)
					{	
						myEngine.activateTexturing (false);
						myEngine.mvMatrixStack.pushMatrix();
							myEngine.setFlatColor(1., 0., 0.);
							bloc->draw();
						myEngine.mvMatrixStack.popMatrix();			
					}
					else
					{	
						//myEngine.activateTexturing (true);			
						appli_Texture_sol(myEngine,bloc);
					}
				}
				else
					//myEngine.activateTexturing (true);
				 	{texture = define_texture(map,x,y);
			 		appli_Texture_pierre(myEngine,bloc,texture);}

			}
			myEngine.mvMatrixStack.addTranslation({1, 0, 0});
		}
		myEngine.mvMatrixStack.addTranslation({- std::floor(GL_VIEW_SIZE) - 3, -1, 0});	
	}
	myEngine.mvMatrixStack.popMatrix();
}

void draw_perso(){
		myEngine.activateTexturing (true);
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.updateMvMatrix();
	texture_perso(myEngine,player,bloc);
	myEngine.mvMatrixStack.popMatrix();
}

void renderScene(std::vector<std::vector<Bloc>>& map){
	myEngine.mvMatrixStack.loadIdentity();
	draw_map(map);
	myEngine.updateMvMatrix();
	// myEngine.setFlatColor(0.6, 0, 0);
	// bloc.drawShape();
	draw_perso();
}

/* Error handling function */
void onError(int error, const char* description) {
	std::cout << "GLFW Error ("<<error<<") : " << description << std::endl;
}

void onWindowResized(GLFWwindow* /*window*/, int width, int height)
{
	WINDOW_HEIGHT = height;
	WINDOW_WIDTH = width;
	aspectRatio = width / (float) height;
	glViewport(0, 0, width, height);
	if( aspectRatio > 1.0)
	{
		myEngine.set2DProjection(-GL_VIEW_SIZE * aspectRatio/ 2.,
			GL_VIEW_SIZE * aspectRatio / 2. ,
			-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
	}
	else
	{
		myEngine.set2DProjection(-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
			-GL_VIEW_SIZE / (2. * aspectRatio),
			GL_VIEW_SIZE / (2. * aspectRatio));
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	switch (key)
	{
	case GLFW_KEY_A:
		if (action == GLFW_PRESS)
			player.left = true;
		if (action == GLFW_RELEASE)
			player.left = false;		
		break;
	case GLFW_KEY_D:
		if (action == GLFW_PRESS)
			player.right = true;
		if (action == GLFW_RELEASE)
			player.right = false;
		break;
	case GLFW_KEY_W:
		if (action == GLFW_PRESS)
			player.up = true;
		if (action == GLFW_RELEASE)
			player.up = false;
		break;
	case GLFW_KEY_S:
		if (action == GLFW_PRESS)
			player.down = true;
		if (action == GLFW_RELEASE)
			player.down = false;
		break;
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, 1);
		}
		break;
	default:
		break;
	}
	
}

void deplacment(std::vector<std::vector<Bloc>>& map, double elapsedTime)
{
	int x = 0;
	int y = 0;
	if (player.left)
	{
		x = -1;
	}
	else if (player.right)
		x = 1;

	else if (player.up)
	{
		y = -1;
	}
	else if (player.down)
		y = 1;	
	//si x = 0, on ne se déplace pas latéralement, donc pos_joueur_x ne change pas
	//en cas de diagonale, abs(y) = 1 (sinon 0) donc on se déplace seulement de rac(0,5) = 0,7 (deplacement² = 0,7² + 0,7²  pythagore)
	pos_joueur_x += vitesse_joueur * elapsedTime * x * (std::abs(x) - std::abs(y) * 0.3);

	if (pos_joueur_x < 0.5)
	{
		pos_joueur_x = 0.5;
	}
	else if (pos_joueur_x > map.size() - 0.5)
	{
		pos_joueur_x = map.size() - 0.5;
	}
	else if(map[(int)pos_joueur_y][(int)(pos_joueur_x - 0.5)].type == Mur)
	{
		pos_joueur_x = (int)pos_joueur_x + 0.5;
		map[(int)pos_joueur_y][(int)(pos_joueur_x - 0.5)].type = Vide;
	}
	else if(map[(int)pos_joueur_y][(int)(pos_joueur_x + 0.5)].type == Mur)
	{
		pos_joueur_x = (int)pos_joueur_x + 0.5;
		map[(int)pos_joueur_y][(int)(pos_joueur_x + 0.5)].type = Vide;
	}

	pos_joueur_y += vitesse_joueur * elapsedTime * y * (std::abs(y) - std::abs(x) * 0.3);;

	if (pos_joueur_y < 0.99)
	{
		pos_joueur_y = 0.99;
	}
	else if (pos_joueur_y > map.size())
	{
		pos_joueur_y = map.size();
	}
	else if(map[(int)(pos_joueur_y - 1)][(int)pos_joueur_x].type == Mur)
	{
		pos_joueur_y = (int)pos_joueur_y + 0.99;
		map[(int)(pos_joueur_y - 1)][(int)pos_joueur_x].type = Vide;
	}
	else if(map[(int)(pos_joueur_y)][(int)pos_joueur_x].type == Mur)
	{
		pos_joueur_y = (int)pos_joueur_y - 0.001;
		map[(int)(pos_joueur_y)][(int)pos_joueur_x].type = Vide;
	}

	if (prec_pos_x != (int)pos_joueur_x || prec_pos_y != (int)pos_joueur_y)
	{
		bfs_flow_field(map, prec_pos_x, prec_pos_y);
		prec_pos_x = (int)pos_joueur_x;
		prec_pos_y = (int)pos_joueur_y;
	}
	
	// std::cout << pos_joueur_x << std::endl;
}

void mouvement_ennemi(std::vector<std::vector<Bloc>>& map, float elapsedTime)
{
	Bloc pos;
	for (auto ennemi : ennemies)
	{
		pos = map[ennemi.first][ennemi.second];
		if (pos.directionx != 0 && pos.directiony !=0)
		{
			ennemi.first += 0.5 * pos.directionx * vitesse_joueur * elapsedTime;
			ennemi.second += 0.5 * pos.directiony * vitesse_joueur * elapsedTime;
		}
		else
		{
			ennemi.first += pos.directionx * vitesse_joueur * elapsedTime;
			ennemi.second += pos.directiony* vitesse_joueur * elapsedTime;
		}
		if (ennemi.first < 0.5)
		{
			ennemi.first = 0.5;
		}
		else if (ennemi.first > map.size() - 0.5)
		{
			ennemi.first = map.size() - 0.5;
		}
		else if(map[(int)ennemi.second][(int)(ennemi.first - 0.5)].type == Mur)
		{
			ennemi.first = (int)ennemi.first + 0.5;
		}
		else if(map[(int)ennemi.second][(int)(ennemi.first + 0.5)].type == Mur)
		{
			ennemi.first = (int)ennemi.first + 0.5;
		}
	
	
		if (ennemi.second < 0.99)
		{
			ennemi.second = 0.99;
		}
		else if (ennemi.second > map.size())
		{
			ennemi.second = map.size();
		}
		else if(map[(int)(ennemi.second - 1)][(int)ennemi.first].type == Mur)
		{
			ennemi.second = (int)ennemi.second + 0.99;
		}
		else if(map[(int)(ennemi.second)][(int)ennemi.first].type == Mur)
		{
			ennemi.second = (int)ennemi.second - 0.001;
		}

	}
	
}


int draw(std::vector<std::vector<Bloc>>& map) {
    // Initialize the library
    if (!glfwInit()) {
        return -1;
    }

    /* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

	WINDOW_WIDTH = original_width;
	WINDOW_HEIGHT = original_height;

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "imac digger", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

	glfwSetInputMode(window, GLFW_MOD_SHIFT, GLFW_TRUE);
	glfwSetWindowSizeCallback(window, onWindowResized);
	glfwSetKeyCallback(window, key_callback);

    // Make the window's context current
    glfwMakeContextCurrent(window);

	// Intialize glad (loads the OpenGL functions)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}

	// Initialize Rendering Engine
	myEngine.initGL();

	pos_joueur_x = MAP_WIDTH/2 + 0.5;
	pos_joueur_y = MAP_HEIGHT/2 + 0.5;
	prec_pos_x = (int)pos_joueur_x;
	prec_pos_y = (int)pos_joueur_y;
	bfs_flow_field(map, prec_pos_x, prec_pos_y);

	for (size_t i = 0; i < nb_ennemis; i++)
	{
		ennemies.push_back(findValidStart(map));
	}
	

	onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	initScene();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Loop until the user closes the window */
	player.left = false;
	player.right = false;
	player.up = false;
	player.down = false;
	double elapsedTime;
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();
		glClear(GL_COLOR_BUFFER_BIT);
        
		// render here
		deplacment(map, elapsedTime);
		handle_events(map, pos_joueur_x, pos_joueur_y);

		// mouvement_ennemi(map);
		renderScene(map);
		if (gagne || perdu)
		{
			break;
		}
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		while(elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
			elapsedTime = glfwGetTime() - startTime;
		}
	}
	if (gagne)
	{
		while (!glfwWindowShouldClose(window)) 
		{
			double startTime = glfwGetTime();
			// Teste la victoire ou la défaite (on change le paramètre pour tester)
			displayEndScreen(Victoire); // ou Defaite

			glfwSwapBuffers(window);
			glfwPollEvents();
			while(elapsedTime < FRAMERATE_IN_SECONDS)
			{
				glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
				elapsedTime = glfwGetTime() - startTime;
			}
		}
	}
	if (perdu)
	{
		while (!glfwWindowShouldClose(window)) 
		{
			double startTime = glfwGetTime();
			// Teste la victoire ou la défaite (on change le paramètre pour tester)
			displayEndScreen(Defaite); // ou Defaite

			glfwSwapBuffers(window);
			glfwPollEvents();
			while(elapsedTime < FRAMERATE_IN_SECONDS)
			{
				glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
				elapsedTime = glfwGetTime() - startTime;
			}
		}
	}
	
    glfwTerminate();
    return 0;
}