#version 400

struct light {
  vec4 pos;
};
uniform light l;

struct ref {
  float fexp;
};
uniform ref r;
uniform sampler2D diffuseTexture;

in vec3 p;
in vec3 N;
in vec2 tcords;
out vec4 FragColor;

void ppx(in vec3 pos,in vec3 norm,out vec3 ad,out vec3 spec){
  vec3 n=normalize(norm);
  vec3 s=normalize(vec3(l.pos)-pos);
  vec3 v=normalize(vec3(-pos));
  vec3 rf=reflect(-s,n);
  ad=vec3(0.7,0.7,0.7)*(vec3(0.7,0.7,0.7)+(vec3(0.7,0.7,0.7)*max(dot(s,n),0.0)));
  spec=vec3(0.7,0.7,0.7)*vec3(0.7,0.7,0.7)*pow(max(dot(rf,v),0.0),r.fexp);
}
void main() {
  vec3 ad;
  vec3 spec;
  vec4 col=texture(diffuseTexture,tcords*5.0f);
  ppx(p,N,ad,spec);
  FragColor=(vec4(ad,1.0)*col) + vec4(spec,1.0);
}