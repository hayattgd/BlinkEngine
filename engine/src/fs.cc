#include "fs.h"

#include <fstream>
#include <string>

namespace BlinkEngine::Engine {
std::string ReadFile(std::string path) {
  std::string source = "";
  std::string line;
  std::ifstream input(path);
  while (std::getline(input, line)) {
    source += line + "\n";
  }
  input.close();
  return source;
}
} // namespace BlinkEngine::Engine
