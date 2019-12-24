#version 330

// Shader inputs
in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoords;
in vec3 vColor;

// Shader outputs
out vec3 fFragColor;

void main() {
	if(vColor == vec3(0, 0, 0)) {
		fFragColor = vec3(normalize(vNormal));
	} else {
		fFragColor = vColor;
	}
	 
}
