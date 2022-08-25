#include <iostream>
#include <string.h>
#include <fstream>
#include <filesystem>
#include <unistd.h>
#include "glfw/glfw3.h"
#include "glm/glm.hpp"

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

  void findAverageNormal(
    unsigned int * indices,
    unsigned int sizeOfIndices,
    GLfloat * vertices,
    unsigned int sizeOfVertices,
    unsigned int vertexLength,
    unsigned int normalOffset
  ) {
    // for each triangle
    for(size_t i = 0; i < sizeOfIndices; i += 3) {
      // indices of the triangle
      unsigned index0 = indices[i] * vertexLength;
      unsigned index1 = indices[i + 1] * vertexLength;
      unsigned index2 = indices[i + 2] * vertexLength;

      glm::vec3 edge1(
        vertices[index1] - vertices[index0],
        vertices[index1 + 1] - vertices[index0 + 1],
        vertices[index1 + 2] - vertices[index0 + 2]
      );

      glm::vec3 edge2(
        vertices[index2] - vertices[index0],
        vertices[index2 + 1] - vertices[index0 + 1],
        vertices[index2 + 2] - vertices[index0 + 2]
      );

      glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));

      // change pointers to point at normals at the end of the vertices array
      // actually here we are trying to mutate the vertices array
      index0 += normalOffset;
      index1 += normalOffset;
      index2 += normalOffset;

      vertices[index0] += normal.x;
      vertices[index0 + 1] += normal.y;
      vertices[index0 + 2] += normal.z;

      vertices[index1] += normal.x;
      vertices[index1 + 1] += normal.y;
      vertices[index1 + 2] += normal.z;

      vertices[index2] += normal.x;
      vertices[index2 + 1] += normal.y;
      vertices[index2 + 2] += normal.z;
    }

    // normalize values
    for (size_t i = 0; i < (sizeOfVertices / vertexLength); i++) {
      unsigned int currentOffset = i * vertexLength + normalOffset;
      glm::vec3 vec(
        vertices[currentOffset],
        vertices[currentOffset + 1],
        vertices[currentOffset + 2]
      );

      vec = glm::normalize(vec);

      // replace normalized values
      vertices[currentOffset] = vec.x;
      vertices[currentOffset + 1] = vec.y;
      vertices[currentOffset + 2] = vec.z;
    }
  }
}

