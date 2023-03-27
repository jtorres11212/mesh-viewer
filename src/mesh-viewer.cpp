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

class MeshViewer:public Window {
public:
    MeshViewer():Window(){
    }

    void setup(){
        files=GetFilenamesInDir("../models","ply");
        renderer.loadShader("normals", "../shaders/normals.vs", "../shaders/normals.fs");
        //renderer.loadShader("phong-vertex", "../shaders/phong-vertex.vs", "../shaders/phong-vertex.fs");
        renderer.loadShader("phong-pixel", "../shaders/phong-pixel.vs", "../shaders/phong-pixel.fs");
        renderer.loadShader("texture","../shaders/texture.vs","../shaders/texture.fs");
        for(string crnt:files){
            PLYMesh eachFile;
            eachFile.load("../models/"+crnt);
            meshes.push_back(eachFile);
        }
        textures.push_back("obunga.png");
        renderer.loadTexture("obunga","../textures/obunga.png",0);
        mesh=meshes[0];
        
    }

    void mouseMotion(int x,int y,int dx,int dy){
        if(clk){
            vp=vp+dy*0.1;
            az=az-dx*0.1;
            float x=r*sin(az)*cos(vp);
            float y=r*sin(vp);
            float z=r*cos(az)*cos(vp);
            eyePos=vec3(x,y,z);
        }
    }

    void mouseDown(int button,int mods){
        clk=true;
    }

    void mouseUp(int button,int mods){
        clk=false;
    }

    void scroll(float dx,float dy){
        r=r+dy;
        float x=r*sin(az)*cos(vp);
        float y=r*sin(vp);
        float z=r*cos(az)*cos(vp);
        eyePos=vec3(x,y,z);
    }
    void keyUp(int key,int mods){
        if(key==GLFW_KEY_N){
            rend=(rend+1)%meshes.size();
        }
        else if(key==GLFW_KEY_M){
            if(rend!=0){
                rend=rend-1;
            }
            else{
                rend=meshes.size()-1;
            }
        }
        else if(key==GLFW_KEY_S){
            sh+=1;
            if(sh>=shdr.size()){
                sh=0;
            }
        }
    }
    void draw(){
        renderer.beginShader(shdr[sh]);
        renderer.texture("diffuseTexture","obunga.png");
        renderer.setUniform("l.a",vec3(0.5f,0.8f,0.5f));
        renderer.setUniform("l.d",vec3(0.5f,0.8f,0.5f));
        renderer.setUniform("l.s",vec3(0.5f,0.8f,0.5f));
        renderer.setUniform("r.ra",vec3(0.1f));
        renderer.setUniform("r.rd",vec3(1.0f));
        renderer.setUniform("r.rs",vec3(0.6f));
        renderer.setUniform("r.fexp",44.4f);
        std::cout << files[rend] << std::endl;
        mesh=meshes[rend];
        float aspect=((float)width())/height();
        renderer.perspective(glm::radians(60.0f),aspect,0.1f,50.0f);
        renderer.lookAt(eyePos,lookPos,up);
        float v1=1;
        float v2=1;
        float v3=1;
        GLfloat xr=mesh.maxBounds().x-mesh.minBounds().x;
        GLfloat yr=mesh.maxBounds().y-mesh.minBounds().y;
        GLfloat zr=mesh.maxBounds().z-mesh.minBounds().z;
        if((xr>zr) || (xr>yr)){
            v1=5.0f/xr;
            v2=5.0f/xr;
            v3=5.0f/xr;
        }
        else if(yr>zr){
            v1=5.0f/yr;
            v2=5.0f/yr;
            v3=5.0f/yr;
        }
        else if(zr>yr){
            v1=5.0f/zr;
            v2=5.0f/zr;
            v3=5.0f/zr;
        }
        renderer.scale(vec3(v1,v2,v3));
        renderer.translate(vec3(0,0,0));
        renderer.lookAt(eyePos,lookPos,up);
        renderer.mesh(mesh);
        //renderer.cube(); // for debugging! 
        renderer.endShader();
    }

protected:
    std::vector<string> files=GetFilenamesInDir("../models","ply");
    std::vector<string> shdr={"normals","phong-pixel","texture"};
    std::vector<string> textures={"obunga.png"}; 
    int sh=0;
    PLYMesh mesh;
    std::vector<PLYMesh> meshes;
    vec3 eyePos=vec3(10,0,0);
    vec3 lookPos=vec3(0,0,0);
    vec3 up=vec3(0,1,0);
    bool clk=false;
    float vp=0;
    float az=0;
    float r=10;
    int rend=0;
};

int main(int argc,char**argv)
{
    MeshViewer viewer;
    viewer.run();
    return 0;
}