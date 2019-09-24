#include "ShaderProgram.h"
#include "Macros.h"

#include <fstream>
#include <sstream>
#include <algorithm>

using string = std::string;
using ifstream = std::ifstream;
using sstream = std::stringstream;

using namespace Coffee;

string ShaderProgram::_shaderDirectory = "res/Shaders/";

ShaderProgram::ShaderProgram() : _programId(0), _vertexPath(""), _fragmentPath(""), _geometryPath("") {}

ShaderProgram::ShaderProgram(const std::string& vertPath, const std::string& fragPath, const std::string& geoPath) {
	_programId = 0;
	_vertexPath = vertPath;
	_fragmentPath = fragPath;
	_geometryPath = geoPath;

	createShader();
}

void ShaderProgram::createShader() {
	GLuint vertShader = 0, fragShader = 0, geoShader = 0;

	DEBUG_LOG_N("\n----------COMPILING SHADERS----------");

	DEBUG_LOG_N("------VERTEX SHADER------");
	compileShader(_vertexPath, ShaderType::VERTEX, vertShader);
	
	DEBUG_LOG_N("\n-----FRAGMENT SHADER-----");
	compileShader(_fragmentPath, ShaderType::FRAGMENT, fragShader);
	
	if (!_geometryPath.empty()) {
		DEBUG_LOG_N("\n-----GEOMETRY SHADER-----");
		compileShader(_geometryPath, ShaderType::GEOMETRY, geoShader);
	}

	DEBUG_LOG_N("\n----------LINKING SHADERS AND CREATING SHADER PROGRAM----------");
	createProgram(vertShader, fragShader, geoShader);
}

void ShaderProgram::use() const { glUseProgram(_programId); }

void ShaderProgram::changeShaderDirectory(const std::string& directory) const {
	string dir = directory;
	std::transform(dir.begin(), dir.end(), dir.begin(), ::tolower);

	if(dir == "default") {
		_shaderDirectory = "res/Shaders/";
	}
	else {
		_shaderDirectory = directory;
	}
}

GLuint ShaderProgram::getId() const { return _programId; }

bool ShaderProgram::loadFileAsString(const std::string& file, std::string& output) {
	ifstream inStream(file.data());
	sstream fileContent;

	if (!inStream.good()) {
		return false;
	}

	fileContent << inStream.rdbuf();
	output = fileContent.str();

	return true;
}

void ShaderProgram::compileShader(const std::string& shaderPath, const ShaderType& type, GLuint& shader) {
	string shaderString;
	const GLchar* shaderSource;

	DEBUG_LOG_N("Reading source code...");
	if (!loadFileAsString(_shaderDirectory + shaderPath, shaderString)) {
		DEBUG_LOG_ERROR("Failed to read shader from file!");
		shaderString = "";
	}

	shaderSource = shaderString.c_str();

	DEBUG_LOG_N("Compiling shader...");
	GLint success;
	GLuint shaderType = NULL;

	switch (type) {
	case ShaderType::VERTEX:
		shaderType = GL_VERTEX_SHADER;
		break;

	case ShaderType::FRAGMENT:
		shaderType = GL_FRAGMENT_SHADER;
		break;

	case ShaderType::GEOMETRY:
		shaderType = GL_GEOMETRY_SHADER;
		break;
	}

	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);

		DEBUG_LOG_ERROR("Failed to compile shader!");
		DEBUG_LOG_ERROR(infoLog);
	}
}

void ShaderProgram::createProgram(GLuint vertex, GLuint fragment, GLuint geometry) {
	_programId = glCreateProgram();

	DEBUG_LOG_N("Linking shaders...");
	if (vertex) {
		glAttachShader(_programId, vertex);
	}
	else {
		DEBUG_LOG_ERROR("No vertex shader linked!");
	}

	if (fragment) {
		glAttachShader(_programId, fragment);
	}
	else {
		DEBUG_LOG_ERROR("No fragment shader linked!");
	}

	if (geometry) {
		glAttachShader(_programId, geometry);
	}
	else {
		DEBUG_LOG_ERROR("No geometry shader linked!");
	}

	DEBUG_LOG_N("Creating program...");
	GLint success;

	glLinkProgram(_programId);

	glGetProgramiv(_programId, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetProgramInfoLog(_programId, 512, NULL, infoLog);
		DEBUG_LOG_ERROR("Failed to create the shader program!");
		DEBUG_LOG_ERROR(infoLog);
	}

	DEBUG_LOG_N("Deleting shaders...");
	if (vertex) {
		glDeleteShader(vertex);
	}
	if (fragment) {
		glDeleteShader(fragment);
	}
	if (geometry) {
		glDeleteShader(geometry);
	}
}

void ShaderProgram::setUniform(const std::string& name, const bool value) const {
	glUniform1i(
		glGetUniformLocation(_programId, name.c_str()), static_cast<GLint>(value)
	);
}
void ShaderProgram::setUniform(const std::string& name, const GLint value) const {
	glUniform1i(
		glGetUniformLocation(_programId, name.c_str()), value
	);
}
void ShaderProgram::setUniform(const std::string& name, const GLfloat value) const {
	glUniform1f(
		glGetUniformLocation(_programId, name.c_str()), value
	);
}

void ShaderProgram::setUniform(const std::string& name, glm::mat4 value) const {
	glUniformMatrix4fv(
		glGetUniformLocation(_programId, name.c_str()), 1, GL_FALSE, value_ptr(value)
	);
}