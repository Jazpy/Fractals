#version 400 core

layout (location = 0) in vec4 Pos;
layout (location = 1) in vec4 Col;

uniform mat4 Modelview;
uniform mat4 Projection;

void main()
{
  gl_Position  = Projection * Modelview * Pos;
}
