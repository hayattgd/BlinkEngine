#pragma once

#include "component/camera.h"
#include "glm/ext/scalar_uint_sized.hpp"

#include "gui/iwindow.h"
#include "imgui.h"

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
  void ResizeFrameBuffer(int w, int h);
  int width = 1;
  int height = 1;
  ImVec2 previous_mouse = ImVec2(0.0f, 0.0f);

  glm::uint32 fbo;
  glm::uint32 colorTex;
  glm::uint32 rbo;

  Engine::Component::Camera* camera;
};
} // namespace BlinkEngine::Editor::Window
