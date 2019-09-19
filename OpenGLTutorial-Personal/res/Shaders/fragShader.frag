#version 460 core								// Version 4.6
out vec4 finalColour;							// Required final colour out vec4

in vec3 vertexColour;							// Colour taken from vert shader
in vec2 vertexTexture;							// Texture taken from vert shader

uniform sampler2D finalTexture;					// Final texture

void main() {
	finalColour = texture(finalTexture, vertexTexture);
}