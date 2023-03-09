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
   void PLYMesh::clear(){
      mb=vec3(-100000,-100000,-100000);
      mnb=vec3(100000,100000,100000);
      _positions.clear;
      _faces.clear;
      _normals.clear;
   }

   bool PLYMesh::load(const std::string& filename){
      if (_positions.size() != 0) {
         std::cout << "WARNING: Cannot load different files with the same PLY mesh\n";
         return false;
      }
      // todo: your code here
      //you need to load ALL your models at the start of the program, so you cant reuse a plymesh, you
      //need to make an array of plymeshes and load them in setup
      ifstream f;
      f.open(filename);
      if (!f.is_open()){
         return false;
      }
      string dad;
      f>>dad;
      if(dad.compare("ply")!=0){
         return false;
      }
      while(dad.compare("vertex")!= 0){
         f>>dad;
      }
      f>>dad;
      stringstream str;
      int numv;
      str<<dad;
      str>>numv;
      while(dad.compare("face")!= 0){
         f>>dad;
      }
      f>>dad;
      int numFace;
      stringstream strstr2;
      strstr2<<dad;
      strstr2>>numFace;
      printf("numface: %d\n", numFace);
      while(dad.compare("end_header")!=0){
         f>>dad;
      }
      for(int i=0;i<numv;i++){
         GLfloat a,b,c,d,e,f;
         f>>a;
         f>>b;
         f>>c;
         f>>d;
         f>>e;
         f>>f;
         mnx=std::min(a,mnx);
         mny=glm::min(b,mny);
         mnz=glm::min(c,mnz);
         mx=glm::max(a,mx);
         my=glm::max(b,my);
         mz=glm::max(c,mz);
         vec3 vtx=vec3{a,b,c};
         _positions.push_back(a);
         _positions.push_back(b);
         _positions.push_back(c);
         _normals.push_back(d);
         _normals.push_back(e);
         _normals.push_back(f);
         f>>dad;
         f>>dad;
      }
      for(int i=0;i<numFace;i++) {
         f>>dad;
         GLuint a,b,c;
         f>>a;
         f>>b;
         f>>c;
         _faces.push_back(a);
         _faces.push_back(b);
         _faces.push_back(c);
      }

      return false;
   }

   glm::vec3 PLYMesh::minBounds() const{
      return glm::vec3(0);
   }

   glm::vec3 PLYMesh::maxBounds() const{
      return glm::vec3(0);
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
}

