#include <cube.hpp>

using glm::vec4;
using glm::vec3;
using std::vector;

Cube::Cube(vec4 center, float length)
{
  // White for now
  vec4 color = vec4(1.0f, 1.0f, 1.0f, 1.0f);

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

  // k
  this->add_poly(points[0], points[1], points[2], color, color, color);
  this->add_poly(points[1], points[3], points[2], color, color, color);
  this->add_poly(points[4], points[6], points[7], color, color, color);
  this->add_poly(points[5], points[4], points[7], color, color, color);
  // e
  this->add_poly(points[5], points[7], points[1], color, color, color);
  this->add_poly(points[1], points[7], points[3], color, color, color);
  this->add_poly(points[0], points[2], points[4], color, color, color);
  this->add_poly(points[2], points[6], points[4], color, color, color);
  // k
  this->add_poly(points[0], points[5], points[1], color, color, color);
  this->add_poly(points[0], points[4], points[5], color, color, color);
  this->add_poly(points[2], points[7], points[6], color, color, color);
  this->add_poly(points[2], points[3], points[7], color, color, color);
}
