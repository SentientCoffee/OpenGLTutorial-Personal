#ifndef VERTEX_INFO_H
#define VERTEX_INFO_H

#include <vector>
#include <glad/glad.h>

namespace Coffee {
	class VertexInfo {
	public:
		static void setupVertices() {
			_vertices = {
				// positions				// colours
				// x, y, z					// r, g, b
				-0.5f, -0.5f, 0.0f,			1.0f, 0.0f, 0.0f,			// bottom left
				0.5f, -0.5f, 0.0f,			0.0f, 1.0f, 0.0f,			// bottom right   // Triangle one
				0.0f, 0.5f, 0.0f,			0.0f, 0.0f, 1.0f			// top

				//0.5f, 0.5f, 0.0f,			0.0f, 0.0f, 0.0f			// top right     // Extra vertices for triangle two (for rectangle)
				//-0.5f, 0.5f, 0.0f,		0.0f, 0.0f, 0.0f			// top left
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

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);								 // Link the vertex position attributes to the shader program
			glEnableVertexAttribArray(0);																				 // Enable the vertex position attribute array (disabled by default)
																														 
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));			 // Link the vertex colour attributes to the shader program
			glEnableVertexAttribArray(1);																				 // Enable the vertex colour attribute array

			// NOTE: this is not strictly necessary, but better to be safe and avoid accidental changes to VAOs/VBOs
			glBindBuffer(GL_ARRAY_BUFFER, 0);       // Unbind VBO to avoid further changes
			glBindVertexArray(0);                   // Unbind VAO to avoid further changes
		}

		static void draw() {
			glBindVertexArray(_vao);                               // Bind the appropriate vertex array
			glDrawArrays(GL_TRIANGLES, 0, 3);                     // Draw the fucking triangle already jeez man        
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);  // Draw a rectangle now bitch

			//glBindVertexArray(0);                // Unbind the VAO (not necessary with only 1 VAO but for the sake of completeness)
		}

	private:
		static std::vector<GLfloat> _vertices;
		static std::vector<GLuint> _indices;
		static GLuint _vao, _vbo, _ebo;
	};

	std::vector<GLfloat> VertexInfo::_vertices{};
	std::vector<GLuint> VertexInfo::_indices{};
	GLuint VertexInfo::_vao = 0,
		   VertexInfo::_vbo = 0,
		   VertexInfo::_ebo = 0;
	
}
#endif