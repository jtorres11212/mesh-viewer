#version 400

in vec3 ints;
out vec4 FragColor;

void main(){
   FragColor = vec4(ints, 1.0);
}