#include "window/scenewindow.h"

#include "application.h"
#include "component/camera.h"
#include "ecs/world.h"
#include "glad/glad.h"
#include "imgui.h"
#include "imgui_internal.h"
#include <GL/glext.h>
#include <iostream>

namespace BlinkEngine::Editor::Window {
SceneWindow::SceneWindow() {
  std::cout << "width:" << width << ", height:" << height  << std::endl;
  glGenFramebuffers(1, &fbo);
  glObjectLabel(GL_FRAMEBUFFER, fbo, -1, "scene framebuffer");
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);

  glGenTextures(1, &colorTex);
  glObjectLabel(GL_TEXTURE, colorTex, -1, "scene colorTex");
  glBindTexture(GL_TEXTURE_2D, colorTex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         colorTex, 0);

  glGenRenderbuffers(1, &rbo);
  glObjectLabel(GL_RENDERBUFFER, rbo, -1, "scene depth");
  glBindRenderbuffer(GL_RENDERBUFFER, rbo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                            GL_RENDERBUFFER, rbo);

  auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (status != GL_FRAMEBUFFER_COMPLETE) {
    std::cerr << "\033[31mFramebuffer incomplete! (";
    switch (status) {
      case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
	std::cerr << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
	break;
      case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
	std::cerr << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
	break;
      case GL_FRAMEBUFFER_UNSUPPORTED:
	std::cerr << "GL_FRAMEBUFFER_UNSUPPORTED";
	break;
      default:
	std::cerr << status;
	break;
    }
    std::cerr << ")\033[0m" << std::endl;
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  camera = nullptr;
}

SceneWindow::~SceneWindow() {
  glDeleteRenderbuffers(1, &rbo);
  glDeleteTextures(1, &colorTex);
  glDeleteFramebuffers(1, &fbo);
}

const char *SceneWindow::GetName() { return "Scene"; }

void SceneWindow::Render() {
  if (camera != nullptr) {
    // float rot[2] = {camera->pitch, camera->yaw};
    // ImGui::SliderFloat2("Rotation", rot, -360.0f, 360.0f);
    // camera->pitch = rot[0];
    // camera->yaw = rot[1];

    float pos[3] = {camera->position.x, camera->position.y, camera->position.z};
    ImGui::SliderFloat3("Position", pos, -10.0f, 10.0f);
    camera->position.x = pos[0];
    camera->position.y = pos[1];
    camera->position.z = pos[2];
    
    auto mouse = ImGui::GetMousePos();
    if (ImGui::IsMouseDown(ImGuiMouseButton_Right)) {
      camera->yaw += mouse.x - previous_mouse.x;
      camera->pitch -= mouse.y - previous_mouse.y;
    }
    previous_mouse = mouse;

    camera->width = width;
    camera->height = height;
    camera->UpdateDirection();
  }
  auto cursorpos = ImGui::GetCursorScreenPos();
  auto spaces = ImGui::GetContentRegionAvail();
  if (spaces.x != width || spaces.y != height) {
    ResizeFrameBuffer(spaces.x, spaces.y);
  }
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  glViewport(0, 0, width, height);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClearDepth(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  auto &world = Engine::Application::GetInstance().GetWorld();
  for (auto entity : world.GetEntities()) {
    auto* camera_component = world.GetComponent<Engine::Component::Camera>(entity);
    if (camera_component != nullptr) {
      camera = camera_component;
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
