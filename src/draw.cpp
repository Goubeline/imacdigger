#include "draw.hpp"
#include "texture.hpp"
#include "bfs.hpp"
#include "default_value.hpp"
#include <iostream>
#include <cmath>

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
STP3D::Vector3D axe_Z {0.0,0.0,0.0};
float vitesse_joueur = 2;

const int original_height = 800;
const int original_width = 800;

float pos_joueur_x;
float pos_joueur_y;

/* OpenGL Engine */
GLBI_Engine myEngine;

inline StandardMesh* Basic_Bloc(float x,float y) {
		StandardMesh* bloc = new StandardMesh(4,GL_TRIANGLE_STRIP);
		float coord[12] = {x/2.f,y/2.f,
		                   x/2.f,-y/2.f,
		                   -x/2.f,-y/2.f,
		                   -x/2.f,y/2.f};
		float uvs_bloc[8] = {0.0,0.0,
							0.0,1.0,
							1.0,0.0,
							1.0,1.0};
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
						myEngine.setFlatColor(0.8, 0.8, 0);						
					}
					else if (map[y][x].trap)
					{
						myEngine.setFlatColor(0, 0, 0);				
					}
					else
					{				
						myEngine.setFlatColor(0, 0.8, 0);
					}
				}
				else
					myEngine.setFlatColor(0.6, 0, 0);
				bloc->draw();
				// if (map[y][x].type == Vide)
				// 	appli_Texture_sol(myEngine,bloc);
				// else{
				// }
				// 	appli_Texture_pierre(myEngine,bloc,texture);
				// 	texture = define_texture(map,x,y);
			}
			myEngine.mvMatrixStack.addTranslation({1, 0, 0});
		}
		myEngine.mvMatrixStack.addTranslation({- std::floor(GL_VIEW_SIZE) - 3, -1, 0});	
	}
	myEngine.mvMatrixStack.popMatrix();
}

void renderScene(std::vector<std::vector<Bloc>>& map){
	myEngine.mvMatrixStack.loadIdentity();
	draw_map(map);
	myEngine.updateMvMatrix();
	axis.drawSet();
	// myEngine.setFlatColor(0.6, 0, 0);
	// bloc.drawShape();
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
	std::cout << player.left << std::endl;
	switch (key)
	{
	case GLFW_KEY_A:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			player.left = true;

		}
		break;
	case GLFW_KEY_D:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			player.right = true;
		}
		break;
	case GLFW_KEY_W:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			player.up = true;
		}
		break;
	case GLFW_KEY_S:
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			player.down = true;
		}
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
	pos_joueur_x += vitesse_joueur * elapsedTime * x;
	if (x < 0)
	{
		if (pos_joueur_x < 0.5)
		{
			pos_joueur_x = 0.5;
		}
		else if(map[(int)pos_joueur_y][(int)(pos_joueur_x - 0.5)].type == Mur)
		{
			pos_joueur_x = (int)pos_joueur_x + 0.5;
		}
		return;
	}

	if (x > 0)
	{
		if (pos_joueur_x > map.size() - 0.5)
		{
			pos_joueur_x = map.size() - 0.5;
		}
		else if(map[(int)pos_joueur_y][(int)(pos_joueur_x + 0.5)].type == Mur)
		{
			pos_joueur_x = (int)pos_joueur_x + 0.5;
		}
		return;
	}

	pos_joueur_y += vitesse_joueur * elapsedTime * y;
	if (y < 0)
	{
		if (pos_joueur_y < 0.5)
		{
			pos_joueur_y = 0.5;
		}
		else if(map[(int)(pos_joueur_y + 0.5)][(int)pos_joueur_x].type == Mur)
		{
			pos_joueur_x = (int)pos_joueur_x + 0.5;
		}
		return;
	}

	if (y > 0)
	{
		if (pos_joueur_y > map.size() - 0.5)
		{
			pos_joueur_y = map.size() - 0.5;
		}
		else if(map[(int)(pos_joueur_y - 0.5)][(int)pos_joueur_x].type == Mur)
		{
			pos_joueur_x = (int)pos_joueur_x - 0.5;
		}
		return;
	}
	// std::cout << pos_joueur_x << std::endl;
	player.left = false;
	player.right = false;
	player.up = false;
	player.down = false;
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
		renderScene(map);

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
    glfwTerminate();
    return 0;
}