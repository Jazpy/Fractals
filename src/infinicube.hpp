#pragma once

#include <fractal.hpp>
#include <cube.hpp>

class Infinicube : public Fractal
{
private:
  std::vector<Cube> cubes;

public:
  Infinicube(unsigned int iterations);
};
