#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform sampler2D heightmap;
uniform float heightMultiplier;

out vec2 fragUV;
out vec3 fragNormal;
out vec3 fragPos;

void main() {
    //sample the height
    float height = texture(heightmap, uv).r;
    vec3 displacedPos = vertex + normal * height * heightMultiplier * 1.5;

    //local space to world space
    vec4 worldPos = modelMatrix * vec4(displacedPos, 1.0);

    //send to fs
    fragUV = uv;

    //for light
    //fragNormal = mat3(transpose(inverse(modelMatrix))) * normal;
    //fragPos = worldPos.xyz;

    //send to gpu
    gl_Position = projectionMatrix * viewMatrix * worldPos;
}
