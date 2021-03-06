#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <shapes/shape.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using std::vector;

typedef vector<float>::iterator vec_iter;

void Shape::add_poly(vec4 p1, vec4 p2, vec4 p3, vec4 c1, vec4 c2, vec4 c3)
{
  // Push vertex data
  vertex_data.push_back(p1);
  vertex_data.push_back(p2);
  vertex_data.push_back(p3);

  // Push color data
  color_data.push_back(c1);
  color_data.push_back(c2);
  color_data.push_back(c3);
}

void Shape::translate_absolute(vec4 p)
{
  // Get translation matrix
  vec3 direction = vec3(p) - vec3(center);
  mat4 translation = glm::translate(mat4(1.0f), direction);

  // Apply translation to all points
  center = p;

  for(vec4 &v : vertex_data)
    v = translation * v;
}

void Shape::translate_relative(vec3 d)
{
  // Get new center
  vec4 new_center = center + vec4(d, 1.0f);
  // Translate absolute
  translate_absolute(new_center);
}

void Shape::rotate_point(vec3 axis, float angle, vec4 p)
{
  // Build transformation matrix
  mat4 translation     = glm::translate(mat4(1.0f), vec3(p));
  mat4 inv_translation = glm::inverse(translation);
  mat4 rotation        = glm::rotate(mat4(1.0f), angle, axis);
  mat4 transform       = translation * rotation * inv_translation;

  // Apply transformation to all points
  center = transform * center;

  for(vec4 &p : vertex_data)
    p = transform * p;
}
