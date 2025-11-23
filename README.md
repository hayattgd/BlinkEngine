# Blink engine (WIP)

Distributed under [MIT License](LICENSE)

(it will be) My own game engine made with C++ and OpenGL

## Todo

- [x] Draw a triangle
- [x] Add camera (FPS camera)
- [x] Load .obj to Mesh
- [x] Split main() and Editor class
- [ ] Add editor UI
- [ ] Implement basic classes (Entity, Component, Transform...)
- [ ] Do some physics
- [ ] Lua scripting

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
- [glad](engine/thirdparty/glad/)
- glm
- glfw
- OpenGL (from `/usr/include/GL/`)
