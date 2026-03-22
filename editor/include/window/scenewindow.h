#pragma once

#include "glm/ext/scalar_uint_sized.hpp"

#include "component/camera.h"
#include "gui/iwindow.h"

namespace BlinkEngine::Editor::Window {
class SceneWindow : public Engine::Gui::IWindow {
public:
  SceneWindow();
  ~SceneWindow() override;
  const char *GetName() override;
  void Render() override;
  void Close() override;
  bool IsOpen() const override;

private:
  bool isopen = true;
  bool looking = false;
  void ResizeFrameBuffer(int w, int h);
  int width = 1;
  int height = 1;
  float sensitivity = 0.5f;
  float speed = 0.1f;

  glm::uint32 fbo;
  glm::uint32 colorTex;
  glm::uint32 rbo;

  Engine::Component::Camera* camera;
};
} // namespace BlinkEngine::Editor::Window
