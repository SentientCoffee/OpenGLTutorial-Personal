#ifndef APPLICATION_H
#define APPLICATION_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Macros.h"

namespace Coffee {

	class Application {
	public:

		Application(
			GLuint  width,
			GLuint  height,
	  const GLchar* title,
			GLuint  contextVersionMajor = 4u,
			GLuint  contextVersionMinor = 6u
		);

		static bool isInstantiated();
		
		void run();

	private:

		static GLuint  _width;
		static GLuint  _height;
		static GLchar* _title;
		static GLuint  _contextVersionMajor;
		static GLuint  _contextVersionMinor;


		static bool _instantiated;

	};
	
}

#endif
