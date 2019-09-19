#ifndef VERTEX_INFO_H
#define VERTEX_INFO_H

#include <vector>
#include <glad/glad.h>

#include "stb_image.h"

namespace Coffee {
	class VertexInfo {
	public:
		static void setupVertices() {
			_vertices = {
				// positions				// colours				// texture coords
				// x, y, z					// r, g, b				// s, t
				 0.5f,  0.5f, 0.0f,			1.0f, 0.0f, 0.0f,		1.0f, 1.0f,			// top right
				 0.5f, -0.5f, 0.0f,			0.0f, 1.0f, 0.0f,		1.0f, 0.0f,			// bottom right
				-0.5f, -0.5f, 0.0f,			0.0f, 0.0f, 1.0f,		0.0f, 0.0f,			// bottom left
				-0.5f,  0.5f, 0.0f,			1.0f, 1.0f, 0.0f,		0.0f, 1.0f			// top left 
			};
		}
		
		static void setupIndices() {
			_indices = {
				0, 1, 3,   // first triangle
				1, 2, 3    // second triangle
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


			
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);								 // Link the vertex position attributes to the shader program
			glEnableVertexAttribArray(0);																				 // Enable the vertex position attribute array (disabled by default)
																														 
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));			 // Link the vertex colour attributes to the shader program
			glEnableVertexAttribArray(1);																				 // Enable the vertex colour attribute array
																											 
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));			 // Link the vertex colour attributes to the shader program
			glEnableVertexAttribArray(2);																				 // Enable the vertex colour attribute array


			
			// NOTE: this is not strictly necessary, but better to be safe and avoid accidental changes to VAOs/VBOs/EBOs
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	// Unbind EBO to avoid further changes
			//glBindBuffer(GL_ARRAY_BUFFER, 0);			// Unbind VBO to avoid further changes
			//glBindVertexArray(0);						// Unbind VAO to avoid further changes
		}

		static void loadAndCreateTextures() {
			glGenTextures(1, &_texture);
			glBindTexture(GL_TEXTURE_2D, _texture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			GLint width, height, numChannels;
			GLubyte* imageData = stbi_load("res/Textures/woodenContainer.jpg", &width, &height, &numChannels, 0);

			if(!imageData) {
				DEBUG_LOG_ERROR("Failed to load texture!");
				stbi_image_free(imageData);
			}
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
			glGenerateMipmap(GL_TEXTURE_2D);
			
			stbi_image_free(imageData);
		}

		static void bindTexture() {
			glBindTexture(GL_TEXTURE_2D, _texture);
		}
		
		static void draw() {
			glBindVertexArray(_vao);                                // Bind the appropriate vertex array
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	// Draw a rectangle now bitch

		}

	private:
		static std::vector<GLfloat> _vertices;
		static std::vector<GLuint> _indices;
		static std::vector<GLfloat> _texCoords;
		static GLuint _vao, _vbo, _ebo, _texture;
	};

	std::vector<GLfloat> VertexInfo::_vertices{};
	std::vector<GLuint> VertexInfo::_indices{};
	std::vector<GLfloat> VertexInfo::_texCoords{};
	GLuint VertexInfo::_vao = 0,
		   VertexInfo::_vbo = 0,
		   VertexInfo::_ebo = 0,
		   VertexInfo::_texture = 0;
	
}
#endif