#version 330

// Shader inputs
in vec3 vPosition;
in vec3 vNormal;
in vec3 vTexCoords;
in vec3 vColor;
flat in int vTexture;

// Uniform variables
uniform samplerCube uTextures[32];
uniform int uNbPonctualLights;
uniform vec3 uPonctualLights[100];
uniform bool uDirectionnalLight;

// Shader outputs
out vec4 fFragColor;

float directionnalLightInfluence(vec3 lightDir) {
	float luminosityDirLight = max(-dot(vNormal, lightDir), 0.0);
	return luminosityDirLight;
}

float ponctualLightInfluence(vec3 lightPos) {
	vec3 dir = normalize(vPosition-lightPos);
	float d = length(vPosition - lightPos);
	float luminosityPointLight = max(-dot(vNormal, dir), 0.)/(d*d);
	return luminosityPointLight;
}

void main() {
	float luminosity = 0.3;
	if(uDirectionnalLight) {
		vec3 dir = vec3(1, 1, 1);
		dir = normalize(dir);
		luminosity += directionnalLightInfluence(dir);
	}
	for(int i=0; i<uNbPonctualLights; i++) {
		luminosity += ponctualLightInfluence(uPonctualLights[i]);
	}
	luminosity = min(luminosity, 1);
	if(vTexture != 0) {
		vec4 color = texture(uTextures[vTexture], vTexCoords);
		fFragColor = vec4(color.xyz*luminosity, 1);
	} else if(vColor != vec3(0, 0, 0)) {
		fFragColor = vec4(vColor*luminosity, 1);
	} else {
		vec3 norm = vec3(normalize(vNormal));
		fFragColor = vec4(norm*luminosity, 1);
	}
	 
}
