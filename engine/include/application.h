#pragma once

#include "glm/ext/vector_int2.hpp"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "ecs/world.h"
#include "input/mouse.h"

namespace BlinkEngine::Engine {
class Application {
public:
  Application(const Application &) = delete;
  Application &operator=(const Application &) = delete;
  static void Initialize(int width, int height, const char *title);
  static void Destroy();
  void Exit();
  bool IsRunning();
  void Update();

  void ResetViewport();
  glm::ivec2 GetWindowSize();
  glm::ivec2 GetFramebufferSize();
  // While pressed
  bool IsKeyDown(int key);

  void EnableCursor();
  void ConfineCursor();
  void DisableCursor();
  int GetCursorState();

  ECS::World &GetWorld();

  Input::Mouse *mouse;

  static Application &GetInstance();

private:
  Application(int width, int height, const char *title);
  ~Application();
  void MouseHandler(GLFWwindow *window, double xpos, double ypos);
  void MouseButtonHandler(GLFWwindow *window, int button, int action, int mods);
  void KeyHandler(GLFWwindow *window, int key, int scancode, int action,
                  int mods);
  void FramebufferSizeCallback(GLFWwindow *window, int width, int height);

  int fbwidth;
  int fbheight;

  ECS::World *world;
  GLFWwindow *window;
  static Application *instance;
};
} // namespace BlinkEngine::Engine
