cmake_minimum_required(VERSION 3.16)
project(engine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

set(GLAD_DIR lib/glad)
add_subdirectory(${GLAD_DIR})
target_include_directories(glad PUBLIC ${GLAD_DIR}/include)

find_package(glm CONFIG REQUIRED)

add_executable(
  engine
  src/main.cc
  src/render/mesh.cc
  src/render/shader.cc
  src/fs.cc
)

target_include_directories(engine PUBLIC .)

target_link_libraries(engine glad glfw glm ${CMAKE_DL_LIBS})

file(COPY res DESTINATION .)
