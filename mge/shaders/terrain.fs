#version 330 core

in vec2 fragUV;
in vec3 fragNormal;
in vec3 fragPos;

out vec4 fragColor;

uniform sampler2D diffuse1;
uniform sampler2D diffuse2;
uniform sampler2D diffuse3;
uniform sampler2D diffuse4;
uniform sampler2D splatmap;

uniform vec3 lightDir;

void main() {
    //sample
    vec4 blend = texture(splatmap, fragUV);
    float total = blend.r + blend.g + blend.b + blend.a;
    if (total == 0.0) total = 1.0; // avoid division by zero
    blend /= total;

    vec4 tex1 = texture(diffuse1, fragUV * 40.0);
    vec4 tex2 = texture(diffuse2, fragUV * 40.0);
    vec4 tex3 = texture(diffuse3, fragUV * 40.0);
    vec4 tex4 = texture(diffuse4, fragUV * 40.0);

    vec4 color = tex1 * blend.r + tex2 * blend.g + tex3 * blend.b + tex4 * blend.a;

    //simple lighting
    //vec3 norm = normalize(fragNormal);
    //float diff = max(dot(norm, normalize(-lightDir)), 0.4); // ambient included

    fragColor = vec4(color.rgb, 1.0);
}
