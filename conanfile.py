from conans import ConanFile, CMake

class PocoTimerConan(ConanFile):
   settings = "os", "compiler", "build_type", "arch", "compiler"
   requires = "glfw/3.3.7", "glew/2.2.0", "glm/cci.20220420", "stb/cci.20210910"
   generators = "cmake"

  #  def configure(self):
  #     del self.settings.compiler.libcxx