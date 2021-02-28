#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
uniform float rOffset;

void main()
{
    gl_Position = vec4(aPos, 1.0);

	if (aPos.x == 0.5)
	{
		ourColor = vec3(aColor.r - rOffset, aColor.g + rOffset, aColor.b);
	}
	else{
		ourColor = vec3(aColor.r, aColor.g, aColor.b);
	}
}


