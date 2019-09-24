#ifndef VERTEX_INFO_H
#define VERTEX_INFO_H

#include "ShaderProgram.h"
#include "stb_image.h"

#include <glad/glad.h>
#include <vector>

namespace Coffee {
	class VertexInfo {
	public:
		static void setupVertices() {
			_vertices = {
				// positions				// texture coords
				// x, y, z					// s, t
				-0.5f, -0.5f, -0.5f,		0.0f, 0.0f,
				 0.5f, -0.5f, -0.5f,		1.0f, 0.0f,
				 0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
				 0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
				-0.5f,  0.5f, -0.5f,		0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,		0.0f, 0.0f,

				-0.5f, -0.5f,  0.5f,		0.0f, 0.0f,
				 0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,		1.0f, 1.0f,
				 0.5f,  0.5f,  0.5f,		1.0f, 1.0f,
				-0.5f,  0.5f,  0.5f,		0.0f, 1.0f,
				-0.5f, -0.5f,  0.5f,		0.0f, 0.0f,

				-0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
				-0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
				-0.5f, -0.5f,  0.5f,		0.0f, 0.0f,
				-0.5f,  0.5f,  0.5f,		1.0f, 0.0f,

				 0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
				 0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
				 0.5f, -0.5f,  0.5f,		0.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,		1.0f, 0.0f,

				-0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,		1.0f, 1.0f,
				 0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
				 0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
				-0.5f, -0.5f,  0.5f,		0.0f, 0.0f,
				-0.5f, -0.5f, -0.5f,		0.0f, 1.0f,

				-0.5f,  0.5f, -0.5f,		0.0f, 1.0f,
				 0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
				 0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
				-0.5f,  0.5f,  0.5f,		0.0f, 0.0f,
				-0.5f,  0.5f, -0.5f,		0.0f, 1.0f
			};
		}
		
		static void setupIndices() {
			_indices = {
				0, 1, 3,   // first triangle
				1, 2, 3    // second triangle
			};
		}

		static void setupPositions() {
			_positions = {
				glm::vec3( 0.0f,	 0.0f,	  0.0f),
				glm::vec3( 2.0f,	 5.0f,	-15.0f),
				glm::vec3(-1.5f,	-2.2f,	 -2.5f),
				glm::vec3(-3.8f,	-2.0f,	-12.3f),
				glm::vec3( 2.4f,	-0.4f,	 -3.5f),
				glm::vec3(-1.7f,	 3.0f,	 -7.5f),
				glm::vec3( 1.3f,	-2.0f,	 -2.5f),
				glm::vec3( 1.5f,	 2.0f,	 -2.5f),
				glm::vec3( 1.5f,	 0.2f,	 -1.5f),
				glm::vec3(-1.3f,	 1.0f,	 -1.5f)
			};
		}
		
		static void setupVertexObjects() {
			// Create a vertex attribute (VAO), vertex buffer (VBO), and element buffer (EBO) objects
			glGenVertexArrays(1, &_vao);																				// Generate a unique ID for the VAO
			glGenBuffers(1, &_vbo);																						// Generate a unique ID for the VBO
			glGenBuffers(1, &_ebo);																						// Generate a unique ID for the EBO
																														
			glBindVertexArray(_vao);																					// Bind the VAO to store the VBO settings


			
			glBindBuffer(GL_ARRAY_BUFFER, _vbo);																		 // Bind the VBO as the target buffer
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _vertices.size(), _vertices.data(), GL_STATIC_DRAW);		 // Copy the vertex data onto the buffer
																														
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);																 // Bind the EBO as the new target buffer
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * _indices.size(), _indices.data(), GL_STATIC_DRAW);	 // Copy index data onto the buffer


			
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);								 // Link the vertex position attributes to the shader program
			glEnableVertexAttribArray(0);																				 // Enable the vertex position attribute array (disabled by default)
			
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));			 // Link the texture coordinate attributes to the shader program
			glEnableVertexAttribArray(1);																				 // Enable the texture coordinate attribute array


			
			// NOTE: this is not strictly necessary, but better to be safe and avoid accidental changes to VAOs/VBOs/EBOs
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	// Unbind EBO to avoid further changes
			//glBindBuffer(GL_ARRAY_BUFFER, 0);			// Unbind VBO to avoid further changes
			//glBindVertexArray(0);						// Unbind VAO to avoid further changes
		}

		static void loadAndCreateTextures() {
			GLint width, height, numChannels;
			// ReSharper disable once CppJoinDeclarationAndAssignment
			GLubyte* imageData;

			stbi_set_flip_vertically_on_load(true);

			glGenTextures(1, &_texture1);
			glBindTexture(GL_TEXTURE_2D, _texture1);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// ReSharper disable once CppJoinDeclarationAndAssignment
			imageData = stbi_load("res/Textures/woodenContainer.jpg", &width, &height, &numChannels, 0);

			if(!imageData) {
				DEBUG_LOG_ERROR("Failed to load texture! (woodenContainer)");
				stbi_image_free(imageData);
			}

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
			glGenerateMipmap(GL_TEXTURE_2D);



			glGenTextures(1, &_texture2);
			glBindTexture(GL_TEXTURE_2D, _texture2);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// ReSharper disable once StringLiteralTypo
			imageData = stbi_load("res/Textures/awesomeface.png", &width, &height, &numChannels, 0);

			if(!imageData) {
				DEBUG_LOG_ERROR("Failed to load texture! (awesomeface)");
				stbi_image_free(imageData);
			}
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
			glGenerateMipmap(GL_TEXTURE_2D);
			
			stbi_image_free(imageData);
		}

		static void setUniforms(const ShaderProgram& shaderProgram) {
			shaderProgram.use();
			
			shaderProgram.setUniform("texture1", 0);
			shaderProgram.setUniform("texture2", 1);
		}

		static void convertViews(const ShaderProgram& shaderProgram, const GLfloat windowWidth, const GLfloat windowHeight) {
			glm::mat4 view(1.0f);
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

			glm::mat4 projection = glm::perspective(glm::radians(45.0f), windowWidth / windowHeight, 0.1f, 100.0f);
			
			shaderProgram.use();
			shaderProgram.setUniform("view", view);
			shaderProgram.setUniform("projection", projection);
			
		}
		
		static void draw(const ShaderProgram& shaderProgram, GLfloat dt) {
			shaderProgram.use();
			
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _texture1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, _texture2);

			glBindVertexArray(_vao);                                // Bind the appropriate vertex array

			for (GLuint i = 0; i < _positions.size(); ++i) {
				glm::mat4 model(1.0f);
				model = glm::translate(model, _positions[i]);
				
				GLfloat angle = 20.0f * i;
				model = glm::rotate(model, dt * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				
				shaderProgram.setUniform("model", model);


				glDrawArrays(GL_TRIANGLES, 0, 36);
				//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	// Draw a rectangle now bitch
			}

		}

	private:
		static std::vector<GLfloat> _vertices;
		static std::vector<GLuint> _indices;
		static std::vector<glm::vec3> _positions;
		static GLuint _vao, _vbo, _ebo;
		static GLuint _texture1, _texture2;
	};

	std::vector<GLfloat> VertexInfo::_vertices{};
	std::vector<GLuint> VertexInfo::_indices{};
	std::vector<glm::vec3> VertexInfo::_positions{};
	
	GLuint VertexInfo::_vao = 0,
		   VertexInfo::_vbo = 0,
		   VertexInfo::_ebo = 0;
	
	GLuint VertexInfo::_texture1 = 0,
		   VertexInfo::_texture2 = 0;
	
}
#endif