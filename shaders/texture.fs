#version 400

uniform sampler2D diffuseTexture;

in vec2 Uv;
in vec3 color;
in vec3 norm;
out vec4 FragColor;
void main() {
  vec3 col=color*texture(diffuseTexture,Uv*-10.0f).xyz;
	FragColor=vec4(col,1.0);
}