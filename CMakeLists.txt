cmake_minimum_required(VERSION 3.16)
project(BlinkEngine VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/Engine.cmake)
include(cmake/Editor.cmake)

file(COPY res DESTINATION .)
