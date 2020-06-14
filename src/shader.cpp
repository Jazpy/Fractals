#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include "shader.hpp"

GLuint LoadShaders(const std::string vert_filepath,
  const std::string geom_filepath,
  const std::string frag_filepath)
{
  // Check if we're compiling geometry shader
  bool compile_geom = !geom_filepath.empty();

  // Create the shaders
  GLuint vert_shader_id = glCreateShader(GL_VERTEX_SHADER);
  GLuint frag_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

  GLuint geom_shader_id = 0;
  if(compile_geom)
    geom_shader_id = glCreateShader(GL_GEOMETRY_SHADER);

  // Read the Vertex Shader code from the file
  std::string vertex_shader_code;
  std::ifstream vertex_shader_stream(vert_filepath, std::ios::in);
  if(vertex_shader_stream.is_open())
  {
    std::stringstream sstr;
    sstr << vertex_shader_stream.rdbuf();
    vertex_shader_code = sstr.str();
    vertex_shader_stream.close();
  } else {
    std::cout << "Impossible to open " << vert_filepath << 
      ". Are you in the right directory ? " << std::endl;

    return 0;
  }

  // Read the Geometry Shader code from the file
  std::string geom_shader_code;
  if(compile_geom) {
    std::ifstream geom_shader_stream(geom_filepath, std::ios::in);
    if(geom_shader_stream.is_open())
    {
      std::stringstream sstr;
      sstr << geom_shader_stream.rdbuf();
      geom_shader_code = sstr.str();
      geom_shader_stream.close();
    } else {
      std::cout << "Impossible to open " << geom_filepath << 
        ". Are you in the right directory ? " << std::endl;

      return 0;
    }
  }

  // Read the Fragment Shader code from the file
  std::string fragment_shader_code;
  std::ifstream fragment_shader_stream(frag_filepath, std::ios::in);
  if(fragment_shader_stream.is_open())
  {
    std::stringstream sstr;
    sstr << fragment_shader_stream.rdbuf();
    fragment_shader_code = sstr.str();
    fragment_shader_stream.close();
  } else {
    std::cout << "Impossible to open " << frag_filepath << 
      ". Are you in the right directory ? " << std::endl;

    return 0;
  }

  GLint result = GL_FALSE;
  int info_log_length;

  // Compile Vertex Shader
  std::cout << "Compiling shader: " << vert_filepath << std::endl;
  char const *vertex_source_pointer = vertex_shader_code.c_str();
  glShaderSource(vert_shader_id, 1, &vertex_source_pointer , NULL);
  glCompileShader(vert_shader_id);

  // Check Vertex Shader
  glGetShaderiv(vert_shader_id, GL_COMPILE_STATUS, &result);
  glGetShaderiv(vert_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
  if(info_log_length > 0)
  {
    std::vector<char> vertex_shader_error_message(
      info_log_length + 1);
    glGetShaderInfoLog(vert_shader_id, info_log_length,
      NULL, &vertex_shader_error_message[0]);
    std::cout << &vertex_shader_error_message[0] << std::endl;
  }

  // Compile Geometry Shader
  if(compile_geom) {
    std::cout << "Compiling shader: " << geom_filepath << std::endl;
    char const *geom_source_pointer = geom_shader_code.c_str();
    glShaderSource(geom_shader_id, 1, &geom_source_pointer, NULL);
    glCompileShader(geom_shader_id);

    // Check Geometry Shader
    glGetShaderiv(geom_shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(geom_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if(info_log_length > 0)
    {
      std::vector<char> geom_shader_error_message(
        info_log_length + 1);
      glGetShaderInfoLog(geom_shader_id, info_log_length,
        NULL, &geom_shader_error_message[0]);
      std::cout << &geom_shader_error_message[0] << std::endl;
    }
  }

  // Compile Fragment Shader
  std::cout << "Compiling shader: " << frag_filepath << std::endl;
  char const *fragment_source_pointer = fragment_shader_code.c_str();
  glShaderSource(frag_shader_id, 1, &fragment_source_pointer , NULL);
  glCompileShader(frag_shader_id);

  // Check Fragment Shader
  glGetShaderiv(frag_shader_id, GL_COMPILE_STATUS, &result);
  glGetShaderiv(frag_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
  if(info_log_length > 0)
  {
    std::vector<char> fragment_shader_error_message(
      info_log_length + 1);
    glGetShaderInfoLog(frag_shader_id, info_log_length,
      NULL, &fragment_shader_error_message[0]);
    std::cout << &fragment_shader_error_message[0] << std::endl;
  }

  // Link the program
  std::cout << "Linking program\n" << std::endl;
  GLuint program_id = glCreateProgram();
  glAttachShader(program_id, vert_shader_id);
  glAttachShader(program_id, frag_shader_id);

  if(compile_geom)
    glAttachShader(program_id, geom_shader_id);

  glBindAttribLocation(program_id, 0, "Position");
  glLinkProgram(program_id);

  // Check the program
  glGetProgramiv(program_id, GL_LINK_STATUS, &result);
  glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
  if ( info_log_length > 0 ){
    std::vector<char> program_error_message(info_log_length + 1);
    glGetProgramInfoLog(program_id, info_log_length,
      NULL, &program_error_message[0]);
    std::cout << &program_error_message[0] << std::endl;
  }

  glDetachShader(program_id, vert_shader_id);
  glDetachShader(program_id, frag_shader_id);

  if(compile_geom)
    glDetachShader(program_id, geom_shader_id);

  glDeleteShader(vert_shader_id);
  glDeleteShader(frag_shader_id);

  if(compile_geom)
    glDeleteShader(geom_shader_id);

  return program_id;
}
