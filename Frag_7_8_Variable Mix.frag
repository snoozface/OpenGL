#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D textures[16];
uniform int numTextures;
uniform float mixAmount;


void main()
{
	vec4 blendedTexture = texture(textures[0], TexCoord);
	for (int i = 1; i < numTextures; ++i)
	{
		blendedTexture = mix(blendedTexture, texture(textures[i], TexCoord), mixAmount);
	}

	FragColor = blendedTexture;
}
