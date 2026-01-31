#include "window/scenewindow.h"

#include "application.h"
#include "component/camera.h"
#include "ecs/world.h"
#include "glad/glad.h"
#include "imgui.h"
#include <GL/glext.h>
#include <iostream>

namespace BlinkEngine::Editor::Window {
SceneWindow::SceneWindow() {
  glGenBuffers(1, &fbo);
  glGenFramebuffers(1, &fbo);

  glGenTextures(1, &colorTex);
  glBindTexture(GL_TEXTURE_2D, colorTex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         colorTex, 0);

  glGenRenderbuffers(1, &rbo);
  glBindRenderbuffer(GL_RENDERBUFFER, rbo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                            GL_RENDERBUFFER, rbo);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::cerr << "Framebuffer incomplete!" << std::endl;
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

SceneWindow::~SceneWindow() {
  glDeleteRenderbuffers(1, &rbo);
  glDeleteTextures(1, &colorTex);
  glDeleteFramebuffers(1, &fbo);
}

const char *SceneWindow::GetName() { return "Scene"; }

void SceneWindow::Render() {
  auto cursorpos = ImGui::GetCursorScreenPos();
  auto spaces = ImGui::GetContentRegionAvail();
  ResizeFrameBuffer(spaces.x, spaces.y);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  glViewport(0, 0, width, height);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  auto &world = Engine::Application::GetInstance().GetWorld();
  for (auto entity : world.GetEntities()) {
    auto *camera = world.GetComponent<Engine::Component::Camera>(entity);
    if (camera != nullptr) {
      camera->Render();
    }
  }
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  Engine::Application::GetInstance().ResetViewport();
  ImGui::GetWindowDrawList()->AddImage(
      (ImTextureRef)colorTex, cursorpos,
      ImVec2(cursorpos.x + width, cursorpos.y + height), ImVec2(0, 1),
      ImVec2(1, 0));
}

void SceneWindow::Close() { isopen = false; }

bool SceneWindow::IsOpen() const { return isopen; }

void SceneWindow::ResizeFrameBuffer(int w, int h) {
  width = w;
  height = h;
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  glBindTexture(GL_TEXTURE_2D, colorTex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
               0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         colorTex, 0);

  glBindRenderbuffer(GL_RENDERBUFFER, rbo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
} // namespace BlinkEngine::Editor::Window
