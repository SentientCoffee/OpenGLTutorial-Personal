#version 460 core								// Version 4.6
layout (location = 0) in vec3 position;			// Position input
layout (location = 1) in vec3 colour;			// Colour input

out vec3 vertexColour;							// vec3 with colour to send to frag shader

void main() {
	gl_Position = vec4(position, 1.0f);			// set position in window
	vertexColour = colour;						// set colour vec3 to send to frag
}