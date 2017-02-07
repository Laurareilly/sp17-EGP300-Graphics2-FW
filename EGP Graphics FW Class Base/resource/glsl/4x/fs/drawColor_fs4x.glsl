/*
	Draw Color
	By Dan Buckstein
	Fragment shader that displays color received from previous piipeline stage.
	
	Modified by: Laura Reilly

*/
#version 410


 //****
 //varyings: data received from previous stage in the pipeline
 //same formats as vertex shader, with restrictions: 
	//-> for structure format, full structure layout must be identical
	//	-> replace 'out' with 'in':		in <structure name> { ...
	//-> for one-by-one format, variable type and name must be identical
in vertex
{
	vec4 color;
} data;


 //uniforms: same idea for all shader types
 //(none in this example)


 //****
 //target: fragment shader result to be stored in framebuffer
 //same format as attribute, but with 'out' instead of 'in': 
	//	layout (location = <target index>) out <type> <name>;
layout(location = 0) out vec4 color;


// shader entry point: function executes once per-fragment
void main()
{
	// ****
	// no required steps, but the goal is to assign a color to a target
	// this example: copy inbound color varying directly to framebuffer target
	//data.color = color;
	color = data.color;

}