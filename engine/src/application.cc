#include "application.h"

#include <GLFW/glfw3.h>
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_int2.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "input/mouse.h"

namespace BlinkEngine::Engine {
  Application* Application::instance = nullptr;
  Application::Application(int width, int height, const char* title) {
    // GLFW Initialization
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
    glfwSetMouseButtonCallback(
      window,
      [](GLFWwindow* window, int button, int action, int mods) {
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        app->MouseButtonHandler(window, button, action, mods);
      }
    );

    //ImGui initialization
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    // OpenGL Initialization
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
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    delete mouse;
    glfwDestroyWindow(window);
    glfwTerminate();
  }

  void Application::Initialize(int width, int height, const char* title) {
    instance = new Application(width, height, title);
  }

  void Application::Quit() {
    delete instance;
  }

  bool Application::IsRunning() {
    if (!glfwWindowShouldClose(window))
    {
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();
      return true;
    }

    return false;
  }

  void Application::Update() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
    if (ImGui::GetIO().WantCaptureKeyboard) {
      return false;
    } else {
      return glfwGetKey(window, key);
    }
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

  int Application::GetCursorState() {
    return glfwGetInputMode(window, GLFW_CURSOR);
  }

  void Application::MouseHandler(GLFWwindow* window, double xpos, double ypos) {
    mouse->UpdatePosition(glm::vec2(xpos, ypos));
  }

  void Application::MouseButtonHandler(GLFWwindow* window, int button, int action, int mods) {

  }

  void Application::KeyHandler(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (ImGui::GetIO().WantCaptureKeyboard) { return; }
    switch (key) {
      case GLFW_KEY_ESCAPE:
        if (action == GLFW_PRESS) {
          EnableCursor();
        }
        break;
      case GLFW_KEY_SPACE:
        if (action == GLFW_PRESS) {
          DisableCursor();
        }
        break;
    }
  }

  void Application::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
  }

  Application& Application::GetInstance() {
    return *instance;
  }
}
