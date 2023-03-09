//--------------------------------------------------
// Author:
// Date:
// Description: Loads PLY files in ASCII format
//--------------------------------------------------

#include <cmath>
#include <string>
#include <vector>
#include "agl/window.h"
#include "plymesh.h"
#include "osutils.h"

using namespace std;
using namespace glm;
using namespace agl;

class MeshViewer : public Window {
public:
   MeshViewer() : Window() {
   }

   void setup() {
      // mesh.load("../models/cube.ply");
      f=GetFilenamesInDir("../models","ply");
      for(string all:f){
         PLYMesh allf;
         allf.load("../models/"+all);
         meshes.push_back(allf);
      }
      mesh=meshes[0];
   }
   void mouseMotion(int x, int y, int dx, int dy) {
      if(clk){
         float x,y,z;
         ga=ga-dx*.1;
         be=be+dy*.1;
         x=r*sin(ga)*cos(be);
         y=r*sin(be);
         z=r*cos(ga)*cos(be);
         eyePos=vec3(x,y,z);
      }
   }

   void mouseDown(int button, int mods) {
      clk=true;
   }

   void mouseUp(int button, int mods) {
      clk=false;
   }

   void scroll(float dx, float dy) {
      float x,y,z;
      r=r+dy;
      x=r*sin(ga)*cos(be);
      y=r*sin(be);
      z=r*cos(ga)*cos(be);
      eyePos=vec3(x,y,z);
   }

   void keyUp(int key, int mods) {
      if(key==GLFW_KEY_N){
         img=(img+1)%meshes.size();
      }
      if(key==GLFW_KEY_M){
         if(img!=0){
            img=img-1;
         }
         else{
            img=meshes.size()-1;
         }
      }
   }

   void draw() {
      float aspect = ((float)width()) / height();
      mesh=meshes[img];
      std::cout<<f[img]<<std::endl;
      renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);
      renderer.lookAt(eyePos,lookPos,up);
      float x,y,z;
      GLfloat xr,yr,zr;
      xr=mesh.maxBounds().x-mesh.minBounds().x;
      yr=mesh.maxBounds().y-mesh.minBounds().y;
      zr=mesh.maxBounds().z-mesh.minBounds().z;
      if(xr>yr||xr>zr){
         x=5.0f/xr;
         y=5.0f/xr;
         z=5.0f/xr;
      }
      if(yr>zr){
         x=5.0f/yr;
         y=5.0f/yr;
         z=5.0f/yr;
      }
      if(zr>yr){
         x=5.0f/zr;
         y=5.0f/zr;
         z=5.0f/zr;
      }
      renderer.rotate(vec3(0,0,0));
      renderer.scale(vec3(x,y,z));
      renderer.mesh(mesh);
      renderer.translate(vec3(0,0,0));
      //renderer.mesh(mesh);
      renderer.cube(); // for debugging!
   }

protected:
   float be=0,ga=0,r=10;
   int img=0; 
   std::vector<PLYMesh> meshes;
   PLYMesh mesh;
   vec3 eyePos = vec3(10, 0, 0);
   vec3 lookPos = vec3(0, 0, 0);
   vec3 up = vec3(0, 1, 0);
   std::vector<string> f=GetFilenamesInDir("../models","ply");
   bool clk=false;
};

int main(int argc, char** argv)
{
   MeshViewer viewer;
   viewer.run();
   return 0;
}

