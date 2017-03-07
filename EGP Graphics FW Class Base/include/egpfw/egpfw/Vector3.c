#include "Vector3.h"
#include <math.h>

//adds two given vectors
struct Vector3 add(struct Vector3* a, struct Vector3* b)
{
	struct Vector3 newVector;
	assignVector(&newVector, a->x + b->x, a->y + b->y, a->z + b->z);
	return newVector;
}

//subtracts two given vectors
struct Vector3 subtract(struct Vector3* a, struct Vector3* b)
{
	struct Vector3 newVector;
	assignVector(&newVector, a->x - b->x, a->y - b->y, a->z - b->z);
	return newVector;
}

//multiplies two given vectors
struct Vector3 multiply(float scalar, struct Vector3* inputVec)
{
	struct Vector3 newVector;
	assignVector(&newVector, inputVec->x * scalar, inputVec->y * scalar, inputVec->z * scalar);
	return newVector;
}

//x = yzzy
struct Vector3 cross(struct Vector3* a, struct Vector3* b)
{
	struct Vector3 newVector;
	assignVector(&newVector, a->y * b->z - a->z * b->y,
							 a->z * b->x - a->x * b->z,
							 a->x * b->y - a->y - b->x);
	return newVector;
}

//lerp
struct Vector3 lerp(struct Vector3* start, struct Vector3* end, float t)
{
	struct Vector3 newVector;

	//clamp
	if (t < 0.0f)
	{
		t = 0.0f;
	}
	if (t > 1.0f)
	{
		t = 0.0f;
	}

	assignVector(&newVector, 
				 start->x * (1.0f - t) + end->x * t,
				 start->y * (1.0f - t) + end->y * t,
				 start->z * (1.0f - t) + end->z * t);
	return newVector;
}

//returns the dot product of two given vectors
float dot(struct Vector3* a, struct Vector3* b)
{
	return (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
}

//returns magnitude (length) of a given vector
float magnitude(struct Vector3* inputVec)
{
	return sqrt(magnitudeSquared(inputVec));
}

//returns squared magnitude of a given vector (just dotted with itself)
float magnitudeSquared(struct Vector3* inputVec)
{
	return dot(inputVec, inputVec);
}

//assigns values of a given vector so that we can return them in above functions
void assignVector(struct Vector3* inputVec, float x, float y, float z)
{
	inputVec->x = x;
	inputVec->y = y;
	inputVec->z = z;
}

struct Vector3 normalize(struct Vector3* inputVec)
{
	struct Vector3 newVector;

	assignVector(&newVector, inputVec->x, inputVec->y, inputVec->z);

	if (magnitudeSquared(&newVector) == 1.0f) //already normalized
	{
		return newVector;
	}

	return multiply(1.0 / magnitude(&newVector), &newVector);
}
