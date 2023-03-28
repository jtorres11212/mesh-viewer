# mesh-viewer

Implements a simple PLY viewer

TODO: Add a representative image for your project here

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
mesh-viewer $ mkdir build
mesh-viewer $ cd build
mesh-viewer/build $ cmake ..
mesh-viewer/build $ start mesh-viewer.sln
```

Your solution file should contain two projects: `mesh-viewer` and `test-ply-mesh`.
To run from the git bash command shell, 

```
mesh-viewer/build $ ../bin/Debug/test-ply-mesh.exe
mesh-viewer/build $ ../bin/Debug/mesh-viewer.exe
```

*macOS*

Open terminal to the directory containing this repository.

```
mesh-viewer $ mkdir build
mesh-viewer $ cd build
mesh-viewer/build $ cmake ..
mesh-viewer/build $ make
```

To run each program from build, you would type

```
mesh-viewer/build $ ../bin/mesh-viewer
```

## Demo of basic features
Normals
![image](https://user-images.githubusercontent.com/94137311/228132503-607c95b5-a40d-4e19-abf4-4e76130714ed.png)
Unlit
![image](https://user-images.githubusercontent.com/94137311/228132621-c989d63d-44c8-4e51-bec6-b6415e9e8c35.png)
Phong pixel is being messed with by light shader
Phong veertex still doesent work
Textures still doesent work

TODO: Document the core features of your viewer (shaders + models)
## Unique features 

TODO: Show the unique features you made
