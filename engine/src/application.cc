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

#include "ecs/world.h"
#include "input/mouse.h"

namespace BlinkEngine::Engine {
Application *Application::instance = nullptr;
Application::Application(int width, int height, const char *title) {
  fbwidth = width;
  fbheight = height;
  // GLFW Initialization
  // glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
  glfwWindowHint(GLFW_DEPTH_BITS, 24);
  window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (!window) {
    std::cerr << "\033[31mGLFWwindow failed to initialize\033[0m" << std::endl;
    glfwTerminate();
    return;
  }
  glfwMakeContextCurrent(window);

  glfwSetWindowUserPointer(window, this);
  glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode,
                                int action, int mods) {
    Application *app =
        static_cast<Application *>(glfwGetWindowUserPointer(window));
    app->KeyHandler(window, key, scancode, action, mods);
  });
  glfwSetFramebufferSizeCallback(
      window, [](GLFWwindow *window, int width, int height) {
        Application *app =
            static_cast<Application *>(glfwGetWindowUserPointer(window));
        app->FramebufferSizeCallback(window, width, height);
      });
  glfwSetCursorPosCallback(
      window, [](GLFWwindow *window, double xpos, double ypos) {
        Application *app =
            static_cast<Application *>(glfwGetWindowUserPointer(window));
        app->MouseHandler(window, xpos, ypos);
      });
  glfwSetMouseButtonCallback(
      window, [](GLFWwindow *window, int button, int action, int mods) {
        Application *app =
            static_cast<Application *>(glfwGetWindowUserPointer(window));
        app->MouseButtonHandler(window, button, action, mods);
      });

  // ImGui initialization
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
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

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);

  mouse = new Input::Mouse();
  world = new ECS::World();
}

Application::~Application() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  delete mouse;
  glfwDestroyWindow(window);
  glfwTerminate();
}

void Application::Initialize(int width, int height, const char *title) {
  instance = new Application(width, height, title);
}

void Application::Destroy() { delete instance; }

void Application::Exit() { glfwSetWindowShouldClose(window, GLFW_TRUE); }

bool Application::IsRunning() {
  if (!glfwWindowShouldClose(window)) {
    auto error = glGetError();
    if (error) {
      std::cerr << error << std::endl;
    }
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ResetViewport();
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

void Application::ResetViewport() { glViewport(0, 0, fbwidth, fbheight); }

glm::ivec2 Application::GetWindowSize() {
  int width, height;
  glfwGetWindowSize(window, &width, &height);
  return glm::ivec2(width, height);
}

glm::ivec2 Application::GetFramebufferSize() {
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
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

ECS::World &Application::GetWorld() {
  return *world;
}

void Application::MouseHandler(GLFWwindow *window, double xpos, double ypos) {
  mouse->UpdatePosition(glm::vec2(xpos, ypos));
}

void Application::MouseButtonHandler(GLFWwindow *window, int button, int action,
                                     int mods) {}

void Application::KeyHandler(GLFWwindow *window, int key, int scancode,
                             int action, int mods) {
  if (ImGui::GetIO().WantCaptureKeyboard) {
    return;
  }
}

void Application::FramebufferSizeCallback(GLFWwindow *window, int width,
                                          int height) {
  fbwidth = width;
  fbheight = height;
}

Application &Application::GetInstance() { return *instance; }
} // namespace BlinkEngine::Engine
