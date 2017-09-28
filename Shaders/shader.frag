#version 330 core
in vec2 TexCoord;
in vec4 ourColour;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

uniform float myUniform;

void main()
{
	vec4 texColour = texture(ourTexture1, TexCoord);// * vec4(ourColour, 1.0f);
	if(texColour.a < 0.1)
		discard;
		
	if(texColour.r == 0)
	{
		color = ourColour;
	}
	else
	{
		color = ourColour * texColour;
	}
}

