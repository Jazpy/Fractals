#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>

class Shape
{
protected:
  // Vertex data
  std::vector<glm::vec4> vertex_data;

  // Color data
  std::vector<glm::vec4> color_data;

  // Object's center
  glm::vec4 center;

public:
  // Getters
  std::vector<glm::vec4> const &get_vertex_data()
    { return vertex_data; }
  std::vector<glm::vec4> const &get_color_data()
    { return color_data; }
  glm::vec4 get_center()
    { return center; }

  // Add polygon to shape
  void add_poly(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3,
    glm::vec4 c1, glm::vec4 c2, glm::vec4 c3);

  // Translate all to new center
  virtual void translate_absolute(glm::vec4 p);
  // Translate all along direction
  virtual void translate_relative(glm::vec3 d);
  // Shift center without affecting polygons
  void shift_center(glm::vec4 p)
    { center = p; }

  // Rotate around axis and point
  virtual void rotate_point(glm::vec3 axis, float angle, glm::vec4 p);
  // Rotate around axis and center
  void rotate_center(glm::vec3 axis, float angle)
    { rotate_point(axis, angle, center); }
};
