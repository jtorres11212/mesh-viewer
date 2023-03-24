#version 400
struct light{
   vec3 amb,diff,spec;
   vec4 pst;
};
uniform light l;
struct reflect{
   vec3 ramb,rdiff,rspec,col;
   float fexp;
};
uniform reflect r;
in vec3 n;
in vec4 p;
out vec4 FragColor;
vec 3 ppxl(){
   vec 3 src,nn;
   nn=normalize(n);
   if(l.pst.w==(n)){
      src=normalize(vec3(l.pst));
   }
   else{
      src=normalize(l.pst-p);
   }
   vec3 viw=normalize(vec3(-p));
   vec3 ambnt=l.amb*r.ramb;
   float sdn=max(dot(src,nn),0.0f);
   vec3 diffu=l.diff*r.rdiff*sdn;
   vec3 rfl=2*(sdn)*nn-src;
   if(sdn>0.0f){
      vec3 specu=l.spec*r.rspec*pow(max(dot(r,v),0,r.fexp));
   }
   else{
      specu=vec3(0.0f);
   }
   return(ambnt+diffu+specu);
}

void main()
{
   FragColor = vec4(ppxl, 1.0);
}