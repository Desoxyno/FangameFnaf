#include "shader.h"

Shader getShader()
{
    // Load basic lighting shader
    Shader shader = LoadShader("../assets/shaders/lighting.vs", "../../assets/shaders/lighting.fs");
    // Get some required shader locations
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
    // NOTE: "matModel" location name is automatically assigned on shader loading,
    // no need to get the location again if using that uniform name
    // shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");

    // Ambient light level (some basic lighting)
    int ambientLoc = GetShaderLocation(shader, "ambient");
    SetShaderValue(shader, ambientLoc, (float[4]) {0.0005f, 0.0005f, 0.0005f, 1.0f}, SHADER_UNIFORM_VEC4);
    return shader;
}