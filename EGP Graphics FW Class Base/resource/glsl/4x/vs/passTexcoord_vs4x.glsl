/*
	Pass Texcoord
	By Dan Buckstein
	Vertex shader that passes texcoord attribute down pipeline.
	
	Modified by: Laura Reilly
*/

// version
#version 410


// ****
// attributes
layout(location = 0) in vec4 position;
layout(location = 8) in vec4 texcoord;

// ****
// uniforms
uniform mat4 mvp;

// ****
// varyings
out vertex
{
	vec2 texcoord; //so that the fragment can look in where the texture it wants to sample that color from
} data;

// shader function
void main()
{
	// ****
	// set proper clip position
	gl_Position = mvp * position;
	// ****
	// pass data
	data.texcoord = texcoord.xy;
}