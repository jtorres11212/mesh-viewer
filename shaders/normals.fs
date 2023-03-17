#version 400
in vec3 coln
out vec4 FragColor;
void main()
{
   FragColor = vec4(coln, 1.0);
}
