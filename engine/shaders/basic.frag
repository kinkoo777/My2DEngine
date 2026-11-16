#version 410 core

in vec2 v_Uv;

uniform sampler2D u_Texture;
uniform bool u_UseTexture;
uniform vec3 u_Color;

out vec4 FragColor;

void main()
{
    if (u_UseTexture)
    {
        FragColor = texture(u_Texture, v_Uv)
                  * vec4(u_Color, 1.0);
    }
    else
    {
        FragColor = vec4(u_Color, 1.0);
    }
}