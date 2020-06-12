#pragma once

#include <shape.hpp>

class Cube : public Shape
{
public:
  Cube(glm::vec4 center, float length);
};
