#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexTexCoord;
out vec3 Position;
out vec2 TexCoord;
out vec3 norm;
out vec3 color;
out vec2 Uv;
uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;

void main(){
    norm=VertexNormal;
    Uv=VertexPosition.xy;
    color=vec3(1.0,1.0,1.0);
    gl_Position = MVP * vec4(VertexPosition, 1.0);

}