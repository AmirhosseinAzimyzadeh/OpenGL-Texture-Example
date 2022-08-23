#include "gl/glew.h"
#include "stb_image.h"

class Texture {
  public:
    Texture();
    Texture(char* filePath);

    void loadTexture();
    void useTexture();
    void clearTexture();

    ~Texture();
  private:
    GLuint textureId;
    int width, height, bitDepth;

    char* fileLocation;

    void resetProperties();
};
