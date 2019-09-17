#include "Application.h"

using namespace Coffee;

GLuint  Application::_width               = 10u;
GLuint  Application::_height              = 10u;
GLchar* Application::_title               = reinterpret_cast<GLchar*>("Failed to start application!");
GLuint  Application::_contextVersionMajor = 4u;
GLuint  Application::_contextVersionMinor = 6u;

bool Application::_instantiated = false;

Application::Application(const GLuint width, const GLuint height, const GLchar* title, const GLuint contextVersionMajor, const GLuint contextVersionMinor) {
	_width = width;
	_height = height;
	_title = const_cast<GLchar*>(title);
	_contextVersionMajor = contextVersionMajor;
	_contextVersionMinor = contextVersionMinor;

	_instantiated = true;
}

bool Application::isInstantiated() { return _instantiated; }

void Application::run() {
#pragma region GLFW/GLAD SETUP
	
	// Initialize GLFW
	DEBUG_LOG_N("----------INITIALIZING GLFW----------");
	DEBUG_LOG_N("Initializing...");
	if (!glfwInit()) {
		DEBUG_LOG_ERROR("Failed to initialize GLFW! Exiting...\n");
		SYS_EXIT(1);
	}

	// Set the window hints (using OpenGL v4.6 by default)
	DEBUG_LOG_N("Setting window hints...");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _contextVersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _contextVersionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create the window
	DEBUG_LOG_N("Creating window...");
	GLFWwindow* window = glfwCreateWindow(_width, _height, _title, NULL, NULL);

	if (window == NULL) {
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
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
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

	while (!glfwWindowShouldClose(window)) {

		// TODO: PROCESS INPUTS

		// Clear the screen every frame
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// TODO: RENDER HERE

		// Swap the buffers after rendering
		glfwSwapBuffers(window);
		// Poll GLFW events (clicks, key presses, etc.)
		glfwPollEvents();
	}

#pragma endregion


	
#pragma region PROGRAM TERMINATION

	DEBUG_LOG_N("\n----------TERMINATING PROGRAM----------");
	glfwTerminate();
	DEBUG_LOG_N("GLFW terminated.\n");

#if _DEBUG
	system("pause");
#endif
	
#pragma endregion 
}