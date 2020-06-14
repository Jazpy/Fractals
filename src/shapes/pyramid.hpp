#pragma once

#include <shapes/shape.hpp>

class Pyramid : public Shape
{
private:
  // (Unique) vertices of the pyramid
  std::vector<glm::vec4> corners;
  void update_corners();

  // Pyramid height
  float height;

public:
  Pyramid(glm::vec4 center, float height);

  // Getters
  std::vector<glm::vec4> &get_corners()
    { return corners; }
  float get_height()
    { return height; }

  // Overrides for translation, rotation, scaling, etc
  void translate_absolute(glm::vec4 p) override;
  void translate_relative(glm::vec3 d) override;
  void rotate_point(glm::vec3 axis, float angle, glm::vec4 p) override;
};
