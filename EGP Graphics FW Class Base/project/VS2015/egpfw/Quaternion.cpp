#include "Quaternion.h"
#include <math.h>

Quaternion::Quaternion()
{
	x = 0;
	y = 0;
	z = 0;
	w = 1;
}

Quaternion::Quaternion(float newX, float newY, float newZ, float newW)
{
	x = newX;
	y = newY;
	z = newZ;
	w = newW;
}

Quaternion::Quaternion(float aVal, Vector3* aVec)
{
	struct Vector3 normalizedVector = normalize(aVec);
	normalizedVector = multiply(sin(aVal), &normalizedVector);

	x = aVec->x;
	y = aVec->y;
	z = aVec->z;

	w = cos(aVal);
}

Quaternion makeIdentity()
{
	Quaternion tempQuat = Quaternion();

	return tempQuat;
}

Quaternion makeInverse(Quaternion* aQuat)
{
	//https://www.3dgep.com/understanding-quaternions/
	float magnitude = getMagnitude(aQuat);

	return Quaternion(
				aQuat->x / magnitude,
		-1.0f * aQuat->y / magnitude,
		-1.0f * aQuat->z / magnitude,
		-1.0f * aQuat->w / magnitude);
}

Quaternion lerp(const Quaternion* aQuatStart, const Quaternion* aQuatEnd, float aValue)
{
	//based lerp and slerp off http://willperone.net/Code/quaternion.php

	Quaternion scaledStart = multiplyByScale(aQuatStart, (1.0f - aValue));
	Quaternion scaledEnd = multiplyByScale(aQuatEnd, aValue);
	Quaternion sum = add(&scaledStart, &scaledEnd);

	normalize(&sum);

	return sum;
}

Quaternion slerp(Quaternion* aQuatStart, Quaternion* aQuatEnd, float aValue)
{
	Quaternion tempQuat;
	float dotProd = dot(aQuatStart, aQuatEnd);
	if (dotProd < 0)
	{
		dotProd = -1.0f * dotProd;
		tempQuat = makeInverse(aQuatEnd);
	}
	else
	{
		tempQuat = *aQuatEnd;
	}
	//clamp(dotProd, -1.0, 1.0); //DOES THIS WORK
	float theta = acos(dotProd);


	Quaternion product = multiplyByScale(aQuatEnd, sinf(theta * (1.0f - aValue)));
	Quaternion otherProduct = multiplyByScale(&tempQuat, sinf(theta * aValue) / sinf(theta));
	Quaternion sum = add(&product, &otherProduct);

	return sum;
}

Quaternion add(Quaternion* aQuat1, Quaternion* aQuat2)
{
	return Quaternion(
		aQuat1->x + aQuat2->x,
		aQuat1->y + aQuat2->y,
		aQuat1->z + aQuat2->z,
		aQuat1->w + aQuat2->w);
}

Quaternion subtract(Quaternion* aQuat1, Quaternion* aQuat2)
{
	return Quaternion(
		aQuat1->x - aQuat2->x,
		aQuat1->y - aQuat2->y,
		aQuat1->z - aQuat2->z,
		aQuat1->w - aQuat2->w);
}

Quaternion multiplyByScale(const Quaternion* aQuat, float aScale)
{
	return Quaternion(
		aQuat->x * aScale,
		aQuat->y * aScale,
		aQuat->z * aScale,
		aQuat->w * aScale);
}

//come back to this
Quaternion concatenate(Quaternion* aQuat1, Quaternion* aQuat2)
{
	//http://physicsforgames.blogspot.ca/2010/02/quaternions.html 
	Quaternion result;

	result.w = aQuat1->w * aQuat2->w - aQuat1->x * aQuat2->x - aQuat1->y * aQuat2->y - aQuat1->z - aQuat2->z;
	result.x = aQuat1->w * aQuat2->x + aQuat1->x * aQuat2->w + aQuat1->y * aQuat2->z - aQuat1->z * aQuat2->y;
	result.y = aQuat1->w * aQuat2->y + aQuat1->y * aQuat2->w + aQuat1->x * aQuat2->z - aQuat1->z * aQuat2->x;
	result.z = aQuat1->w * aQuat2->z + aQuat1->z * aQuat2->w + aQuat1->x * aQuat2->y - aQuat1->y * aQuat2->x;

	return result;
}

Quaternion makeRotX(float x)
{
	struct Vector3 rightVec;
	assignVector(&rightVec, 1, 0, 0);
	return Quaternion(x, &rightVec);
}

Quaternion makeRotY(float y)
{
	struct Vector3 forwardVec;
	assignVector(&forwardVec, 0, 1, 0);
	return Quaternion(y, &forwardVec);
}

Quaternion makeRotZ(float z)
{
	struct Vector3 upVec;
	assignVector(&upVec, 0, 1, 0);
	return Quaternion(z, &upVec);
}

//come back to this
Quaternion makeRotZYX(float x, float y, float z)
{
	//I asked james for help and he pointed me to this link and I would love if
	//we could do some sort of review on this! I can't get it into my brain to even
	//begin to draw this out or something
	//https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
	double yawCos = cos(x / 2.0f);		
	double yawSin = sin(x / 2.0f);
	double pitchCos = cos(y / 2.0f);
	double pitchSin = sin(y / 2.0f);
	double rollCos = cos(z / 2.0f);
	double rollSin = sin(z / 2.0f);

	double endX = yawCos * pitchSin * rollCos - yawSin * pitchCos * rollSin;
	double endY = yawCos * pitchCos * rollSin + yawSin * pitchSin * rollCos;
	double endZ = yawSin * pitchCos * rollCos - yawCos * pitchSin * rollSin;
	double endW = yawCos * pitchCos * rollCos + yawSin * pitchSin * rollSin;

	return Quaternion(endX, endY, endZ, endW);
}

Quaternion makeRotXYZ(float x, float y, float z)
{
	Quaternion xy = concatenate(&makeRotX(x), &makeRotY(y));
	return concatenate(&xy, &makeRotZ(z));
}

Transform4x4 convertToMatrix(Quaternion* aQuat)
{
	//http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/

	Transform4x4 convertedMat;
	normalize(aQuat);

	convertedMat.matrixElements[0][0] = 1 - 2 * aQuat->y * aQuat->y - 2 * aQuat->z * aQuat->z;
	convertedMat.matrixElements[0][1] = 2 * aQuat->x * aQuat->y - 2 * aQuat->z * aQuat->w;
	convertedMat.matrixElements[0][2] = 2 * aQuat->x * aQuat->z + 2 * aQuat->y * aQuat->w;

	convertedMat.matrixElements[1][0] = 2 * aQuat->x * aQuat->y + 2 * aQuat->z * aQuat->w;
	convertedMat.matrixElements[1][1] = 1 - 2 * aQuat->x * aQuat->x - 2 * aQuat->z * aQuat->z;
	convertedMat.matrixElements[1][2] = 2 * aQuat->y * aQuat->z - 2 * aQuat->x * aQuat->w;

	convertedMat.matrixElements[2][0] = 2 * aQuat->x * aQuat->z - 2 * aQuat->y * aQuat->w;
	convertedMat.matrixElements[2][1] = 2 * aQuat->y * aQuat->z + 2 * aQuat->x * aQuat->w;
	convertedMat.matrixElements[2][2] = 1 - 2 * aQuat->x * aQuat->x - 2 * aQuat->y * aQuat->y;

	return convertedMat;
}

struct Vector3 multiply3DVector(Quaternion* aQuat, struct Vector3* aInputVec)
{
	//http://gamedev.stackexchange.com/questions/28395/rotating-vector3-by-a-quaternion
	Vector3 result;
	assignVector(&result, aQuat->x, aQuat->y, aQuat->z);

	//because I didn't do this in c++ :) :) :)
	float dotUV = 2.0 * dot(&result, aInputVec);
	Vector3 multipliedDotUV  = multiply(dotUV, &result);

	float dotUU = (aQuat->w * aQuat->w) - dot(&result, &result);
	Vector3 multipliedDotUU = multiply(dotUU, aInputVec);

	Vector3 crossUV = multiply(2.0 * aQuat->w, &cross(&result, aInputVec));

	//NOW ADD THE STEPS
	Vector3 UVdots = add(&multipliedDotUV, &multipliedDotUU);
	return add(&UVdots, &crossUV);
}

double clamp(double x, double aUpper, double aLower)
{
	return fmin(aUpper, fmax(x, aLower));
}

void normalize(Quaternion* aQuat)
{
	float magnitude = getMagnitude(aQuat);

	aQuat->x /= magnitude;
	aQuat->y /= magnitude;
	aQuat->z /= magnitude;
	aQuat->w /= magnitude;
}

float getMagnitude(Quaternion* aQuat)
{
	return sqrt(dot(aQuat, aQuat));
}

float getMagnitudeSqr(Quaternion* aQuat)
{
	return dot(aQuat, aQuat);
}

float dot(const Quaternion* aQuat1, const Quaternion* aQuat2)
{
	//pretty much the same as a vector, just with the added w

	return aQuat1->x * aQuat2->x +
		   aQuat1->y * aQuat2->y +
		   aQuat1->z * aQuat2->z +
		   aQuat1->w * aQuat2->w;
}


