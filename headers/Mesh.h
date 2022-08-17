#include "gl/glew.h"

class Mesh {
  public: Mesh();
  
  void createMesh(
    GLfloat *vertices,
    unsigned int *indicies,
    unsigned int numberOfVertices,
    unsigned int numberOfIndicies
  );
  void renderMesh();
  void clearMesh();
  
  ~Mesh();

  private:
    GLuint VAO, VBO, IBO;
    GLsizei indexCount;
};
