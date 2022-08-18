#include <iostream>
#include <string.h>
#include <fstream>
#include <filesystem>
#include <unistd.h>

namespace utils {
  // reading a file
  std::string readFile(const char* filePath) {
    std::string content;
    std::string line;

    std::cout << "READING FILE:" << filePath << '\n';

    std::ifstream targetFile (filePath);
    if (targetFile.is_open()) {
      char c;
      while (targetFile.get(c)) {
        content.push_back(c);
      }
    } else {
      std::cout << "Unable to open file";
    }

    std::cout << "FILE: --" << content << "\n";
    return content;
  }

  float toRadian(float degree) {
    return degree * M_PI / 180.0f;
  }
}

