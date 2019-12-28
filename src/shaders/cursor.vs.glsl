#version 330

// Attributes
layout(location = 0) in vec3 aVertexPosition;

// Uniform variables : matrix
uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;
uniform vec3 uCursorPosition;
uniform vec3 uCursorColor;

// Shader outputs
out vec3 vPosition_vs;

void main() {
	// Homogeneous coordinates
	vec4 vertexPosition = vec4(aVertexPosition + uCursorPosition, 1);

	// Output values
	vPosition_vs = vec3(uMVMatrix * vertexPosition);

    // Projected position
    gl_Position = uMVPMatrix * vertexPosition;
}
