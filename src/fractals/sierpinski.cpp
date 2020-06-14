#include <stdlib.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/geometric.hpp>
#include <fractals/sierpinski.hpp>

using glm::vec3;
using glm::vec4;
using std::vector;

// Fractal construction takes place in the constructor
Sierpinski::Sierpinski(unsigned int iterations)
{
  // Sierpinski will render as polygons
  this->mode = GL_TRIANGLES;
  // TODO move to wireframe shader
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  for(Pyramid &p : pyramids)
  {
    for(vec4 v_data : p.get_vertex_data())
      Fractal::add_to_vec(vertex_buffer_data, v_data);
    for(vec4 c_data : p.get_color_data())
      Fractal::add_to_vec(color_buffer_data, c_data);
  }

  this->elements = vertex_buffer_data.size() / 4;

  // Bind vertex buffer data
  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER,
    vertex_buffer_data.size() * sizeof(float),
    &vertex_buffer_data[0], GL_STATIC_DRAW);

  // Bind color buffer data
  glGenBuffers(1, &color_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
  glBufferData(GL_ARRAY_BUFFER,
    color_buffer_data.size() * sizeof(float),
    &color_buffer_data[0], GL_STATIC_DRAW);
}
