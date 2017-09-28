#version 330 core
in vec2 TexCoord;

out vec4 color;

uniform sampler2D texFramebuffer;
uniform float time;

void main()
{
	color = texture(texFramebuffer, TexCoord);
	color = color * vec4(0.2, 0.2, 0.2, 1.0);

}


/*

#version 330 core

in vec2 TexCoord;
out vec4 color;
uniform sampler2D texFramebuffer;

void main()
{
	#line 1 "screen_shader.frag"
	color = texture(texFramebuffer, TexCoord);
	float avg = (color.r + color.g + color.b) / 3.0;
	color = vec4(avg, avg, avg, 1.0);
}

*/