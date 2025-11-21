#include <iostream>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/detail/qualifier.hpp>
#include <glm/ext/vector_float3.hpp>

#include "render/mesh.h"
#include "render/shader.h"

using namespace BlinkEngine::Render;

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
  GLFWwindow* window = glfwCreateWindow(800, 600, "title", nullptr, nullptr);
  if (!window) {
    std::cerr << "\033[31mGLFWwindow failed to initialize" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, KeyHandler);
  glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    std::cerr << "\033[31mGLAD failed to initialize" << std::endl;
    return -1;
  }

  Vertex v1;
  v1.position = glm::vec3(-0.5f, -0.5f, 0.0f); //bottom left
  v1.normal = glm::vec3(0.0f, 0.0f, 1.0f);
  v1.uv = glm::vec2(0.0f, 0.0f);

  Vertex v2;
  v2.position = glm::vec3(0.5f, -0.5f, 0.0f); //bottom right
  v2.normal = glm::vec3(0.0f, 0.0f, 1.0f);
  v2.uv = glm::vec2(1.0f, 0.0f);

  Vertex v3;
  v3.position = glm::vec3(0.0f, 0.5f, 0.0f);
  v3.normal = glm::vec3(0.0f, 0.0f, 1.0f);
  v3.uv = glm::vec2(0.5f, 1.0f);

  Mesh* m = new Mesh(
    {v1, v2, v3},
    {0, 1, 2},
    {}
  );

  Shader* s = new Shader(
    "res/default.vert",
    "res/uv_test.frag"
  );
  s->Compile();

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    s->Use();
    m->Draw();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  delete m;
  delete s;

  glfwTerminate();
}
