#version 400

struct light{
   vec4 pos;
   vec3 a;
   vec3 d;
   vec3 s;
   vec3 ints;
};
uniform light l;
struct ref{
   vec3 ra;
   vec3 rd;
   vec3 rs;
   float fexp;
};
uniform ref r;
uniform sampler2D diffuseTexture;
in vec2 uv;
in vec3 pos;
in vec3 norm;
out vec4 FragColor;
const float uvs=3.0f;

vec3 ppx(){
   vec3 n=normalize(norm);
   vec3 sn=normalize(vec3(l.pos.xyz)-pos);
   float sdn=max(dot(sn,n),0.0f);
   vec3 v=normalize(vec3(-pos));
   vec3 rf=reflect(-sn,n);
   vec3 spec=vec3(0.0f);
   vec3 amb=l.ints*r.ra;
   vec3 diff=l.ints*r.rd*sdn;
   if(sdn>0.0f){
      spec=l.ints*r.rs*pow(max(dot(rf,v),0),r.fexp);
   }
   return ((amb+diff)*texture(diffuseTexture,uv*uvs).xyz+spec);
}

void main(){
   FragColor=vec4(ppx(),1.0);
}