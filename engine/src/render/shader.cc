#include "render/shader.h"

#include <cstddef>
#include <iostream>
#include <string>

#include "glad/glad.h"
#include "glm/ext/scalar_uint_sized.hpp"

#include "fs.h"

namespace BlinkEngine::Engine::Render {
  bool get_shader_compile_error(glm::uint32 shader) {
    int success;
    char info_log[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 512, NULL, info_log);
      std::cerr << "OpenGL Shader Compile Error:\n" << info_log << std::endl;
    }
    return success;
  }

  bool get_program_link_error(glm::uint32 program) {
    int success;
    char info_log[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(program, 512, NULL, info_log);
      std::cerr << "OpenGL Program Link Error:\n" << info_log << std::endl;
    }
    return success;
  }

  Shader::Shader(std::string vert_path, std::string frag_path) {
    vert = vert_path;
    frag = frag_path;
    id = -1;
  }

  void Shader::UniformBlockBinding(const char* uniform_name, glm::uint32 binding_point) {
    glm::uint32 index = glGetUniformBlockIndex(id, uniform_name);
    glUniformBlockBinding(id, index, binding_point);
  }

  void Shader::Compile() {
    glm::uint32 vert_shader;
    vert_shader = glCreateShader(GL_VERTEX_SHADER);
    std::string vert_src_str = ReadFile(vert);
    const char* vert_src = vert_src_str.c_str();
    std::cout << "compiling: "<< vert << std::endl;
    glShaderSource(vert_shader, 1, &vert_src, NULL);
    glCompileShader(vert_shader);
    if (!get_shader_compile_error(vert_shader)) {
      glDeleteShader(vert_shader);
      return;
    }

    glm::uint32 frag_shader;
    frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string frag_src_str = ReadFile(frag);
    const char* frag_src = frag_src_str.c_str();
    std::cout << "compiling: "<< frag << std::endl;
    glShaderSource(frag_shader, 1, &frag_src, NULL);
    glCompileShader(frag_shader);
    if (!get_shader_compile_error(frag_shader)) {
      glDeleteShader(vert_shader);
      glDeleteShader(frag_shader);
      return;
    }

    glm::uint32 shader_program;
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vert_shader);
    glAttachShader(shader_program, frag_shader);
    glLinkProgram(shader_program);
    if (!get_program_link_error(shader_program)) {
      std::cerr << "Shader link error!" << std::endl;
      glDeleteProgram(shader_program);
      glDeleteShader(vert_shader);
      glDeleteShader(frag_shader);
      return;
    }
    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);
    std::cout << "Shader id:" << shader_program << std::endl;
    id = shader_program;
  }

  glm::uint32 Shader::GetId() {
    return id;
  }

  void Shader::Use() {
    glUseProgram(id);
  }
}
