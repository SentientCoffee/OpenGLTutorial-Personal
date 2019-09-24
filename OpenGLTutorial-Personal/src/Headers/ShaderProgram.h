#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

namespace Coffee {

	enum class ShaderType : GLuint {
		VERTEX = 0,
		FRAGMENT,
		GEOMETRY
	};
	
	class ShaderProgram {
	public:

		ShaderProgram();
		ShaderProgram(
			const std::string& vertPath,
			const std::string& fragPath,
			const std::string& geoPath = ""
		);

		void createShader();
		void use() const;
		void changeShaderDirectory(const std::string& directory) const;
		
		void setUniform(const std::string& name, bool value)     const;
		void setUniform(const std::string& name, GLint value)    const;
		void setUniform(const std::string& name, GLfloat value)  const;
		
		void setUniform(const std::string& name, glm::mat4 value)  const;

		GLuint getId() const;
		
	private:

		// Function to load files as strings (used for shader source code)
		static bool loadFileAsString(const std::string& file, std::string& output);
		// Function to compile shaders in the constructor
		static void compileShader(const std::string& shaderPath, const ShaderType& type, GLuint& shader);
		// Function to link shaders together after compilation
		void createProgram(GLuint vertex, GLuint fragment, GLuint geometry);

		GLuint _programId;

		std::string _vertexPath;
		std::string _fragmentPath;
		std::string _geometryPath;

		static std::string _shaderDirectory;
	};
	
}
#endif 