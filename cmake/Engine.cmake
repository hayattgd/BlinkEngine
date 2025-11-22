set(
  BLINKENGINE_SRC
  engine/src/render/mesh.cc
  engine/src/render/glrenderer.cc
  engine/src/render/shader.cc
  engine/src/fs.cc
  engine/src/component/camera.cc
  engine/src/import/obj_loader.cc
)

add_subdirectory(engine/thirdparty/glad)
add_subdirectory(engine/thirdparty/glfw)
add_subdirectory(engine/thirdparty/glm)

add_library(BlinkEngine STATIC ${BLINKENGINE_SRC})
target_include_directories(BlinkEngine PUBLIC engine/include)
target_link_libraries(BlinkEngine PUBLIC glad glfw glm)
