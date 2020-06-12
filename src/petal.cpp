#define GLM_ENABLE_EXPERIMENTAL

#include <stdlib.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/geometric.hpp>
#include <petal.hpp>
#include <iostream>

using glm::vec3;
using std::vector;

typedef vector<float>::iterator vec_iter;

// Fractal construction takes place in the constructor
Petal::Petal(unsigned int iterations, float angle)
{
  // Create initial iteration data, this represents the
  // petal's first line
  vector<float> root;

  // Add initial points
  Fractal::add_to_vec(root, vec3(0.0f,  0.0f, 0.0f));
  Fractal::add_to_vec(root, vec3(0.0f, 10.0f, 0.0f));
  ++this->lines;

  // Iterate, building more of the petal in each iteration
  vector<float> curr = root;
  for(int i = 0; i != iterations; ++i)
  {
    // Create new vector for this iteration's data
    vector<float> new_vec;

    // Modify past iteration's data
    for(vec_iter it = curr.begin(); it != curr.end(); it += 6)
    {
      // Create glm vectors for easier processing
      vec3 p1(*it,       *(it + 1), *(it + 2));
      vec3 p2(*(it + 3), *(it + 4), *(it + 5));
      vec3 original = p2 - p1;

      // Segment line in fourths
      vec3 midpoint_a = p1 + (original * (1.0f / 4.0f));
      vec3 midpoint_b = p1 + (original * (2.0f / 4.0f));
      vec3 midpoint_c = p1 + (original * (3.0f / 4.0f));

      // Begin building trapezoid with previous line as the base

      // Get perpendicular vector
      vec3 perp = glm::cross(original, vec3(1.0f, 0.0f, 0.0f));

      // Build endpoints
      vec3 endpoint_al = rotate(midpoint_a - p1, 45.0f, perp) + p1;
      vec3 endpoint_cl = rotate(p2 - midpoint_c, 45.0f, perp) + midpoint_c;
      vec3 endpoint_ar = rotate(midpoint_a - p1, -45.0f, perp) + p1;
      vec3 endpoint_cr = rotate(p2 - midpoint_c, -45.0f, perp) + midpoint_c;

      // Add to vec
      Fractal::add_to_vec(new_vec, p1);
      Fractal::add_to_vec(new_vec, endpoint_al);
      Fractal::add_to_vec(new_vec, endpoint_al);
      Fractal::add_to_vec(new_vec, midpoint_b);
      Fractal::add_to_vec(new_vec, midpoint_b);
      Fractal::add_to_vec(new_vec, endpoint_cl);
      Fractal::add_to_vec(new_vec, endpoint_cl);
      Fractal::add_to_vec(new_vec, p2);

      Fractal::add_to_vec(new_vec, p2);
      Fractal::add_to_vec(new_vec, endpoint_cr);
      Fractal::add_to_vec(new_vec, endpoint_cr);
      Fractal::add_to_vec(new_vec, midpoint_b);
      Fractal::add_to_vec(new_vec, midpoint_b);
      Fractal::add_to_vec(new_vec, endpoint_ar);
      Fractal::add_to_vec(new_vec, endpoint_ar);
      Fractal::add_to_vec(new_vec, p1);

      this->lines += 8;
    }

    new_vec.swap(curr);
  }

  // Add to final vertex buffer
  curr.swap(vertex_buffer_data);

  // Push RED for all vertices
  for(int i = 0; i != vertex_buffer_data.size(); ++i)
    color_buffer_data.push_back((float)(rand()) / (float)(RAND_MAX));
    //color_buffer_data.push_back(1.0);

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
