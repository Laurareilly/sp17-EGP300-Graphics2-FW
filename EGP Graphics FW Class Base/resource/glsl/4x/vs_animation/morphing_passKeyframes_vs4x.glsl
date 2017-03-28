/*
	Morphing - Pass Keyframes
	By Dan Buckstein
	Vertex shader that passes keyframes for morphing to geometry shader.
	
	Modified by: ______________________________________________________________
*/

#version 410


// ****
// attributes: one per morphing attribute (e.g. multiple positions)
layout (location = 0) in vec4 position1;
layout (location = 1) in vec4 position2;
layout (location = 2) in vec4 position3;
layout (location = 3) in vec4 position4;

// ****
// varying output: pass all attributes
out vertexdata
{
	vec4 position1;
	vec4 position2;
	vec4 position3;
	vec4 position4;
} pass;

void main()
{
	// ****
	// pass data along
	pass.position1 = position1;
	pass.position2 = position2;
	pass.position3 = position3;
	pass.position4 = position4;
}