#version 460 core
layout (location = 0) in vec3 aPos;

uniform float shift;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y - shift, aPos.z, 1.0);
}


