#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Macros.h"

#pragma region PROGRAM SETTINGS

constexpr GLuint  SCR_WIDTH  = 800;
constexpr GLuint  SCR_HEIGHT = 600;
constexpr GLchar* SCR_TITLE  = const_cast<GLchar*>("OpenGL for CG");

#pragma endregion 

int main() {
	
#pragma region GLFW/GLAD SETUP

	// Initialize GLFW
	DEBUG_LOG_N("----------INITIALIZING GLFW----------");
	DEBUG_LOG_N("Initializing...");
	if(!glfwInit()) {
		DEBUG_LOG_ERROR("Failed to initialize GLFW! Exiting...\n");
		SYS_EXIT(1);
	}

	// Set the window hints (using OpenGL v4.6)
	DEBUG_LOG_N("Setting window hints...");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create the window
	DEBUG_LOG_N("Creating window...");
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, SCR_TITLE, NULL, NULL);

	if(window == NULL) {
		DEBUG_LOG_ERROR("Failed to initialize GLFW window! Exiting...\n");
		glfwTerminate();
		SYS_EXIT(2);
	}

	// Make the current context the window and set a buffer size callback that lets us resize the window
	DEBUG_LOG_N("Setting window settings...");
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); });

	// Initialize GLAD
	DEBUG_LOG_N("\n----------INITIALIZING GLAD----------");
	if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		DEBUG_LOG_ERROR("Failed to initialize GLAD! Exiting...\n");
		glfwTerminate();
		SYS_EXIT(3);
	}
	DEBUG_LOG_N("GLFW OpenGL function pointers loaded.");
	
#pragma endregion

#pragma region RENDER LOOP

	DEBUG_LOG_N("\n----------STARTING RENDER LOOP----------");
	DEBUG_LOG_N("OpenGL version %s", reinterpret_cast<GLchar const*>(glGetString(GL_VERSION)));
	DEBUG_LOG_N("Using %s %s", reinterpret_cast<GLchar const*>(glGetString(GL_VENDOR)), reinterpret_cast<GLchar const*>(glGetString(GL_RENDERER)));
	
	while(!glfwWindowShouldClose(window)) {
		// Poll GLFW events (clicks, key presses, etc.)
		glfwPollEvents();
		
		// TODO: PROCESS INPUTS

		// Clear the screen every frame
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// TODO: RENDER HERE

		// Swap the buffers after rendering
		glfwSwapBuffers(window);
	}
	
#pragma endregion

#pragma region PROGRAM TERMINATION

	DEBUG_LOG_N("\n----------TERMINATING PROGRAM----------");
	glfwTerminate();
	DEBUG_LOG_N("GLFW terminated.\n");

	system("pause");
	return 0;

#pragma endregion 
}