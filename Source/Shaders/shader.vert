#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;

out vec4 vertexColor;
out vec2 fragResolution;

uniform mat4 mvp;

void main()
{
	gl_Position = vec4(position, 1.0);
	vertexColor = color;
	fragResolution = vec2(mvp * vec4(position, 1.0));
}
