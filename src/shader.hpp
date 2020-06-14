#pragma once

#include <string>

GLuint LoadShaders(const std::string vert_filepath,
  const std::string geom_filepath,
  const std::string frag_filepath);
