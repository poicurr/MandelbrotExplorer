#include "../include/core/Window.hpp"

void printUsage() {
  std::cout << "Usage:" << std::endl;
  std::cout << " - press Up key to increase max iteration" << std::endl;
  std::cout << " - press Down key to decrease max iteration" << std::endl;
  std::cout << " - press Escape key to quit" << std::endl;
  std::cout << " - drag to move position" << std::endl;
  std::cout << " - scroll to zoom in/out" << std::endl;
}

int main() {
  printUsage();
  Window window;
  window.start();
}
