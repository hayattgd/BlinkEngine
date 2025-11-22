#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/ext/vector_float3.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "render/mesh.h"
#include "render/shader.h"
#include "component/camera.h"
#include "import/obj_loader.h"

using namespace BlinkEngine::Engine;
using namespace BlinkEngine::Engine::Render;
using namespace BlinkEngine::Engine::Component;
using namespace BlinkEngine::Engine::Import;

double lastX = 0, lastY = 0;
float xoffset = 0, yoffset = 0;
float lastTime = 0.0f;
bool firstMouse = true;

void MouseHandler(GLFWwindow* window, double xpos, double ypos) {
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  xoffset = xpos - lastX;
  yoffset = ypos - lastY;
  lastX = xpos;
  lastY = ypos;
}

void KeyHandler(GLFWwindow* window, int key, int scancode, int action,
                 int mods) {
  switch (key) {
    case GLFW_KEY_ESCAPE:
      if (action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
      }
      break;
  }
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
  glfwWindowHint(GLFW_DEPTH_BITS, 24);
  GLFWwindow* window = glfwCreateWindow(800, 600, "title", nullptr, nullptr);
  if (!window) {
    std::cerr << "\033[31mGLFWwindow failed to initialize" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, KeyHandler);
  glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
  glfwSetCursorPosCallback(window, MouseHandler);
  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    std::cerr << "\033[31mGLAD failed to initialize" << std::endl;
    return -1;
  }

  Shader* shader = new Shader(
    "res/default.vert",
    "res/simple.frag"
  );
  shader->Compile();

  Mesh* mesh;
  LoadObj("res/Cubes.obj", &mesh);

  Camera* cam = new Camera(glm::vec3(0, 0, -2), 0, 0, 70, 0.01f, 1000);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  while (!glfwWindowShouldClose(window)) {
    float t = glfwGetTime();
    float dt = t - lastTime;
    lastTime = t;
    int width;
    int height;
    glfwGetWindowSize(window, &width, &height);
    cam->width = width;
    cam->height = height;

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (glfwGetKey(window, GLFW_KEY_W)) {
      cam->position += cam->GetFront() * dt * 10.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_A)) {
      cam->position -= cam->GetRight() * dt * 10.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_S)) {
      cam->position -= cam->GetFront() * dt * 10.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_D)) {
      cam->position += cam->GetRight() * dt * 10.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_E)) {
      cam->position += glm::vec3(0, 1, 0) * dt * 10.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_Q)) {
      cam->position -= glm::vec3(0, 1, 0) * dt * 10.0f;
    }
    cam->UpdateDirection();

    cam->yaw += xoffset * 0.45f;
    cam->pitch -= yoffset * 0.45f;

    shader->Use();
    GLuint viewloc = glGetUniformLocation(shader->GetId(), "view");
    glUniformMatrix4fv(viewloc, 1, GL_FALSE, glm::value_ptr(cam->GetViewMatrix()));
    GLuint projloc = glGetUniformLocation(shader->GetId(), "projection");
    glUniformMatrix4fv(projloc, 1, GL_FALSE, glm::value_ptr(cam->GetProjectionMatrix()));
    mesh->Draw();

    xoffset = 0;
    yoffset = 0;
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  delete cam;
  delete mesh;
  delete shader;

  glfwTerminate();
}
