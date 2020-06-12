#pragma once

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
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

  // Count of all elements (points, lines, polys) to render
  int elements = 0;

  // Points, lines, polys, etc.
  GLenum mode;

public:
  ~Fractal();

  // Bind to the current VAO
  void BindToVAO();

  // Simple getters
  int    get_elements()
    { return this->elements; }
  GLenum get_mode()
    { return this->mode; }

  // Utility
  static void add_to_vec(std::vector<float> &vec, glm::vec3 p);
  static void add_to_vec(std::vector<float> &vec, glm::vec4 p);
};
