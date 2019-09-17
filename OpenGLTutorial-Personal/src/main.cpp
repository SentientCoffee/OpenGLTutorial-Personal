#include "Application.h"

using Application = Coffee::Application;

#pragma region PROGRAM SETTINGS

constexpr GLuint  SCR_WIDTH  = 800;
constexpr GLuint  SCR_HEIGHT = 600;
constexpr GLchar* SCR_TITLE  = const_cast<GLchar*>("OpenGL for CG");

#pragma endregion 

int main() {

	Application* application = new Application(SCR_WIDTH, SCR_HEIGHT, SCR_TITLE);
	application->run();
	
	return 0;

#pragma endregion 
}