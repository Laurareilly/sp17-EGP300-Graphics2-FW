// By Dan Buckstein
// Modified by: _______________________________________________________________
#include "egpfw/egpfw/egpfwInterpolation.h"


#include <math.h>


// ****
// lerp and lerp inverse
float egpfwLerp(const float v0, const float v1, const float param)
{
	return v0 + (v1 - v0) * param;
}

// ****
float egpfwLerpInv(const float v0, const float v1, const float v)
{
	return 0.0f;
}


// ****
// Catmull-Rom spline interpolation
float egpfwCatmullRom(const float vPrev, const float v0, const float v1, const float vNext, const float param)
{
	float t = param;
	float t2 = param * param;
	float t3 = param * param * param;

	float first = -t + 2 * t2 - t3;
	float second = 2 - 5 * t2 + 3 * t3;
	float third = t + 4 * t2 - 3 * t3;
	float fourth = -t2 + t3;

	return 0.5 * (vPrev * first + v0 * second + v1 * third + vNext * fourth);
}

// ****
// Cubic hermite spline interpolation
float egpfwCubicHermite(const float v0, const float dv0, const float v1, const float dv1, const float param)
{
	float t = param;
	float t2 = param * param;
	float t3 = param * param * param;

	float h00 = 1 - 3 * t2 + 2 * t3;
	float h10 = t - 2 * t2 + t3;
	float h01 = 3 * t2 - 2 * t3;
	float h11 = -t2 + t3;

	return h00 * v0 + h10 * dv0 + h01 * v1 + h11 * dv1;
}


// Bezier spline interpolation
float egpfwBezier0(const float v0, const float param)
{
	// this function is complete!
	return v0;
}

// ****
float egpfwBezier1(const float v0, const float v1, const float param)
{
	return (1 - param) * v0 + v1;
}

// ****
float egpfwBezier2(const float v0, const float v1, const float v2, const float param)
{
	return egpfwLerp(egpfwLerp(v0, v1, param), egpfwLerp(v1, v2, param), param);
}

// ****
float egpfwBezier3(const float v0, const float v1, const float v2, const float v3, const float param)
{
	return egpfwLerp(egpfwBezier2(v0, v1, v2, param), egpfwBezier2(v1, v2, v3, param), param);
}

// ****
float egpfwBezier4(const float v0, const float v1, const float v2, const float v3, const float v4, const float param)
{
	return egpfwLerp(egpfwBezier3(v0, v1, v2, v3, param), egpfwBezier3(v1, v2, v3, v4, param), param);
}

// ****
float egpfwBezier(const float *v, unsigned int order, const float param)
{
	//...
	return 0.0f;
}


// ****
// vector interpolation
void egpfwLerpVector(const float *v0, const float *v1, const float param, const unsigned int numElements, float *v_out)
{
	
}

// ****
void egpfwCatmullRomVector(const float *vPrev, const float *v0, const float *v1, const float *vNext, const float param, const unsigned int numElements, float *v_out)
{
	//...
}

// ****
void egpfwCubicHermiteVector(const float *v0, const float *dv0, const float *v1, const float *dv1, const float param, const unsigned int numElements, float *v_out)
{
	//...
}

// ****
void egpfwBezierVector(const float *v, unsigned int order, const float param, const unsigned int numElements, float *v_out)
{
	//...
}


// ****
// table sampling
unsigned int egpfwSearchSampleTable(const float *sampleTable, const float *paramTable, const float searchParam, unsigned int numElements, float *param_out)
{
	//...
	return 0;
}


// ****
// calculate arc length
float egpfwComputeArcLengthCatmullRom(const float *vPrev, const float *v0, const float *v1, const float *vNext, unsigned int numElements, unsigned int numSamples, int autoNormalize, float *prevSamplePtr, float *currentSamplePtr, float *sampleTable_out, float *paramTable_out)
{
	//...
	return 0.0f;
}

// ****
float egpfwComputeArcLengthCubicHermite(const float *v0, const float *dv0, const float *v1, const float *dv1, unsigned int numElements, unsigned int numSamples, int autoNormalize, float *prevSamplePtr, float *currentSamplePtr, float *sampleTable_out, float *paramTable_out)
{
	//...
	return 0.0f;
}

// ****
float egpfwComputeArcLengthBezier(const float *v, unsigned int order, unsigned int numElements, unsigned int numSamples, int autoNormalize, float *prevSamplePtr, float *currentSamplePtr, float *sampleTable_out, float *paramTable_out)
{
	//...
	return 0.0f;
}
