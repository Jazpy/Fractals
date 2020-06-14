#include <stdlib.h>
#include <shapes/pyramid.hpp>

using glm::vec4;
using glm::vec3;
using std::vector;

Pyramid::Pyramid(vec4 center, float height)
{
  // White for now
  vec4 color = vec4(1.0f, 1.0f, 1.0f, 1.0f);

  // Store corners
  update_corners();
}

void Pyramid::update_corners()
{
  corners = {
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
