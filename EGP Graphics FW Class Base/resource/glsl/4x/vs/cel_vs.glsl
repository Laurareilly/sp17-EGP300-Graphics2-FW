/*
	Cel vertex
	By Laura Reilly
	Vertex shader for cel shading
*/

#version 410


// attributes
layout (location = 0) in vec4 position;
layout (location = 2) in vec4 normal;
layout (location = 8) in vec4 texcoord;


// uniforms
uniform mat4 mvp;
uniform vec4 lightPos;
uniform vec4 eyePos;


// varyings
out vertex
{
	vec4 normal;
	vec4 lightVec;
	vec4 eyeVec;
	vec2 texcoord;
} data;


void main()
{
	//this is actually the same as phong-- might try to use phongs vs instead of
	//creating this but its too late oops
	gl_Position = mvp * position;

	// pass data to the fragment shader
	data.eyeVec = eyePos - position;
	data.normal = vec4(normal.xyz, 0.0);
	data.lightVec = lightPos - position;
	data.texcoord = texcoord.xy;
}