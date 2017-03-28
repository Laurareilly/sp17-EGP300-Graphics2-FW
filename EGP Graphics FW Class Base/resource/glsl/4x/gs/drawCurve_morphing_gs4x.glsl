/*
	Draw Curve - Morphing
	By Dan Buckstein
	Geometry shader that draws the path that a morphing vertex follows.
	
	Modified by: ______________________________________________________________
*/

#version 410

// ****
#define SAMPLES_MAX 6

// geometry type layout qualifiers
layout (triangles) in;
layout (line_strip, max_vertices = 120) out;

// ****
// receive varying data
in vertexdata
{
	vec4 position1;
	vec4 position2;
	vec4 position3;
	vec4 position4;
} pass[];

// uniforms
uniform mat4 mvp;

// varying output: solid color
out vec4 passColor;


void drawLineFull(in vec4 p0, in vec4 p1)
{
	gl_Position = mvp * p0;
	EmitVertex();
	gl_Position = mvp * p1;
	EmitVertex();
	EndPrimitive();
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

void drawSegment(in vec4 pPrev, in vec4 p0, in vec4 p1, in vec4 pNext, const int samples, float dt)
{
	float t = 0.0;
	int i = 0;

	for(i = 0; i < samples; i++)
	{
		gl_Position = mvp * catmullrom(pPrev, p0, p1, pNext, t);
		EmitVertex();
		t += dt;
	}

	EndPrimitive();
}

void drawVertexCurve(const int samples, int i, float dt)
{
	drawSegment(pass[i].position1, pass[i].position2, pass[i].position3, pass[i].position4, samples, dt);
	drawSegment(pass[i].position2, pass[i].position3, pass[i].position4, pass[i].position1, samples, dt);
	drawSegment(pass[i].position3, pass[i].position4, pass[i].position1, pass[i].position2, samples, dt);
	drawSegment(pass[i].position4, pass[i].position1, pass[i].position2, pass[i].position3, samples, dt);
}


void main()
{
	// ****
	// do line drawing
	const int samplesPerSegment = SAMPLES_MAX;
	const float dt = 1.0 / float(samplesPerSegment);

	// testing: pass solid color
	passColor = vec4(0.0, 0.5, 1.0, 1.0);

	drawVertexCurve(samplesPerSegment, 0, dt);
	drawVertexCurve(samplesPerSegment, 1, dt);
	drawVertexCurve(samplesPerSegment, 2, dt);

}