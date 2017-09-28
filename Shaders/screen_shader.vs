#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;

out vec2 TexCoord;


void main()
{
	#line 1 "screen shader vert"
    gl_Position = vec4(position.x, position.y, 0.0, 1.0);
    TexCoord = texCoord;
}