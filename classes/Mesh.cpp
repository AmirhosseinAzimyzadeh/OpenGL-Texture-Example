#include "Mesh.h"

Mesh::Mesh() {
  VAO = 0;
  VBO = 0;
  IBO = 0;
  indexCount = 0;

}

void Mesh::createMesh(
  GLfloat *vertices,
  unsigned int *indicies,
  unsigned int numberOfVertices,
  unsigned int numberOfIndicies
) {
  indexCount = numberOfIndicies;

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies[0]) * numberOfIndicies, indicies, GL_STATIC_DRAW);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numberOfVertices, vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(
    0, // position (layout 0)
    3,
    GL_FLOAT,
    GL_FALSE, // is dynamic?
    (sizeof(vertices[0]) * 8), // skip
    0 // offset
  );
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(
    1, // texture coordinate (layout 1)
    2,
    GL_FLOAT,
    GL_FALSE, // is dynamic?
    (sizeof(vertices[0]) * 8), // skip
    (void*)(sizeof(vertices[0]) * 3) // offset
  );
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(
    2, // for diffuse light (layout 2)
    3,
    GL_FLOAT,
    GL_FALSE, // is dynamic?
    (sizeof(vertices[0]) * 8), // skip
    (void*)(sizeof(vertices[0]) * 5) // offset
  );
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Mesh::renderMesh() {
  glBindVertexArray(VAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
  glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Mesh::clearMesh() {
  if (IBO != 0) {
    glDeleteBuffers(1, &IBO);
    IBO = 0;
  }

  if (VBO != 0) {
    glDeleteBuffers(1, &VBO);
    VBO = 0;
  }

  if (VAO != 0) {
    glDeleteVertexArrays(1, &VAO);
    VAO = 0;
  }

  indexCount = 0;
}

Mesh::~Mesh() {
  clearMesh();
}
