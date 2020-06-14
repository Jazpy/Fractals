#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <camera.hpp>

using glm::vec3;  using glm::vec4;
using glm::mat4;  using glm::mat3;
using glm::quat;

using glm::degrees;     using glm::radians;
using glm::lookAt;      using glm::transpose;
using glm::angleAxis;   using glm::toMat4;
using glm::perspective;

Camera::Camera(GLuint program_id, float fov, float aspect_ratio,
  float min_distance, float max_distance, vec3 position, vec3 lookat)
{
  // Get shader uniforms
  projection_u = glGetUniformLocation(program_id, "Projection");
  modelview_u = glGetUniformLocation(program_id, "Modelview");
  normal_u = glGetUniformLocation(program_id, "NormalMatrix");
  ambient_mat_u = glGetUniformLocation(program_id, "AmbientMaterial");
  diffuse_mat_u = glGetUniformLocation(program_id, "DiffuseMaterial");
  light_pos_u = glGetUniformLocation(program_id, "LightPos");

  // Update uniforms
  glUniform3f(ambient_mat_u, 0.1f, 0.1f, 0.15f);
  glUniform3f(diffuse_mat_u, 0.0f, 0.4f, 0.75f);

  glUniform4f(light_pos_u, 0.0f, 10.0f, 0.0f, 1.0f);

  // Initialize projection matrix
  projection = perspective(radians(fov),
    aspect_ratio, min_distance, max_distance);

  // Initialize camera view matrix
  vec3 up_vector(0, 1, 0);
  initial_lookat = lookAt(position, lookat, up_vector);
  modelview = initial_lookat;
}

void Camera::update()
{
  // Update normal matrix
  normal = mat3(modelview);
  // Pack and transpose normal matrix
  float packed[9] =
  {
    normal[0][0], normal[1][0], normal[2][0],
    normal[0][1], normal[1][1], normal[2][1],
    normal[0][2], normal[1][2], normal[2][2]
  };

  // Send MVP to shaders
  glUniformMatrix4fv(projection_u, 1, 0, &projection[0][0]);
  glUniformMatrix4fv(modelview_u, 1, 0, &modelview[0][0]);
  glUniformMatrix3fv(normal_u, 1, 0, &packed[0]);
}

void Camera::rotate_origin(float delta_time)
{
  // Get rotation for this frame
  static float rotation = 0.0f;
  rotation += 0.005f * delta_time;

  // Create rotation matrix
  vec3 axis(0.0f, 1.0f, 0.0f);
  quat rotation_quat   = glm::angleAxis(glm::degrees(rotation), axis);
  mat4 rotation_matrix = glm::toMat4(rotation_quat);

  // Rotate
  modelview = initial_lookat * rotation_matrix;

  // Update normal matrix
  update();
}
