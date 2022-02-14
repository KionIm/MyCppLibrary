#ifndef QUATERNION_H
#define QUATERNION_H
#include <cmath>
#include <iostream>
#include "Matrix4.h"

class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

	Quaternion()
	{
		x = 0.0; y = 0.0; z = 0.0; w = 1.0;
	}

	explicit Quaternion(float inX, float inY, float inZ, float inW)
	{
		Set(inX, inY, inZ, inW);
	}

	explicit Quaternion(const Vector3& axis, float angle)
	{
		float scalar = Math::Sin(angle / 2.0f);
		x = axis.x * scalar;
		y = axis.y * scalar;
		z = axis.z * scalar;
		w = Math::Cos(angle / 2.0f);
	}

	void Set(float inX, float inY, float inZ, float inW)
	{
		x = inX;
		y = inY;
		z = inZ;
		w = inW;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Quaternion& q) {
		return stream << "(" << q.x << ", " << q.y << ", " << q.z << " " << q.w << ")";
	}

	void Conjugate()
	{
		x *= -1.0f;
		y *= -1.0f;
		z *= -1.0f;
	}

	float LengthSq() const
	{
		return (x * x + y * y + z * z + w * w);
	}

	float Length() const
	{
		return Math::Sqrt(LengthSq());
	}

	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}

	static Quaternion Normalize(const Quaternion& q)
	{
		Quaternion retVal = q;
		retVal.Normalize();
		return retVal;
	}

};

const Quaternion IdentityQ(0.0f, 0.0f, 0.0f, 1.0f);

Quaternion Lerp(const Quaternion& a, const Quaternion& b, float f)
{
	Quaternion retVal;
	retVal.x = Math::Lerp(a.x, b.x, f);
	retVal.y = Math::Lerp(a.y, b.y, f);
	retVal.z = Math::Lerp(a.z, b.z, f);
	retVal.w = Math::Lerp(a.w, b.w, f);
	retVal.Normalize();
	return retVal;
}

float Dot(const Quaternion& a, const Quaternion& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}


Quaternion Slerp(const Quaternion& a, const Quaternion& b, float f)
{
	float rawCosm = Dot(a, b);

	float cosom = -rawCosm;
	if (rawCosm >= 0.0f)
	{
		cosom = rawCosm;
	}

	float scale0, scale1;

	if (cosom < 0.9999f)
	{
		const float omega = Math::Acos(cosom);
		const float invSin = 1.f / Math::Sin(omega);
		scale0 = Math::Sin((1.f - f) * omega) * invSin;
		scale1 = Math::Sin(f * omega) * invSin;
	}
	else
	{

		scale0 = 1.0f - f;
		scale1 = f;
	}

	if (rawCosm < 0.0f)
	{
		scale1 = -scale1;
	}

	Quaternion retVal;
	retVal.x = scale0 * a.x + scale1 * b.x;
	retVal.y = scale0 * a.y + scale1 * b.y;
	retVal.z = scale0 * a.z + scale1 * b.z;
	retVal.w = scale0 * a.w + scale1 * b.w;
	retVal.Normalize();
	return retVal;
}


Quaternion Concatenate(const Quaternion& q, const Quaternion& p)
{
	Quaternion retVal;


	Vector3 qv(q.x, q.y, q.z);
	Vector3 pv(p.x, p.y, p.z);
	Vector3 newVec = p.w * qv + q.w * pv + Cross(pv, qv);
	retVal.x = newVec.x;
	retVal.y = newVec.y;
	retVal.z = newVec.z;


	retVal.w = p.w * q.w - Dot(pv, qv);

	return retVal;
}

Matrix4 CreateFromQuaternion(const class Quaternion& q)
{
	float mat[4][4];

	mat[0][0] = 1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z;
	mat[0][1] = 2.0f * q.x * q.y + 2.0f * q.w * q.z;
	mat[0][2] = 2.0f * q.x * q.z - 2.0f * q.w * q.y;
	mat[0][3] = 0.0f;

	mat[1][0] = 2.0f * q.x * q.y - 2.0f * q.w * q.z;
	mat[1][1] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z;
	mat[1][2] = 2.0f * q.y * q.z + 2.0f * q.w * q.x;
	mat[1][3] = 0.0f;

	mat[2][0] = 2.0f * q.x * q.z + 2.0f * q.w * q.y;
	mat[2][1] = 2.0f * q.y * q.z - 2.0f * q.w * q.x;
	mat[2][2] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y;
	mat[2][3] = 0.0f;

	mat[3][0] = 0.0f;
	mat[3][1] = 0.0f;
	mat[3][2] = 0.0f;
	mat[3][3] = 1.0f;

	return Matrix4(mat);
}

#endif