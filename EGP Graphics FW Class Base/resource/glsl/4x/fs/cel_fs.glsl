/*
	Cel fs
	By Laura Reilly
	Fragment shader for cel shading
*/

#version 410

//varyings
in vertex
{
	vec4 normal;
	vec4 lightVec;
	vec4 eyeVec;
	vec2 texcoord;
} data;

//uniforms
uniform sampler2D tex_dm;

//target
layout (location = 0) out vec4 fragColor;


// shader function
void main()
{
	fragColor = texture(tex_dm, passTexcoord);
}

