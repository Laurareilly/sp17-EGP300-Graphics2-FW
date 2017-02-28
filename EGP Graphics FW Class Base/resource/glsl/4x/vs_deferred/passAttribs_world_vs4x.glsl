/*
	Pass Attributes World
	By Dan Buckstein
	Vertex shader that passes attributes in world space.
	
	Modified by: Laura Reilly
*/

// version
#version 410


// ****
// attributes
layout (location = 0) in vec4 position;
layout (location = 2) in vec4 normal;
layout (location = 8) in vec4 texcoord;


// ****
// uniforms
uniform mat4 modelMat;
uniform mat4 viewprojMat;
uniform mat4 atlasMat;
uniform float normalScale;

//****
//varyings
out vertexdata
{
	vec4 position_world;
	vec4 normal_world;
	vec4 texcoord_atlas;
} pass;


// shader function
void main()
{
	// ****
	// set proper clip position
	vec4 worldPos = modelMat * position; //transforming camera matrix, all lighting in terms of world position
	pass.position_world = worldPos;
	pass.normal_world = modelMat * vec4(normal.xyz * normalScale, 0.0); //this preserves the normals of the geometry- undo the scale of the normal for the scale we give to it's geometry
	pass.texcoord_atlas = atlasMat * texcoord;

	gl_Position = viewprojMat * worldPos;
}