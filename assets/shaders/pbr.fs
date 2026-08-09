#version 330

#define MAX_LIGHTS              4
#define LIGHT_DIRECTIONAL       0
#define LIGHT_POINT             1
#define PI 3.14159265358979323846

struct Light {
    int enabled;
    int type;
    vec3 position;
    vec3 target;
    vec4 color;
    float intensity;
};

// Input vertex attributes (from vertex shader)
in vec3 fragPosition;
in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragNormal;
in mat3 TBN;

// Output fragment color
out vec4 finalColor;

// Input uniform values
uniform int numOfLights;
uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D roughnessMap;
uniform sampler2D aoMap;
uniform sampler2D emissiveMap; // r: height, g: emissive

uniform vec2 tiling;
uniform vec2 offset;

uniform int useTexAlbedo;
uniform int useTexNormal;
uniform int useTexRoughness;
uniform int useTexAO;
uniform int useTexEmissive;

uniform vec4  albedoColor;
uniform vec4  emissiveColor;
uniform float normalValue;
uniform float metallicValue;
uniform float roughnessValue;
uniform float aoValue;
uniform float emissivePower;

// Input lighting values
uniform Light lights[MAX_LIGHTS];
uniform vec3 viewPos;

uniform vec3 ambientColor;
uniform float ambient;

// Reflectivity in range 0.0 to 1.0
// NOTE: Reflectivity is increased when surface view at larger angle
vec3 SchlickFresnel(float hDotV, vec3 refl)
{
    return refl + (1.0 - refl)*pow(1.0 - hDotV, 5.0);
}

float GgxDistribution(float nDotH, float roughness)
{
    float a = roughness*roughness*roughness*roughness;
    float d = nDotH*nDotH*(a - 1.0) + 1.0;
    d = PI*d*d;
    return (a/max(d, 0.0000001));
}

float GeomSmith(float nDotV, float nDotL, float roughness)
{
    float r = roughness + 1.0;
    float k = r*r/8.0;
    float ik = 1.0 - k;
    float ggx1 = nDotV/(nDotV*ik + k);
    float ggx2 = nDotL/(nDotL*ik + k);
    return ggx1*ggx2;
}

vec3 ComputePBR()
{
    vec2 uv = vec2(fragTexCoord.x*tiling.x + offset.x, fragTexCoord.y*tiling.y + offset.y);

    vec3 albedo = albedoColor.rgb;
    if (useTexAlbedo == 1)
    {
        albedo = texture(albedoMap, uv).rgb*albedoColor.rgb;
    }

    float metallic = clamp(metallicValue, 0.0, 1.0);
    float roughness = clamp(roughnessValue, 0.0, 1.0);
    float ao = clamp(aoValue, 0.0, 1.0);

    if (useTexRoughness == 1)
    {
        roughness = clamp(texture(roughnessMap, uv).r, 0.04, 1.0);
    }
    if (useTexAO == 1)
    {
        ao = texture(aoMap, uv).r;
    }

    vec3 N = normalize(fragNormal);
    if (useTexNormal == 1)
    {
        N = texture(normalMap, uv).rgb;
        N = normalize(N*2.0 - 1.0);
        N = normalize(N*TBN);
    }

    vec3 V = normalize(viewPos - fragPosition);

    vec3 emissive = vec3(0.0);
    if (useTexEmissive == 1)
    {
        emissive = texture(emissiveMap, uv).g*emissiveColor.rgb*emissivePower;
    }

    // If dia-electric use base reflectivity of 0.04, otherwise it is a metal, use albedo as base reflectivity
    vec3 baseRefl = mix(vec3(0.04), albedo.rgb, metallic);
    vec3 lightAccum = vec3(0.0); // Accumulate lighting lum

    for (int i = 0; i < numOfLights; i++)
    {
        vec3 L = normalize(lights[i].position - fragPosition);      // Compute light vector
        vec3 H = normalize(V + L);                                  // Compute halfway bisecting vector
        float dist = length(lights[i].position - fragPosition);     // Compute distance to light
        float attenuation = 1.0/(dist*dist*0.23);                   // Compute attenuation
        vec3 radiance = lights[i].color.rgb*lights[i].intensity*attenuation; // Compute input radiance

        // Cook-Torrance BRDF distribution function
        float nDotV = max(dot(N, V), 0.0000001);
        float nDotL = max(dot(N, L), 0.0000001);
        float hDotV = max(dot(H, V), 0.0);
        float nDotH = max(dot(N, H), 0.0);
        float D = GgxDistribution(nDotH, roughness);   // Larger the more micro-facets aligned to H
        float G = GeomSmith(nDotV, nDotL, roughness);  // Smaller the more micro-facets shadow
        vec3 F = SchlickFresnel(hDotV, baseRefl);       // Fresnel proportion of specular reflectance

        vec3 spec = (D*G*F)/(4.0*nDotV*nDotL);

        // kD = 1.0 - kS, diffuse component is equal to 1.0 - spec component
        vec3 kD = vec3(1.0) - F;

        // Only non-metals should have diffuse light
        kD *= 1.0 - metallic;
        lightAccum += ((kD*albedo.rgb/PI + spec)*radiance*nDotL)*float(lights[i].enabled);
    }

    vec3 ambientFinal = (ambientColor + albedo)*ambient*0.5;

    return (ambientFinal + lightAccum*ao + emissive);
}

void main()
{
    vec3 color = ComputePBR();

    // HDR tonemapping
    color = pow(color, color + vec3(1.0));

    // Gamma correction
    color = pow(color, vec3(1.0/2.2));

    finalColor = vec4(color, 1.0);
}