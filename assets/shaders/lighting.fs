#version 330

in vec3 fragPosition;
in vec2 fragTexCoord;
in vec3 fragNormal;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float lightIntensity;

uniform vec3 viewPosition;

out vec4 finalColor;

void main()
{
    vec4 texel = texture(texture0, fragTexCoord);

    vec3 baseColor =
        texel.rgb *
        colDiffuse.rgb *
        fragColor.rgb;

    vec3 normal = normalize(fragNormal);

    // Direction vers la lumière
    vec3 toLight = lightPosition - fragPosition;

    float distanceToLight = length(toLight);

    vec3 lightDirection =
        toLight / distanceToLight;

    // Éclairage Lambert
    float diffuse =
        max(dot(normal, lightDirection), 0.0);

    // Atténuation
    float attenuation =
        1.0 /
        (
            1.0 +
            0.09 * distanceToLight +
            0.032 * distanceToLight * distanceToLight
        );

    // Lumière finale
    vec3 lighting =
        lightColor *
        lightIntensity *
        diffuse *
        attenuation;

    vec3 result =
        baseColor *
        lighting;

    finalColor =
        vec4(result, texel.a * colDiffuse.a);
}