/*
	Morphing
	By Dan Buckstein
	Vertex shader that performs morph target animation.
	
	Modified by: ______________________________________________________________
*/

#version 430

#define KEYFRAME_COUNT 4

// ****
// attributes: one per morphing attribute (e.g. multiple positions)
layout (location = 0) in vec4 position1;
layout (location = 1) in vec4 position2;
layout (location = 2) in vec4 position3;
layout (location = 3) in vec4 position4;

// ****
// uniforms: animation controls
uniform mat4 mvp;
uniform float param; //takes in anything between 0 and 1
uniform int index[KEYFRAME_COUNT];

// varying output: solid color
out vec4 passColor;

vec4 lerp(in vec4 p0, in vec4 p1, const float t)
{
	return p0 + (p1 - p0) * t;
}

vec4 catmullrom(in vec4 pPrev, in vec4 p0, in vec4 p1, in vec4 pNext, const float t)
{
	mat4 influenceMat = mat4(pPrev, p0, p1, pNext);

	mat4 mCR = mat4(0, -1, 2, -1,
					2, 0, -5, 3,
					0, 1, 4, -3,
					0, 0, -1, 1);

	mCR = transpose(mCR);

	mCR *= 0.5f;

	vec4 tVals = vec4(1, t, t * t, t * t * t);

	return influenceMat * mCR * tVals;
}

vec4 hermite(in vec4 p0, in vec4 m0, in vec4 p1, in vec4 m1, const float t)
{
	mat4 influenceMat = mat4(p0, m0, p1, m1);

	mat4 mH = mat4(1, 0, -3, 2,
				   0, 1, -2, 1,
				   0, 0, 3, -2,
				   0, 0, -1, 1);

	mH = transpose(mH);

	vec4 tVals = vec4(1, t, t * t, t * t * t);
	
	return influenceMat * mH * tVals;
}

void main()
{

	vec4 position;
	vec4 p[KEYFRAME_COUNT] = { position1, position2, position3, position4 };

	//position = lerp(p[index[0]], p[index[1]], param);
	position =  catmullrom(p[index[3]], p[index[0]], p[index[1]], p[index[2]], param);
	//position =  hermite(p[index[3]], p[index[0]], p[index[1]], p[index[2]], param);

	// ****
	// do morphing, transform the correct result before assigning to output
	gl_Position = mvp * position;

	// TESTING: send position as color to give us some variance
	passColor = position*0.5+0.5;
}