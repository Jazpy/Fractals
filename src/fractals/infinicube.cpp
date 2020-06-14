#include <stdlib.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/geometric.hpp>
#include <fractals/infinicube.hpp>

using glm::vec3;
using glm::vec4;
using std::vector;

// Fractal construction takes place in the constructor
Infinicube::Infinicube(unsigned int iterations)
{
  // Infinicube will render as polygons
  this->mode = GL_TRIANGLES;
  // TODO move to wireframe shader
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // Add initial cube
  cubes.push_back(Cube(vec4(0.0f, 5.0f, 0.0f, 0.0f), 5.0f));

  // Range of base cubes to compute next iteration (only initial cube for now)
  size_t range_start = 0;
  size_t range_end   = 1;

  // Iterate, building more cubes in each iteration
  for(unsigned int i = 0; i != iterations; ++i)
  {
    for(size_t index = range_start; index != range_end; ++index)
    {
      // Get cube's corners, center, and side length
      Cube cube = cubes[index];
      vector<vec4> new_origins = cube.get_corners();
      new_origins.push_back(cube.get_center());

      float new_length = cube.get_length() / 3.0f;

      // Add smaller cube at all new origins
      for(vec4 &c : new_origins)
        cubes.push_back(Cube(c, new_length));
    }

    // Update ranges for next iteration
    range_start = range_end;
    range_end   = cubes.size();
  }

  // Add to final vertex and color buffers
  for(Cube &cube : cubes)
  {
    for(vec4 v_data : cube.get_vertex_data())
      Fractal::add_to_vec(vertex_buffer_data, v_data);
    for(vec4 c_data : cube.get_color_data())
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
