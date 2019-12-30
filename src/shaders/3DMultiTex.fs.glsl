#version 330

// Shader inputs
in vec3 vPosition;
in vec3 vNormal;
in vec3 vTexCoords;
in vec3 vColor;
flat in int vTexture;

// Uniform variables
uniform samplerCube uTextures[32];

// Shader outputs
out vec4 fFragColor;

void main() {
	if(vTexture != 0) {
		fFragColor = texture(uTextures[vTexture], vTexCoords);
	} else if(vColor != vec3(0, 0, 0)) {
		fFragColor = vec4(vColor.x, vColor.y, vColor.z, 1);
	} else {
		vec3 norm = vec3(normalize(vNormal));
		fFragColor = vec4(norm.x, norm.y, norm.z, 1);
	}
	 
}
