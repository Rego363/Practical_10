#ifndef GAME_H
#define GAME_H

#include <Debug.h>
#include <Cube.h>
#include <iostream>
#include <C:\glew-1.13.0\include\GL/glew.h>
#include <C:\glew-1.13.0\include\GL/wglew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <fstream>
#include <sstream>
#include <Vector3.h>
#include <Matrix3.h>
#include <C:\glm\glm/glm.hpp>
#include <C:\glm\glm/gtc/matrix_transform.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace std;
using namespace sf;
using namespace glm;

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void render();
	void unload();

	std::ifstream vertexInput;
	std::stringstream vss;
	std::string vsLine;
	std::ifstream fragInput;
	std::stringstream ss;
	std::string line;
	Clock clock;
	Time elapsed;

	float rotationAngle = 0.01f;
};

#endif