#pragma once

#include "glm/ext/vector_int2.hpp"
#include "input/mouse.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

namespace BlinkEngine::Engine {
  class Application {
    public:
      Application(int width, int height, const char* title);
      ~Application();
      bool IsRunning();
      void Update();

      glm::ivec2 GetWindowSize();

      // While pressed
      bool IsKeyDown(int key);

      void EnableCursor();
      void ConfineCursor();
      void DisableCursor();

      Input::Mouse* mouse;
    private:
      void MouseHandler(GLFWwindow* window, double xpos, double ypos);
      void KeyHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
      void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

      GLFWwindow* window;
  };
}
