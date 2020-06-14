#include <stdlib.h>
#include <shapes/pyramid.hpp>

using glm::vec4;
using glm::vec3;
using std::vector;

vec4 pyramid_random_color()
{
  vec4 color = vec4(
    (float)(rand()) / (float)(RAND_MAX),
    (float)(rand()) / (float)(RAND_MAX),
    (float)(rand()) / (float)(RAND_MAX),
    1.0f
  );

  return color;
}

Pyramid::Pyramid(vec4 center, float height)
{
  // TODO Random color for now, until lighting is better
  vec4 color = pyramid_random_color();

  // Get "radius"
  float         half_height = height / 2.0f;
  vector<vec4>  points;

  // Top of pyramid
  points.push_back(center + vec4(0.0f, half_height, 0.0f, 0.0f));
  // Base
  points.push_back(center + vec4(half_height,
                                -half_height,
                                 half_height,
                                 0.0f));
  points.push_back(points[1] + vec4(-height, 0.0f, 0.0f, 0.0f));
  points.push_back(points[2] + vec4(0.0f, 0.0f, -height, 0.0f));
  points.push_back(points[3] + vec4(height, 0.0f, 0.0f, 0.0f));

  // Update center and add all polys
  this->center = center;
  this->height = height;

  add_poly(points[0], points[2], points[1], color, color, color);
  add_poly(points[0], points[3], points[2], color, color, color);
  add_poly(points[0], points[4], points[3], color, color, color);
  add_poly(points[0], points[1], points[4], color, color, color);
  add_poly(points[1], points[2], points[4], color, color, color);
  add_poly(points[3], points[4], points[2], color, color, color);

  // Store corners
  update_corners();
}

void Pyramid::update_corners()
{
  corners = {
    vertex_data[0], vertex_data[1], vertex_data[2],
    vertex_data[5], vertex_data[8]
  };
}

void Pyramid::translate_absolute(vec4 p)
{
  Shape::translate_absolute(p);
  update_corners();
}

void Pyramid::translate_relative(vec3 d)
{
  Shape::translate_relative(d);
  update_corners();
}

void Pyramid::rotate_point(vec3 axis, float angle, vec4 p)
{
  Shape::rotate_point(axis, angle, p);
  update_corners();
}
