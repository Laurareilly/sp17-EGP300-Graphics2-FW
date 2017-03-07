#include "3x3Matrix.h"
#include "4x4Transformation.h"

//i definitely need review on this
struct Transform4x4 inverse4x4(Transform4x4* inputMat)
{
	struct Transform4x4 tempMat4x4;
	struct Mat3x3 tempMat3x3;

	makeIdentity4x4(&tempMat4x4);

	tempMat3x3 = getRotationFromTransformation(inputMat);

	struct Mat3x3 inverse3x3;
	inverse3x3 = inverse(&tempMat3x3);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{		
			tempMat4x4.matrixElements[i][j] = inverse3x3.matrixElements[j][i];
		}
	}

	struct Vector3 tempVec;
	tempVec.x = inputMat->matrixElements[0][3];
	tempVec.x = inputMat->matrixElements[1][3];
	tempVec.x = inputMat->matrixElements[2][3];

	tempVec = multiply3DVector(&tempVec, &inverse3x3);

	tempVec.x *= -1;
	tempVec.y *= -1;
	tempVec.z *= -1;

	tempMat4x4.matrixElements[0][3] = tempVec.x;
	tempMat4x4.matrixElements[1][3] = tempVec.y;
	tempMat4x4.matrixElements[2][3] = tempVec.z;

	return tempMat4x4;
}

struct Mat3x3 getRotationFromTransformation(Transform4x4* inputMat)
{
	struct Mat3x3 tempMat;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tempMat.matrixElements[i][j] = inputMat->matrixElements[i][j];
		}
	}

	return tempMat;
}

struct Vector3 multiply3DVector4x4(struct Vector3* inputVector, Transform4x4* inputMatrix)
{
	struct Vector3 tempVec;

	tempVec.x = inputMatrix->matrixElements[0][0] * inputVector->x + inputMatrix->matrixElements[0][1] * inputVector->y + inputMatrix->matrixElements[0][2] * inputVector->z + inputMatrix->matrixElements[0][3];
	tempVec.y = inputMatrix->matrixElements[1][0] * inputVector->x + inputMatrix->matrixElements[1][1] * inputVector->y + inputMatrix->matrixElements[1][2] * inputVector->z + inputMatrix->matrixElements[1][3];
	tempVec.z = inputMatrix->matrixElements[2][0] * inputVector->x + inputMatrix->matrixElements[2][1] * inputVector->y + inputMatrix->matrixElements[2][2] * inputVector->z + inputMatrix->matrixElements[2][3];

	return tempVec;
}

//dot product of the first row of a and first column of b, then move to the next and do the same
//james helped me with this one
struct Transform4x4 concatenate4x4(Transform4x4* a, Transform4x4* b)
{
	struct Transform4x4 tempMat;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tempMat.matrixElements[i][j] =
				a->matrixElements[i][0] * b->matrixElements[0][j] +
				a->matrixElements[i][1] * b->matrixElements[1][j] +
				a->matrixElements[i][2] * b->matrixElements[2][j] +
				a->matrixElements[i][3] * b->matrixElements[3][j];
		}
	}

	return tempMat;
}

void makeTransformFromRotation(struct Mat3x3* inputMat, float x, float y, float z)
{
	struct Transform4x4 tempMat;

	makeIdentity4x4(&tempMat); //this fills in the entire bottom row for us


	for (int i = 0; i < 3; i++) //turn the top left of the 4x4 into the inputMat
	{
		for (int j = 0; j < 3; j++)
		{
			tempMat.matrixElements[i][j] = inputMat->matrixElements[i][j];
		}
	}

	//turn the top right into our x, y, and z input
	tempMat.matrixElements[0][3] = x;
	tempMat.matrixElements[1][3] = y;
	tempMat.matrixElements[2][3] = z;
}

void makeTransformFromTranslation(Transform4x4* inputMat, float x, float y, float z)
{
	makeIdentity4x4(inputMat);
	//the fourth column is going to be our x, y, z values
	inputMat->matrixElements[0][3] = x;
	inputMat->matrixElements[1][3] = y;
	inputMat->matrixElements[2][3] = z;
	//we don't need the fourth row because that's just going to be 1
}

void makeTransformFromUniformScale(Transform4x4* inputMat, float scale)
{
	makeIdentity4x4(inputMat);
	inputMat->matrixElements[0][0] = scale;
	inputMat->matrixElements[1][1] = scale;
	inputMat->matrixElements[2][2] = scale;
	inputMat->matrixElements[3][3] = scale;
}

void makeIdentity4x4(Transform4x4* matrix)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matrix->matrixElements[i][j] = 0.0f;
		}
	}

	matrix->matrixElements[0][0] = 1.0f;
	matrix->matrixElements[1][1] = 1.0f;
	matrix->matrixElements[2][2] = 1.0f;
	matrix->matrixElements[3][3] = 1.0f;
}

Transform4x4 & Transform4x4::operator*(Transform4x4 & other)
{
	return concatenate4x4(this, &other);
}
