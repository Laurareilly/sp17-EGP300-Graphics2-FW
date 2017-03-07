/*
Vector3 by Laura Reilly

Certificate of Authenticity

I certify that this work is entirely my own.The assessor of this project may
reproduce this project and provide copies to other academic staff, and / or
communicate a copy of this project to a plagiarism - checking service, which
may retain a copy of the project on its database.
*/


#ifndef VECTOR3_H
#define VECTOR3_H

#ifdef __cplusplus
extern "C"
{
#endif	// __cplusplus


	struct Vector3
	{
		float x, y, z;
	};

	struct Vector3 add(struct Vector3* a, struct Vector3* b);
	struct Vector3 subtract(struct Vector3* a, struct Vector3* b);
	struct Vector3 multiply(float scalar, struct Vector3* inputVec);
	struct Vector3 cross(struct Vector3* a, struct Vector3* b);
	struct Vector3 lerp(struct Vector3* start, struct Vector3* end, float t);
	struct Vector3 normalize(struct Vector3* inputVec);

	float dot(struct Vector3* a, struct Vector3* b);
	float magnitude(struct Vector3* inputVec);
	float magnitudeSquared(struct Vector3* inputVec);
 
	void assignVector(struct Vector3* inputVec, float x, float y, float z);

#ifdef __cplusplus
}
#endif	// __cplusplus


#endif