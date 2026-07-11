#version 330

in vec3 fragPosition;
in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragNormal;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

out vec4 finalColor;

#define MAX_LIGHTS 4
#define LIGHT_DIRECTIONAL 0
#define LIGHT_POINT 1

struct Light {
    int enabled;
    int type;
    vec3 position;
    vec3 target;
    vec4 color;
};

uniform Light lights[MAX_LIGHTS];
uniform vec4 ambient;
uniform vec3 viewPos;

void main()
{
    vec4 texelColor = texture(texture0, fragTexCoord);

    vec3 lightDot = vec3(0.0);
    vec3 normal = normalize(fragNormal);
    vec3 viewD = normalize(viewPos - fragPosition);
    vec3 specular = vec3(0.0);

    vec4 tint = colDiffuse * fragColor;

    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        float attenuation = 1.0;

        if (lights[i].enabled == 1)
        {
            vec3 light = vec3(0.0);

            if (lights[i].type == LIGHT_DIRECTIONAL)
            {
                light = -normalize(lights[i].target - lights[i].position);
            }

            else if (lights[i].type == LIGHT_POINT)
            {
                vec3 lightVec = lights[i].position - fragPosition;
                float distance = length(lightVec);

                light = normalize(lightVec);

                attenuation = 1.0 / (1.0 + 0.3 * distance + 0.1 * distance * distance);
            }

            float NdotL = max(dot(normal, light), 0.0);

            // lumière augmentée
            lightDot += lights[i].color.rgb * NdotL * attenuation * 0.1;

            if (NdotL > 0.0)
            {
                float specCo = pow(max(0.0, dot(viewD, reflect(-light, normal))), 16.0);
                specular += specCo * 0.25;
            }
        }
    }


    vec3 ambientLight = ambient.rgb / 50.0;

    finalColor = texelColor * tint * vec4(lightDot + specular + ambientLight, 1.0);

    // garde l'alpha du matériau
    finalColor.a *= tint.a;

    finalColor = clamp(finalColor, 0.0, 1.0);
}