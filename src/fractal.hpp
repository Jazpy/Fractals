#pragma once

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <vector>

class Fractal
{
protected:
  // OpenGL buffer ids
  GLuint vertex_buffer;
  GLuint color_buffer;

  // Vertex data
  std::vector<float> vertex_buffer_data;

  // Color data
  std::vector<float> color_buffer_data;

  // OpenGL VAO
  GLuint vao_id;

  // Count of all line segments in the tree
  int lines = 0;

public:
  ~Fractal();

  // Bind to the current VAO
  void BindToVAO();

  int get_lines() { return this->lines; }

  // Utility
  static void add_to_vec(std::vector<float> &vec, glm::vec3 p);
};
