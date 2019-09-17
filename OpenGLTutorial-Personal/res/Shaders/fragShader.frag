#version 460 core								// Version 4.6
out vec4 finalColour;							// Required final colour out vec4

in vec3 vertexColour;							// Colour taken from vert shader

void main() {
	finalColour = vec4(vertexColour, 1.0f);		// Change vertexColour from vert shader to vec4
												// and set the final colour to that value
}