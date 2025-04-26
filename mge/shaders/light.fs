#version 330 core

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragUV;

out vec4 fragColor;

uniform sampler2D diffuseTexture;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float lightIntensity;

uniform vec3 cameraPosition;

uniform float materialShininess;
uniform vec3 materialSpecular;

void main() {
    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(lightPosition - fragPos);
    vec3 viewDir = normalize(cameraPosition - fragPos);

    // Ambient
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess);
    vec3 specular = spec * materialSpecular;

    // Attenuation
    float distance = length(lightPosition - fragPos);
    //float attenuation = diff / (1.0 + 0.09 * distance + 0.032 * distance * distance);
    float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * distance * distance);

    vec3 lighting = (ambient + diffuse + specular) * attenuation * lightIntensity;

    vec4 texColor = texture(diffuseTexture, fragUV);
    fragColor = vec4(lighting, 1.0) * texColor;
    //fragColor = vec4(fragUV, 0.0 , 1.0);
    //fragColor = texColor;
    //fragColor = vec4(fragUV, 0.0, 1.0); //should display gradient for debugging
}
