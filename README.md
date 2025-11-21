# Blink engine (WIP)

Distributed under [MIT License](LICENSE)

(it will be) My own game engine made with C++ and OpenGL

currently it only draws triangle and nothing more than it -_-

## Todo

[x] Draw a triangle
[ ] Add camera (FPS camera)
[ ] Load .obj to Mesh
...add more later

## Build

```sh
git clone https://github.com/hayattgd/BlinkEngine.git --recursive
cd BlinkEngine

mkdir build
cd build
cmake ..
cmake --build .
```

Run `cmake ..` to copy `res/` to `build/res/`

## Dependencies
- [glad](lib/glad/)
- [glm](lib/glm/)
- OpenGL (from `/usr/include/GL/`)
