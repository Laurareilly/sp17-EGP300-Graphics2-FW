/*
	Skinning & Pass Normal as Color
	By Dan Buckstein
	Vertex shader that performs vertex skinning, passing resulting normal out
		as a solid color for debugging purposes.
	
	Modified by: ______________________________________________________________
*/

#version 410


// ****
// the usual attributes, but also need skinning attributes: 
// weights and bone indices
layout (location = 0) in vec4 position;
layout (location = 2) in vec4 normal;
layout (location = 1) in vec4 blendWeight;
layout (location = 7) in vec4 blendIndex;


uniform mat4 mvp;


#define BONES_MAX 64

// ****
// skinning uniforms
uniform mat4 bones_skinning[BONES_MAX];

// pass some piece of data along for debugging
out vec4 passColor;


// ****
// skinning algorithm: 
// vector goes indeformed vector comes out
vec4 skin(in vec4 v)
{
	vec4 v_out = vec4(0.0);

	vec4 weights1 = blendWeight.x * (bones_skinning[int(blendIndex.x)] * v);
	vec4 weights2 = blendWeight.y * (bones_skinning[int(blendIndex.y)] * v);
	vec4 weights3 = blendWeight.z * (bones_skinning[int(blendIndex.z)] * v);
	vec4 weights4 = blendWeight.w * (bones_skinning[int(blendIndex.w)] * v);

	v_out += weights1;
	v_out += weights2;
	v_out += weights3;
	v_out += weights4;

	return v_out;
}


void main()
{
	// ****
	// skin any attribute that has to do with the SURFACE
	// i.e. anything that could potentially affect shading
	gl_Position = mvp * skin(position);

	passColor = skin(vec4(normal.xyz, 0)) * 0.5f + 0.5f;
}