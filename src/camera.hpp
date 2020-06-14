#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Camera
{
private:
  // OpenGL shader uniforms
  GLuint projection_u, modelview_u, normal_u;
  GLuint ambient_mat_u, diffuse_mat_u, light_pos_u;

  // Camera matrices
  glm::mat4 initial_lookat;
  glm::mat4 projection;
  glm::mat4 modelview;
  glm::mat4 normal;

  // Lighting
  glm::vec4 light_pos;

  // Update normal matrix
  void update();

public:
  Camera(GLuint program_id, float fov, float aspect_ratio,
    float min_distance, float max_distance,
    glm::vec3 position, glm::vec3 look_at);

  // Rotate around the origin
  void rotate_origin(float delta_time);
};
