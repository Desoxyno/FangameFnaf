#include "raylib.h"

Shader getShader()
{
    Shader shader = LoadShader("../assets/shaders/pbr.vs", "../assets/shaders/pbr.fs");

    if (shader.id == 0)
    {
        TraceLog(LOG_ERROR, "Failed to load PBR shader (pbr.vs / pbr.fs)");
    }

    // Required raylib shader locations
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
    shader.locs[SHADER_LOC_MAP_ALBEDO] = GetShaderLocation(shader, "albedoMap");
    shader.locs[SHADER_LOC_MAP_NORMAL] = GetShaderLocation(shader, "normalMap");
    shader.locs[SHADER_LOC_MAP_ROUGHNESS] = GetShaderLocation(shader, "roughnessMap");
    shader.locs[SHADER_LOC_MAP_OCCLUSION] = GetShaderLocation(shader, "aoMap");
    // NOTE: "matModel" location name is automatically assigned on shader loading,
    // no need to get the location again if using that uniform name

    // Ambient light level (low, for horror atmosphere)
    int ambientLoc = GetShaderLocation(shader, "ambient");
    float ambientValue = 0.05f;  // teste avec une valeur visible d'abord, tu baisseras après
    SetShaderValue(shader, ambientLoc, &ambientValue, SHADER_UNIFORM_FLOAT);

    Vector3 ambientColor = {0.02f, 0.02f, 0.03f};
    SetShaderValue(shader, GetShaderLocation(shader, "ambientColor"), &ambientColor, SHADER_UNIFORM_VEC3);

    // Light count — MUST be updated wherever lights are actually created (rlights.h / CreateLight),
    // otherwise the lighting loop in the fragment shader never executes.
    int numLights = 0;
    SetShaderValue(shader, GetShaderLocation(shader, "numOfLights"), &numLights, SHADER_UNIFORM_INT);

    // Default PBR scalar values (used when a texture slot is disabled, or as a base offset)
    float defaultAO = 1.0f;
    float defaultRoughness = 0.5f;
    float defaultMetallic = 0.0f;
    SetShaderValue(shader, GetShaderLocation(shader, "aoValue"), &defaultAO, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, GetShaderLocation(shader, "roughnessValue"), &defaultRoughness, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, GetShaderLocation(shader, "metallicValue"), &defaultMetallic, SHADER_UNIFORM_FLOAT);

    // UV tiling / offset — must default to (1,1) / (0,0), NOT (0,0), or every texture sample collapses to a single
    // texel
    Vector2 tiling = {1.0f, 1.0f};
    Vector2 offset = {0.0f, 0.0f};
    SetShaderValue(shader, GetShaderLocation(shader, "tiling"), &tiling, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, GetShaderLocation(shader, "offset"), &offset, SHADER_UNIFORM_VEC2);

    // Texture toggles — enable the maps this pipeline actually loads (albedo, normal, roughness, AO)
    int useTexAlbedo = 1;
    int useTexNormal = 1;
    int useTexRoughness = 1;
    int useTexAO = 1;
    int useTexEmissive = 0;
    SetShaderValue(shader, GetShaderLocation(shader, "useTexAlbedo"), &useTexAlbedo, SHADER_UNIFORM_INT);
    SetShaderValue(shader, GetShaderLocation(shader, "useTexNormal"), &useTexNormal, SHADER_UNIFORM_INT);
    SetShaderValue(shader, GetShaderLocation(shader, "useTexRoughness"), &useTexRoughness, SHADER_UNIFORM_INT);
    SetShaderValue(shader, GetShaderLocation(shader, "useTexAO"), &useTexAO, SHADER_UNIFORM_INT);
    SetShaderValue(shader, GetShaderLocation(shader, "useTexEmissive"), &useTexEmissive, SHADER_UNIFORM_INT);

    Vector4 albedoColor = {1.0f, 1.0f, 1.0f, 1.0f};
    SetShaderValue(shader, GetShaderLocation(shader, "albedoColor"), &albedoColor, SHADER_UNIFORM_VEC4);

    Vector4 emissiveColor = {0.0f, 0.0f, 0.0f, 1.0f};
    float emissivePower = 0.0f;
    SetShaderValue(shader, GetShaderLocation(shader, "emissiveColor"), &emissiveColor, SHADER_UNIFORM_VEC4);
    SetShaderValue(shader, GetShaderLocation(shader, "emissivePower"), &emissivePower, SHADER_UNIFORM_FLOAT);

    return shader;
}
