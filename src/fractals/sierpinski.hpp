#pragma once

#include <fractals/fractal.hpp>
#include <shapes/pyramid.hpp>

class Sierpinski : public Fractal
{
private:
  std::vector<Pyramid> pyramids;

public:
  Sierpinski(unsigned int iterations);
};
