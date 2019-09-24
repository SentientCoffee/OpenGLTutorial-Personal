#version 460 core								// Version 4.6
out vec4 finalColour;							// Required final colour out vec4

in vec2 texCoords;								// Texture coordinates taken from vert shader

uniform sampler2D texture1;						// Final texture
uniform sampler2D texture2;						// Final texture

void main() {
	finalColour = mix(texture(texture1, texCoords), texture(texture2, texCoords), 0.2f);
}