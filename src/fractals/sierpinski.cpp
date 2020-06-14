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

  // Add initial pyramid
  pyramids.push_back(Pyramid(vec4(0.0f, 5.0f, 0.0f, 1.0f), 7.5f));

  // Iterate, building more pyramids in each iteration
  for(unsigned int i = 0; i != iterations; ++i)
  {
    vector<Pyramid> new_vec;

    for(Pyramid &p : pyramids)
    {
      // Get old pyramid's center and height
      vec4  old_center  = p.get_center();
      float new_height  = p.get_height() / 2.0f;
      float half_height = new_height     / 2.0f;

      // Calculate new origins (TODO Scaling and taking corners)
      vector<vec4> new_origins;

      // Top
      new_origins.push_back(old_center + vec4(0.0f, half_height, 0.0f, 0.0f));
      // Bases
      new_origins.push_back(old_center + vec4(
        half_height, -half_height, half_height, 0.0f));
      new_origins.push_back(new_origins[1] + vec4(
        -new_height, 0.0f, 0.0f, 0.0f));
      new_origins.push_back(new_origins[2] + vec4(
        0.0f, 0.0f, -new_height, 0.0f));
      new_origins.push_back(new_origins[3] + vec4(
        new_height, 0.0f, 0.0f, 0.0f));

      // Add smaller pyramid at all new origins
      for(vec4 &c : new_origins)
        new_vec.push_back(Pyramid(c, new_height));
    }

    // Throw away old pyramids and keep the new ones
    new_vec.swap(pyramids);
  }

  // Add to final vertex and color buffers
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
