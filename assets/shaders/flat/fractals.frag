#version 400 core

in  vec3 gFacetNormal;
out vec4 FragColor;

uniform vec3 AmbientMaterial;
uniform vec3 DiffuseMaterial;
uniform vec4 LightPos;
uniform mat4 Modelview;

void main()
{
  vec3 N = normalize(gFacetNormal);

  // Transform LightPos into eye coordinates
  vec4 eye_pos = LightPos * Modelview;
  vec3 L = vec3(eye_pos.x, eye_pos.y, eye_pos.z);

  float df = abs(dot(N, L));
  vec3 color = AmbientMaterial + df * DiffuseMaterial;

  FragColor = vec4(color, 1.0);
}
