#pragma once

#include <fractals/fractal.hpp>
#include <shapes/cube.hpp>

class Infinicube : public Fractal
{
private:
  std::vector<Cube> cubes;

public:
  Infinicube(unsigned int iterations);
};
