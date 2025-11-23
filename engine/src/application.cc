#include "application.h"

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_int2.hpp"
#include "input/mouse.h"

namespace BlinkEngine::Engine {
  Application::Application(int width, int height, const char* title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
      std::cerr << "\033[31mGLFWwindow failed to initialize" << std::endl;
      glfwTerminate();
      return;
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(
      window,
      [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        app->KeyHandler(window, key, scancode, action, mods);
      }
    );
    glfwSetFramebufferSizeCallback(
      window,
      [](GLFWwindow* window, int width, int height) {
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        app->FramebufferSizeCallback(window, width, height);
      }
    );
    glfwSetCursorPosCallback(
      window,
      [](GLFWwindow* window, double xpos, double ypos) {
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        app->MouseHandler(window, xpos, ypos);
      }
    );

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
      std::cerr << "\033[31mGLAD failed to initialize" << std::endl;
      return;
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    mouse = new Input::Mouse();
  }

  Application::~Application() {
    delete mouse;
    glfwDestroyWindow(window);
    glfwTerminate();
  }

  bool Application::IsRunning() {
    return !glfwWindowShouldClose(window);
  }

  void Application::Update() {
    mouse->Update();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glm::ivec2 Application::GetWindowSize() {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return glm::ivec2(width, height);
  }

  bool Application::IsKeyDown(int key) {
    return glfwGetKey(window, key);
  }

  void Application::EnableCursor() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }

  void Application::ConfineCursor() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
  }

  void Application::DisableCursor() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  }

  void Application::MouseHandler(GLFWwindow* window, double xpos, double ypos) {
    mouse->UpdatePosition(glm::vec2(xpos, ypos));
  }

  void Application::KeyHandler(GLFWwindow* window, int key, int scancode, int action, int mods) {
    switch (key) {
      case GLFW_KEY_ESCAPE:
        if (action == GLFW_PRESS) {
          glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        break;
    }
  }

  void Application::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
  }
}
