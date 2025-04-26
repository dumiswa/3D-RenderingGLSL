#version 330 core

in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragUV;

void main() {
    //convert pos from obj to world
    vec4 worldPos = modelMatrix * vec4(vertex, 1.0);
    fragPos = worldPos.xyz;
    fragNormal = mat3(transpose(inverse(modelMatrix))) * normal;
    fragUV = uv;

    //final screen rendering
    gl_Position = projectionMatrix * viewMatrix * worldPos;
}
