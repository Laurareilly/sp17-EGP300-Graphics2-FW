#include "3x3Matrix.h"
#include <math.h>


struct Mat3x3 transpose(struct Mat3x3* inputMatrix)
{
	struct Mat3x3 tempMat;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tempMat.matrixElements[i][j] = inputMatrix->matrixElements[j][i];
		}
	}
	return tempMat;
}

//since we're assuming it's a rotation matrix, inverse = transpose
struct Mat3x3 inverse(struct Mat3x3* inputMatrix)
{
	return transpose(inputMatrix);
}

void  makeIdentity(struct Mat3x3* inputMatrix)
{

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//zero out everything, put the diagonal 1's in later
			inputMatrix->matrixElements[i][j] = 0.0f;
		}
	}

	inputMatrix->matrixElements[0][0] = 1.0f;
	inputMatrix->matrixElements[1][1] = 1.0f;
	inputMatrix->matrixElements[2][2] = 1.0f;
}

struct Mat3x3 makeRotX(float radians)
{
	//this starts out pretty similar to identity matrix, so we can start with one
	struct Mat3x3 tempMat;
	makeIdentity(&tempMat);

	tempMat.matrixElements[1][1] = cos(radians);
	tempMat.matrixElements[1][2] = -sin(radians);
	tempMat.matrixElements[2][1] = sin(radians);
	tempMat.matrixElements[2][2] = cos(radians);

	return tempMat;
}

Mat3x3 makeRotY(float radians)
{
	struct Mat3x3 tempMat;
	makeIdentity(&tempMat);

	tempMat.matrixElements[0][0] = cos(radians);
	tempMat.matrixElements[0][2] = sin(radians);
	tempMat.matrixElements[2][0] = -sin(radians);
	tempMat.matrixElements[2][2] = cos(radians);

	return tempMat;
}

Mat3x3 makeRotZ(float radians)
{
	struct Mat3x3 tempMat;
	makeIdentity(&tempMat);

	tempMat.matrixElements[0][0] = cos(radians);
	tempMat.matrixElements[0][1] = -sin(radians);
	tempMat.matrixElements[1][0] = sin(radians);
	tempMat.matrixElements[1][1] = cos(radians);

	return tempMat;
}

//this is something i'd like review on if we have time at some point
struct Vector3 makeEulerXYZ(struct Vector3* inputVector, float x, float y, float z)
{
	struct Mat3x3 xMat = makeRotX(x);
	struct Mat3x3 yMat = makeRotX(y);
	struct Mat3x3 zMat = makeRotX(z);

	struct Mat3x3 yzMat = concatenate(&yMat, &zMat);
	struct Mat3x3 finalMat = concatenate(&xMat, &yzMat);
	
	struct Vector3 vec = multiply3DVector(inputVector, &finalMat);

	return vec;
}

//this is something i'd like review on if we have time at some point
struct Vector3 makeEulerZYX(struct Vector3* inputVector, float x, float y, float z)
{
	struct Mat3x3 xMat = makeRotX(x);
	struct Mat3x3 yMat = makeRotX(y);
	struct Mat3x3 zMat = makeRotX(z);

	struct Mat3x3 yxMat = concatenate(&yMat, &xMat);
	struct Mat3x3 finalMat = concatenate(&zMat, &yxMat);

	struct Vector3 vec = multiply3DVector(inputVector, &finalMat);

	return vec;
}

struct Vector3 multiply3DVector(struct Vector3* inputVector, struct Mat3x3* inputMatrix)
{
	struct Vector3 tempVec;

	tempVec.x = inputMatrix->matrixElements[0][0] * inputVector->x + inputMatrix->matrixElements[0][1] * inputVector->y + inputMatrix->matrixElements[0][2] * inputVector->z;
	tempVec.y = inputMatrix->matrixElements[1][0] * inputVector->x + inputMatrix->matrixElements[1][1] * inputVector->y + inputMatrix->matrixElements[1][2] * inputVector->z;
	tempVec.z = inputMatrix->matrixElements[2][0] * inputVector->x + inputMatrix->matrixElements[2][1] * inputVector->y + inputMatrix->matrixElements[2][2] * inputVector->z;

	return tempVec;
}

Mat3x3 makeUniformScale(float scale)
{
	struct Mat3x3 tempMat;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tempMat.matrixElements[i][j] = 0.0f;
		}
	}

	//the scale goes down the diagonal, so we only want to change those elements
	for (int i = 0; i < 3; i++)
	{
		tempMat.matrixElements[i][i] = scale;
	}

	return tempMat;
}

//dot product of the first row of a and first column of b, then move to the next and do the same
//james helped me with this one
Mat3x3 concatenate(Mat3x3* a, Mat3x3* b)
{
	struct Mat3x3 tempMat;
	for (char i = 0; i < 3; i++)
	{
		for (char j = 0; j < 3; j++)
		{
			tempMat.matrixElements[i][j] =
				a->matrixElements[i][0] * b->matrixElements[0][j] +
				a->matrixElements[i][1] * b->matrixElements[1][j] +
				a->matrixElements[i][2] * b->matrixElements[2][j];
		}
	}
	return tempMat;
}

Mat3x3 & Mat3x3::operator*(Mat3x3 & other)
{
	return concatenate(this, &other);
}
