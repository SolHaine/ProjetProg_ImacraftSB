#version 330

// Shader inputs
in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

// Uniform variables
uniform sampler2D uTexture;

// Shader outputs
out vec3 fFragColor;

void main() {
	vec4 color = texture(uTexture, vTexCoords);
    fFragColor = color.rgb;
}
