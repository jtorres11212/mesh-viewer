#version 400

layout (location=0) in vec3 vPos;
layout (location=1) in vec3 vNormals;
layout (location=2) in vec2 vTextureCoords;

struct light{
   vec4 pos;
   vec3 a;
   vec3 d;
   vec3 s;
};
uniform light l;

struct ref{
   vec3 ra;
   vec3 rd;
   vec3 rs;
   float fexp;
};
uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;
uniform ref m;

out vec3 ints;

void main(){
   vec3 norEye=normalize(NormalMatrix*vNormals);
   vec4 posEye=ModelViewMatrix*vec4(vPos,1.0);
   vec3 ss=normalize(vec3(l.pos - posEye));
   vec3 v=normalize(-posEye.xyz);
   vec3 rf=reflect(-ss, norEye);
   float sn=max(dot(ss,norEye), 0.0);
   vec3 amb=l.a*r.ra;
   vec3 dif=l.d*r.rd*sn;
   vec3 spec=vec3(0.0);
   if(sn > 0.0){
      spec=l.s*r.rs*pow(max(dot(rf,v), 0.0),r.fexp);
   }

   ints= amb + dif + spec;

   gl_Position=MVP*vec4(vPos, 1.0);
}