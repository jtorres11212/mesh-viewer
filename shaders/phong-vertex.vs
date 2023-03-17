#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormals;
layout (location = 2) in vec2 vTextureCoords;

uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;
uniform bool HasUV;
out vec3 ints;
struct light{
   vec3 a,d,s;
   vec4 pst;
};
uniform light l;
struct reflect{
   vec3 ra,rd,rs;
   float fexp;
};
uniform reflect r;
vec3 pv(vec4 p,vec3 n){
   vec3 src;
   if(l.pst.w==0.0f){
      src=normalize(vec3(l.pst));
   }
   else{
      
   }
}
void main()
{
   gl_Position = MVP * vec4(vPos, 1.0);
}
