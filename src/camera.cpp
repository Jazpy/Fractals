#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <camera.hpp>

using glm::vec3;  using glm::mat4;
using glm::quat;

Camera::Camera(GLuint program_id, float fov, float aspect_ratio,
  float min_distance, float max_distance, vec3 position, vec3 look_at)
{
  // Get our handle
  matrix_id = glGetUniformLocation(program_id, "MVP");

  // Initialize matrices

  // Projection matrix
  projection = glm::perspective(glm::radians(fov),
    aspect_ratio, min_distance, max_distance);

  // Camera matrix
  view = glm::lookAt
    (
      position,         // Camera position
      look_at,          // where it's looking
      vec3(0, 1, 0)     // (0, -1, 0) is upside-down
    );

  // model matrix: an identity matrix (model will be at the origin)
  model = mat4(1.0f);

  // Our ModelViewProjection: multiplication of our 3 matrices
  MVP  = projection * view * model; 
}

void Camera::rotate_origin(float delta_time)
{
  // Get rotation for this frame
  float speed = 0.005f * delta_time;

  // Create rotation matrix
  vec3 axis(0.0f, 1.0f, 0.0f);
  quat rotation_quat   = glm::angleAxis(glm::degrees(speed), axis);
  mat4 rotation_matrix = glm::toMat4(rotation_quat);

  // Rotate
  model *= rotation_matrix;
  MVP    = projection * view * model;
}

GLfloat *Camera::get_transformation()
{
  return &MVP[0][0];
}

GLint Camera::get_handle()
{
  return matrix_id;
}
