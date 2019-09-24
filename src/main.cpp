#include "Application.h"

using Application = Coffee::Application;

#pragma region PROGRAM SETTINGS

constexpr GLuint  SCR_WIDTH  = 800;
constexpr GLuint  SCR_HEIGHT = 600;
constexpr GLchar* SCR_TITLE  = const_cast<GLchar*>("OpenGL Tutorial");

#pragma endregion

#pragma region GPU PERFORMANCE SWITCH

// This piece of code was given to us by Shawn Matthews
// Auto-magically changes OpenGL to use the high performance GPU to render rather than the iGPU
// (for dual GPU systems)
extern "C" {
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x01;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 0x01;
}

#pragma endregion 

int main() {

	if (!Application::isInstantiated()) {
		Application* application = new Application(SCR_WIDTH, SCR_HEIGHT, SCR_TITLE);
		application->run();
	}
	
	return 0;

#pragma endregion 
}