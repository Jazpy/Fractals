#define GLM_ENABLE_EXPERIMENTAL

#include <stdlib.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/geometric.hpp>
#include <fractals/tree.hpp>

using glm::vec3;
using std::vector;

typedef vector<float>::iterator vec_iter;

// Fractal construction takes place in the constructor
Tree::Tree(unsigned int iterations)
{
  // Tree will render as lines
  this->mode = GL_LINES;

  // Create initial iteration data, this represents the
  // tree's "trunk"
  vector<float> trunk;

  // Add initial points
  Fractal::add_to_vec(trunk, vec3(0.0f, -1.0f, 0.0f));
  Fractal::add_to_vec(trunk, vec3(0.0f, 12.0f, 0.0f));

  // Iterate, building more of the tree in each iteration
  vector<float> curr = trunk;
  for(int i = 0; i != iterations; ++i)
  {
    // Create new vector for this iteration's data
    vector<float> new_vec;

    // Modify past iteration's data, adding to final buffer
    for(vec_iter it = curr.begin(); it != curr.end(); it += 8)
    {
      // Create glm vectors for easier processing
      vec3 p1(*it,       *(it + 1), *(it + 2));
      vec3 p2(*(it + 4), *(it + 5), *(it + 6));

      // Split in half, midpoint formula
      vec3 midpoint = p1 + p2;
      midpoint = midpoint / 2.0f;

      // Add the split line to the final buffer
      Fractal::add_to_vec(vertex_buffer_data, p1);
      Fractal::add_to_vec(vertex_buffer_data, midpoint);

      // Random color values
      for(int j = 0; j != 6; ++j)
        color_buffer_data.push_back((float)(rand()) / (float)(RAND_MAX));

      ++this->elements;

      // Calculate perpendicular vector
      vec3 original = midpoint - p1;
      vec3 perp = glm::cross(original, vec3(0.0f, 0.0f, 1.0f));
      vec3 endpoint = rotate(p2 - midpoint, 45.0f, perp);

      // We'll create 3 branches
      for(int j = 0; j != 3; ++j)
      {
        // Rotate our new branch
        vec3 curr_endpoint = rotate(endpoint, 400.0f * j, original);

        // Add to this iteration's vector
        Fractal::add_to_vec(new_vec, midpoint);
        Fractal::add_to_vec(new_vec, midpoint + curr_endpoint);
      }
    }

    curr = new_vec;
  }

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
