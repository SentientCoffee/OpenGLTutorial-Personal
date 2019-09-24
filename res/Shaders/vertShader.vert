#version 460 core								// Version 4.6
layout (location = 0) in vec3 position;			// Position input
layout (location = 1) in vec2 textureCoords;	// Texture coordinate input

out vec2 texCoords;								// vec2 with texture coordinates to send to frag shader

uniform mat4 model;								// view transform matrices
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(position, 1.0f);

	texCoords = textureCoords;								// set texture vec2 to send to frag
}