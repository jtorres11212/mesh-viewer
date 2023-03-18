#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormals;
layout (location = 2) in vec2 vTextureCoords;

uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;
uniform bool HasUV;
out vec3 lstrngth;
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
      src=normalize(l.pst-p);
   }
   float sdn=max(dot(s,n),0);
   vec3 vcam=normalize(vec3(-p));
   vec 3 amb,diff,spec;
   ambi=l.a*r.ra;
   diff=l.d*r.rd*sdn;
   vec3 angchk=2*sdn*n-s;
   if(sdn>0.0f){
      spec=l.s*r.rs*pow(max(dot(angchk,vcam),0),r.fexp);
   }
   else{
      spec=vec3(0.0f);
   }
   return (amb+diff+spec);

}
void main()
{
   vec3 n=normalize(NormalMatrix*vNormals);
   vec3 p=ModelViewMatrix*vec4(vPos,1.0);
   lstrngth=pv(p,n);
   gl_Position = MVP * vec4(vPos, 1.0);
}
