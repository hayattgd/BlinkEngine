set(
  BLINKENGINE_EDITOR_SRC
  editor/src/main.cc
  editor/src/window/scenewindow.cc
  editor/src/window/worldwindow.cc
  editor/src/window/propertywindow.cc
)

add_executable(BlinkEngine_Editor ${BLINKENGINE_EDITOR_SRC})

target_link_libraries(BlinkEngine_Editor PUBLIC BlinkEngine)
target_include_directories(BlinkEngine_Editor PUBLIC editor/include)
target_include_directories(BlinkEngine_Editor PUBLIC engine/include)
