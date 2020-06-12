#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec4 vertex_position_modelspace;
layout(location = 1) in vec4 vertex_color;

// Output data ; will be interpolated for each fragment.
out vec4 fragment_color;
// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main(){

  // Output position of the vertex, in clip space : MVP * position
  gl_Position =  MVP * vertex_position_modelspace;

  // The color of each vertex will be interpolated
  // to produce the color of each fragment
  fragment_color = vertex_color;
}

