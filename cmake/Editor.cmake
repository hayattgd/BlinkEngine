set(
  BLINKENGINE_EDITOR_SRC
  editor/src/main.cc
)

add_executable(BlinkEngine_Editor ${BLINKENGINE_EDITOR_SRC})
target_link_libraries(BlinkEngine_Editor PRIVATE BlinkEngine)
target_include_directories(BlinkEngine_Editor PUBLIC editor/include)
target_include_directories(BlinkEngine_Editor PUBLIC engine/include)
