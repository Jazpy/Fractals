#pragma once

#include <shape.hpp>

class Cube : public Shape
{
private:
  // (Unique) corners of the cube
  std::vector<glm::vec4> corners;
  void update_corners();

  // Side length
  float length;

public:
  Cube(glm::vec4 center, float length);

  // Getters
  std::vector<glm::vec4> &get_corners()
    { return corners; }
  float get_length()
    { return length; }

  // Overrides for translation, rotation, scaling, etc
  void translate_absolute(glm::vec4 p) override;
  void translate_relative(glm::vec3 d) override;
  void rotate_point(glm::vec3 axis, float angle, glm::vec4 p) override;
};
