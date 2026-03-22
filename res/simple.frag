#version 330 core
in vec3 Normal;

out vec4 FragColor;

void main() {
  vec3 lightDir = normalize(vec3(1, 4, 2));
  float diff = max(dot(normalize(Normal), lightDir), 0.05);
  FragColor = vec4(vec3(diff), 1.0f);
}
