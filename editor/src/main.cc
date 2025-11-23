#include "application.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/ext/vector_float3.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "render/mesh.h"
#include "render/shader.h"
#include "component/camera.h"
#include "import/obj_loader.h"
#include "input/mouse.h"
#include "application.h"

using namespace BlinkEngine::Engine;
using namespace BlinkEngine::Engine::Render;
using namespace BlinkEngine::Engine::Component;
using namespace BlinkEngine::Engine::Import;

float lastTime;
Application* app;

int main() {
  app = new Application(800, 600, "BlinkEngine Editor");
  Shader* shader = new Shader(
    "res/default.vert",
    "res/simple.frag"
  );
  shader->Compile();

  Mesh* mesh;
  LoadObj("res/Cubes.obj", &mesh);

  Camera* cam = new Camera(glm::vec3(0, 0, -2), 0, 0, 70, 0.01f, 1000);

  app->DisableCursor();

  while (app->IsRunning()) {
    float t = glfwGetTime();
    float dt = t - lastTime;
    lastTime = t;
    glm::ivec2 size = app->GetWindowSize();
    cam->width = size.x;
    cam->height = size.y;

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (app->IsKeyDown(GLFW_KEY_W)) {
      cam->position += cam->GetFront() * dt * 10.0f;
    }
    if (app->IsKeyDown(GLFW_KEY_A)) {
      cam->position -= cam->GetRight() * dt * 10.0f;
    }
    if (app->IsKeyDown(GLFW_KEY_S)) {
      cam->position -= cam->GetFront() * dt * 10.0f;
    }
    if (app->IsKeyDown(GLFW_KEY_D)) {
      cam->position += cam->GetRight() * dt * 10.0f;
    }
    if (app->IsKeyDown(GLFW_KEY_E)) {
      cam->position += cam->GetUp() * dt * 10.0f;
    }
    if (app->IsKeyDown(GLFW_KEY_Q)) {
      cam->position -= cam->GetUp() * dt * 10.0f;
    }
    cam->UpdateDirection();

    glm::vec2 mouse_relative = app->mouse->GetRelativePos();
    cam->yaw += mouse_relative.x * 0.45f;
    cam->pitch -= mouse_relative.y * 0.45f;

    shader->Use();
    GLuint viewloc = glGetUniformLocation(shader->GetId(), "view");
    glUniformMatrix4fv(
      viewloc, 1, GL_FALSE,
      glm::value_ptr(cam->GetViewMatrix())
    );
    GLuint projloc = glGetUniformLocation(shader->GetId(), "projection");
    glUniformMatrix4fv(
      projloc, 1, GL_FALSE,
      glm::value_ptr(cam->GetProjectionMatrix())
    );
    mesh->Draw();

    app->Update();
  }

  delete cam;
  delete mesh;
  delete shader;

  delete app;
}
