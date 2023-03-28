#version 400

struct light{
   vec4 pos;
   vec3 a;
   vec3 d;
   vec3 s;
};
uniform light l;
struct light2{
   vec4 pos2;
   vec3 a2;
   vec3 d2;
   vec3 s2;
};
uniform light2 l2;
struct light3{
   vec4 pos3;
   vec3 a3;
   vec3 d3;
   vec3 s3;
};
uniform light3 l3;
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
vec3 ppx2(){
   vec3 n=normalize(norm);
   vec3 sn=normalize(vec3(l2.pos2.xyz)-pos);
   vec3 v=normalize(vec3(-pos));
   vec3 rf=reflect(-sn,n);
   return (l2.s2*(r.ra+(r.rd*max(dot(sn,n),0.0))+(r.rs *pow(max(dot(rf,v),0.0),r.fexp))));
}
vec3 ppx3(){
   vec3 n=normalize(norm);
   vec3 sn=normalize(vec3(l3.pos3.xyz)-pos);
   vec3 v=normalize(vec3(-pos));
   vec3 rf=reflect(-sn,n);
   return (l3.s3*(r.ra+(r.rd*max(dot(sn,n),0.0))+(r.rs *pow(max(dot(rf,v),0.0),r.fexp))));
}
void main(){
   FragColor=vec4(ppx()+ppx2()+ppx3(),1.0);
}