/*
	Bright Pass
	By Dan Buckstein
	Fragment shader that leaves bright pixels bright and makes dark darker.
	
	Modified by: ______________________________________________________________
*/

// version
#version 410


// varyings
in vec2 passTexcoord;


// uniforms
uniform sampler2D img;


// target
layout (location = 0) out vec4 fragColor;


// shader function
void main()
{
	// ****
	// output: make bright values brighter, make dark values darker

	vec4 imgSample = texture(img, passTexcoord);
	float luminance = 0.2126 * imgSample.r + 0.7152 * imgSample.g + 0.0722 * imgSample.b; //for greyscale weighted average
	//everythign that's dark stays dark, preserving light, so everything beneath a certain range stays 0
	luminance *= luminance;
	luminance *= luminance;
	luminance *= luminance;
	luminance *= luminance;
	fragColor = imgSample * luminance;
	//fragColor = vec4(luminance);
	//fragColor = texture(img, passTexcoord);
}