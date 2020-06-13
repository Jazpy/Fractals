#include <stdlib.h>
#include <cube.hpp>

using glm::vec4;
using glm::vec3;
using std::vector;

vec4 random_color()
{
  vec4 color = vec4(
    (float)(rand()) / (float)(RAND_MAX),
    (float)(rand()) / (float)(RAND_MAX),
    (float)(rand()) / (float)(RAND_MAX),
    1.0f
  );

  return color;
}

Cube::Cube(vec4 center, float length)
{
  // Get a random color
  vec4 color = random_color();

  // Get "radius"
  float         half_length = length / 2.0f;
  vector<float> offsets     = {half_length, -half_length};
  vector<vec4>  points;

  for(float o1 : offsets)
    for(float o2 : offsets)
      for(float o3 : offsets)
        points.push_back(vec4(center.x + o3, center.y + o2,
          center.z + o1, 1.0f));

  // Update center and add all polys
  this->center = center;
  this->length = length;

  // k
  add_poly(points[0], points[1], points[2], color, color, color);
  add_poly(points[1], points[3], points[2], color, color, color);
  add_poly(points[4], points[6], points[7], color, color, color);
  add_poly(points[5], points[4], points[7], color, color, color);
  // e
  add_poly(points[5], points[7], points[1], color, color, color);
  add_poly(points[1], points[7], points[3], color, color, color);
  add_poly(points[0], points[2], points[4], color, color, color);
  add_poly(points[2], points[6], points[4], color, color, color);
  // k
  add_poly(points[0], points[5], points[1], color, color, color);
  add_poly(points[0], points[4], points[5], color, color, color);
  add_poly(points[2], points[7], points[6], color, color, color);
  add_poly(points[2], points[3], points[7], color, color, color);

  // Store corners
  update_corners();
}

void Cube::update_corners()
{
  corners = {
    vertex_data[0], vertex_data[1], vertex_data[2],
    vertex_data[4], vertex_data[6], vertex_data[9],
    vertex_data[7], vertex_data[8]
  };
}

void Cube::translate_absolute(vec4 p)
{
  Shape::translate_absolute(p);
  update_corners();
}

void Cube::translate_relative(vec3 d)
{
  Shape::translate_relative(d);
  update_corners();
}

void Cube::rotate_point(vec3 axis, float angle, vec4 p)
{
  Shape::rotate_point(axis, angle, p);
  update_corners();
}
