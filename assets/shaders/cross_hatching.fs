#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

out vec4 finalColor;

const float HATCH_SCALE = 8.0;
const float HATCH_WIDTH = 1.5;

const float LUM_1 = 0.80;
const float LUM_2 = 0.60;
const float LUM_3 = 0.40;
const float LUM_4 = 0.20;

float line(float value)
{
    return step(value, HATCH_WIDTH);
}

void main()
{
    vec4 texel = texture(texture0, fragTexCoord) * colDiffuse;

    float lum = dot(texel.rgb, vec3(0.2126, 0.7152, 0.0722));

    vec3 color = texel.rgb;

    float hatch1 = line(mod(gl_FragCoord.x + gl_FragCoord.y, HATCH_SCALE));
    float hatch2 = line(mod(gl_FragCoord.x - gl_FragCoord.y, HATCH_SCALE));
    float hatch3 = line(mod(gl_FragCoord.x + gl_FragCoord.y + 4.0, HATCH_SCALE));
    float hatch4 = line(mod(gl_FragCoord.x - gl_FragCoord.y + 4.0, HATCH_SCALE));

    if (lum < LUM_1)
        color *= mix(1.0, 0.75, hatch1);

    if (lum < LUM_2)
        color *= mix(1.0, 0.70, hatch2);

    if (lum < LUM_3)
        color *= mix(1.0, 0.65, hatch3);

    if (lum < LUM_4)
        color *= mix(1.0, 0.55, hatch4);

    finalColor = vec4(color, texel.a);
}