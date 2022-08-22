#include <iostream>
#include <string.h>
#include <fstream>
#include <filesystem>
#include <unistd.h>
#include "glfw/glfw3.h"

namespace utils {
  // reading a file
  std::string readFile(const char* filePath) {
    std::string content;
    std::string line;

    std::ifstream targetFile (filePath);
    if (targetFile.is_open()) {
      char c;
      while (targetFile.get(c)) {
        content.push_back(c);
      }
    } else {
      std::cout << "Unable to open file";
    }

    return content;
  }

  float toRadian(float degree) {
    return degree * M_PI / 180.0f;
  }

  GLfloat lastTime = 0.0f;
  GLfloat getDeltaTime() {
    GLfloat currentTime = glfwGetTime();
    GLfloat deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    return deltaTime;
  }
}

