
#version 410 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;

uniform mat4 u_Model;

uniform vec2 u_Offset;


out vec3 vColor;

void main()
{
    gl_Position = u_Model * vec4(aPos, 0.0, 1.0);

    vColor = aColor;
}
