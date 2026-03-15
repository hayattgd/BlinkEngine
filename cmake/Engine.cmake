set(
  BLINKENGINE_SRC
  engine/src/render/mesh.cc
  engine/src/render/shader.cc
  engine/src/fs.cc
  engine/src/component/camera.cc
  engine/src/import/objloader.cc
  engine/src/application.cc
  engine/src/input/mouse.cc
  engine/src/gui/windowmanager.cc
  engine/src/ecs/world.cc
  engine/src/component/meshrenderer.cc
  engine/src/render/uniformbuffer.cc
)

add_compile_definitions(_GLFW_X11 _GLFW_WAYLAND)

add_subdirectory(engine/thirdparty/glad)
add_subdirectory(engine/thirdparty/glfw)
add_subdirectory(engine/thirdparty/glm)

include(cmake/ImGui.cmake)

add_library(BlinkEngine STATIC ${BLINKENGINE_SRC})
target_include_directories(BlinkEngine PUBLIC engine/include)
target_link_libraries(BlinkEngine PUBLIC imgui glad glfw glm)
