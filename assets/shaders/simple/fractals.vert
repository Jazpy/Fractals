#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec4 vertex_position;
layout(location = 1) in vec4 vertex_color;

// Output data ; will be interpolated for each fragment.
out vec4 fragment_color;
// Values that stay constant for the whole mesh.
uniform mat4 Modelview;
uniform mat4 Projection;

void main()
{
  // Output position of the vertex, in clip space : MVP * position
  gl_Position = Projection * Modelview * vertex_position;

  // The color of each vertex will be interpolated
  // to produce the color of each fragment
  fragment_color = vertex_color;
}
