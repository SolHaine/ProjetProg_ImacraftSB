#version 330

// Shader inputs
in vec3 vPosition_vs;

// Uniform variable
uniform vec3 uCursorColor;

// Shader outputs
out vec3 fFragColor;

void main() {
	fFragColor = uCursorColor;
}
