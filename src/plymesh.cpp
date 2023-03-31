//--------------------------------------------------
// Author:
// Date:
// Description: Loads PLY files in ASCII format
//--------------------------------------------------
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include "plymesh.h"

using namespace std;
using namespace glm;

namespace agl{

   
   PLYMesh::PLYMesh(const std::string& filename){
      load(filename);
   }
   PLYMesh::PLYMesh(){
   }
   void PLYMesh::init(){
      assert(_positions.size() != 0);
      initBuffers(&_faces,&_positions,&_normals);
   }
   PLYMesh::~PLYMesh(){
   }
   bool PLYMesh::load(const std::string& filename){
      int numv,numf,vx,vy,vz,v,cnt;
      
      float x1,x2,y1,y2,z1,z2;
      if (_positions.size() != 0) {
         std::cout << "WARNING: Cannot load different files with the same PLY mesh\n";
         return false;
      }
      std::ifstream f(filename);
      if (!f.is_open()){
         return false;
      }
      std::string dad;
      if (!std::getline(f,dad)||dad!="ply") {
         return false;
      }
      while(std::getline(f,dad)&&dad!="end_header"){
         std::string str;
         std::istringstream curr(dad);
         printf("%s\n",dad.c_str());
         curr>>str;
      
         if(str=="element"){
            int num;
            std::string elem;
            curr>>elem>>num;
            if (elem=="vertex"){
               numv=num;
            }
            else if(elem=="face"){
               numf=num;
            }
         }
         
   }
   for (int i=0;i<numv;i++){
      std::getline(f,dad);
      std::istringstream str(dad);
      str>>x1>>y1>>z1>>x2>>y2>>z2;
      _positions.push_back(x1);
      _positions.push_back(y1);
      _positions.push_back(z1);
      _normals.push_back(x2);
      _normals.push_back(y2); 
      _normals.push_back(z2);
   }
   for(int i=0;i<numf;i++){
      f>>cnt>>vx>>vy>>vz;
      _faces.push_back(vx);
      _faces.push_back(vy);
      _faces.push_back(vz);
      for(int j=0;j<cnt-3;j++){
         f>>v;
         _faces.push_back(vx-1);
         _faces.push_back(v-1);
         _faces.push_back(v-1);
      }
   }
      return false;
   }
   void PLYMesh::clear(){
      _positions.clear();
      _normals.clear();
      _faces.clear();
   }
   glm::vec3 PLYMesh::minBounds() const{
      glm::vec3 mnb(_positions[0],_positions[1],_positions[2]);
      for(int i=0;i<_positions.size();i+=3){
         glm::vec3 vert(_positions[i],_positions[i+1],_positions[i+2]);
         if (vert.x<mnb.x){
            mnb.x=vert.x;
         }
         if(vert.y<mnb.y){
            mnb.y=vert.y;
         }
         if(vert.z<mnb.z){
            mnb.z=vert.z;
         }
      }
      return mnb;
   }

   glm::vec3 PLYMesh::maxBounds() const{
      glm::vec3 mb(_positions[0],_positions[1],_positions[2]);
      for(int i=0;i<_positions.size();i+=3){
         glm::vec3 vert(_positions[i],_positions[i+1],_positions[i+2]);
         if (vert.x>mb.x){
            mb.x=vert.x;
         }
         if(vert.y>mb.y){
            mb.y=vert.y;
         }
         if(vert.z>mb.z){
            mb.z=vert.z;
         }
      }
      return mb;
   }

   int PLYMesh::numVertices() const{
      return _positions.size()/3;
   }

   int PLYMesh::numTriangles() const{
      return _faces.size()/3;
   }

   const std::vector<GLfloat>& PLYMesh::positions() const{
      return _positions;
   }

   const std::vector<GLfloat>& PLYMesh::normals() const{
      return _normals;
   }

   const std::vector<GLuint>& PLYMesh::indices() const{
      return _faces;
   }
   /**float uvcalc(w,h,x,y,pic,pc){
      renderer.loadTexture(pic,pc)//loads png for texture
      float u,v;
      //set w and h = to width/ height of photo and add parameter to read in photo
      u=x/w;
      v=y/h;
      return(u,v);

   }**/
}

