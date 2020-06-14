#version 400 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

uniform mat3 NormalMatrix;

out vec3 gFacetNormal;

void main()
{
  // Get normal for current tri
  vec3 A = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
  vec3 B = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
  gFacetNormal = NormalMatrix * cross(A, B);

  gl_Position = gl_in[0].gl_Position;
  EmitVertex();
  gl_Position = gl_in[1].gl_Position;
  EmitVertex();
  gl_Position = gl_in[2].gl_Position;
  EmitVertex();

  EndPrimitive();
}
