#version 330

// Attributes
layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexScenePosition;
layout(location = 2) in vec3 aVertexNormal;
layout(location = 3) in vec2 aVertexTexCoords;
layout(location = 4) in vec3 aVertexSceneColor;

// Uniform variables : matrix
uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

// Shader outputs
out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexCoords;
out vec3 vColor;

void main() {
	// Homogeneous coordinates
	vec4 vertexPosition = vec4(aVertexPosition + aVertexScenePosition, 1);
	vec4 vertexNormal = vec4(aVertexNormal, 0);

	// Output values
	vPosition = vec3(uMVMatrix * vertexPosition);
    vNormal = vec3(uNormalMatrix * vertexNormal);
    vTexCoords = aVertexTexCoords;
    vColor = aVertexSceneColor;

    // Projected position
    gl_Position = uMVPMatrix * vertexPosition;
}
