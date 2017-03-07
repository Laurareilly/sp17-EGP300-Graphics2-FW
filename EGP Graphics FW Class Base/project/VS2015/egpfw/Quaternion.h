/*
Quaternion by Laura Reilly

Certificate of Authenticity

I certify that this work is entirely my own.The assessor of this project may
reproduce this project and provide copies to other academic staff, and / or
communicate a copy of this project to a plagiarism - checking service, which
may retain a copy of the project on its database.
*/

#pragma once
#include "egpfw/egpfw/Vector3.h"
#include "4x4Transformation.h"

struct Quaternion
{
	float x, y, z, w;

	Quaternion();
	Quaternion(float newX, float newY, float newZ, float newW);
	Quaternion(float aVal, struct Vector3* aVec);
};

Quaternion makeIdentity();
Quaternion makeInverse(Quaternion* aQuat);

Quaternion lerp(const Quaternion* aQuatStart, const Quaternion* aQuatEnd, float aValue);
Quaternion slerp(Quaternion* aQuatStart, Quaternion* aQuatEnd, float aValue);

Quaternion add(Quaternion* aQuat1, Quaternion* aQuat2);
Quaternion subtract(Quaternion* aQuat1, Quaternion* aQuat2);
Quaternion multiplyByScale(const Quaternion* aQuat, float aScale);
Quaternion concatenate(Quaternion* aQuat1, Quaternion* aQuat2);

Quaternion makeRotX(float x);
Quaternion makeRotY(float y);
Quaternion makeRotZ(float z);
Quaternion makeRotZYX(float x, float y, float z);
Quaternion makeRotXYZ(float x, float y, float z);

Transform4x4 convertToMatrix(Quaternion* aQuat);
struct Vector3 multiply3DVector(Quaternion* aQuat, struct Vector3* aInputVec);

void normalize(Quaternion* aQuat);
float getMagnitude(Quaternion* aQuat);
float getMagnitudeSqr(Quaternion* aQuat);
float dot(const Quaternion* aQuat1, const Quaternion* aQuat2);
double clamp(double x, double aUpper, double aLower);


