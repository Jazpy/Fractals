#include <fractal.hpp>

using std::vector;
using glm::vec3;

Fractal::~Fractal()
{
  // Cleanup VBO
  glDeleteBuffers(1, &vertex_buffer);
  glDeleteBuffers(1, &color_buffer);

  // Cleanup attributes
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

void Fractal::BindToVAO()
{
  // Bind our VBOs
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
}

void Fractal::add_to_vec(vector<float> &vec, vec3 p)
{
  vec.push_back(p.x);
  vec.push_back(p.y);
  vec.push_back(p.z);
}
