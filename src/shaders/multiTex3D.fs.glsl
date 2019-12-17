#version 330

// Shader inputs
in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

// Uniform variables
uniform sampler2D uTexture;
uniform sampler2D uTexture2;

// Shader outputs
out vec3 fFragColor;

void main() {
	vec4 color = texture(uTexture, vTexCoords);
	vec4 color2 = texture(uTexture2, vTexCoords);

    fFragColor = color.rgb + color2.rgb;
}
