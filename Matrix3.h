#ifndef Matrix3_H
#define Matrix3_H
#include <cmath>
#include <iostream>
#include "Vector2.h"

class Matrix3
{
public:
	float mat[3][3];

	Matrix3()
	{
		mat[0][0] = 1; mat[0][1] = 0; mat[0][2] = 0;
		mat[1][0] = 0; mat[1][1] = 1; mat[1][2] = 0;
		mat[2][0] = 0; mat[2][1] = 0; mat[2][2] = 1;
	}

	explicit Matrix3(float inMat[3][3])
	{
		memcpy(mat, inMat, 9 * sizeof(float));
	}


	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&mat[0][0]);
	}


	friend Matrix3 operator*(const Matrix3& left, const Matrix3& right)
	{
		Matrix3 retVal;

		retVal.mat[0][0] =
			left.mat[0][0] * right.mat[0][0] +
			left.mat[0][1] * right.mat[1][0] +
			left.mat[0][2] * right.mat[2][0];

		retVal.mat[0][1] =
			left.mat[0][0] * right.mat[0][1] +
			left.mat[0][1] * right.mat[1][1] +
			left.mat[0][2] * right.mat[2][1];

		retVal.mat[0][2] =
			left.mat[0][0] * right.mat[0][2] +
			left.mat[0][1] * right.mat[1][2] +
			left.mat[0][2] * right.mat[2][2];

	
		retVal.mat[1][0] =
			left.mat[1][0] * right.mat[0][0] +
			left.mat[1][1] * right.mat[1][0] +
			left.mat[1][2] * right.mat[2][0];

		retVal.mat[1][1] =
			left.mat[1][0] * right.mat[0][1] +
			left.mat[1][1] * right.mat[1][1] +
			left.mat[1][2] * right.mat[2][1];

		retVal.mat[1][2] =
			left.mat[1][0] * right.mat[0][2] +
			left.mat[1][1] * right.mat[1][2] +
			left.mat[1][2] * right.mat[2][2];


		retVal.mat[2][0] =
			left.mat[2][0] * right.mat[0][0] +
			left.mat[2][1] * right.mat[1][0] +
			left.mat[2][2] * right.mat[2][0];

		retVal.mat[2][1] =
			left.mat[2][0] * right.mat[0][1] +
			left.mat[2][1] * right.mat[1][1] +
			left.mat[2][2] * right.mat[2][1];

		retVal.mat[2][2] =
			left.mat[2][0] * right.mat[0][2] +
			left.mat[2][1] * right.mat[1][2] +
			left.mat[2][2] * right.mat[2][2];

		return retVal;
	}



	friend std::ostream& operator<<(std::ostream& stream, const Matrix3& m) {
		return stream << "(" << m.mat[0][0] << " " << m.mat[1][0] << " " << m.mat[2][0] << ")" << "\n"
			<< "(" << m.mat[0][1] << " " << m.mat[1][1] << " " << m.mat[2][1] << ")" << "\n"
		<< "(" << m.mat[0][2] << " " << m.mat[1][2] << " " << m.mat[2][2] << ")";
	}

};

float m3Ident[3][3] =
{
	{ 1.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f }
};

const Matrix3 Identity3(m3Ident);


Matrix3 CreateScale(float xScale, float yScale)
{
	float temp[3][3] =
	{
		{ xScale, 0.0f, 0.0f },
		{ 0.0f, yScale, 0.0f },
		{ 0.0f, 0.0f, 1.0f },
	};
	return Matrix3(temp);
}

Matrix3 CreateScale(const Vector2& scaleVector)
{
	return CreateScale(scaleVector.x, scaleVector.y);
}

Matrix3 CreateScale(float scale)
{
	return CreateScale(scale, scale);
}

Matrix3 CreateRotation(float theta)
{
	float temp[3][3] =
	{
		{ Math::Cos(theta), Math::Sin(theta), 0.0f },
		{ -Math::Sin(theta), Math::Cos(theta), 0.0f },
		{ 0.0f, 0.0f, 1.0f },
	};
	return Matrix3(temp);
}

Matrix3 CreateTranslation(const Vector2& trans)
{
	float temp[3][3] =
	{
		{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ trans.x, trans.y, 1.0f },
	};
	return Matrix3(temp);
}

Vector2 Transform(const Vector2& vec, const Matrix3& mat, float w = 1.0f )
{
	Vector2 retVal;
	retVal.x = vec.x * mat.mat[0][0] + vec.y * mat.mat[1][0] + w * mat.mat[2][0];
	retVal.y = vec.x * mat.mat[0][1] + vec.y * mat.mat[1][1] + w * mat.mat[2][1];
	return retVal;
}

#endif