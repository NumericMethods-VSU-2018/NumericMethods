#version 330
layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;

out vec3 Color;

void main()
{
	gl_Position = projMatrix * viewMatrix * vec4(position, 0.0, 1.0);
	
	Color = color;
}