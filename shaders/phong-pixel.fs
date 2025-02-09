#version 400

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
uniform ref r;

in vec3 pos;
in vec3 norm;
out vec4 FragColor;

vec3 ppx(){
   vec3 n=normalize(norm);
   vec3 sn=normalize(vec3(l.pos.xyz)-pos);
   vec3 v=normalize(vec3(-pos));
   vec3 rf=reflect(-sn,n);
   return (l.s*(r.ra+(r.rd*max(dot(sn,n),0.0))+(r.rs *pow(max(dot(rf,v),0.0),r.fexp))));
}

void main(){
   FragColor=vec4(ppx(),1.0);
}