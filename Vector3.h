#ifndef VECTOR3_H
#define VECTOR3_H
#include <iostream>
#include <cmath>
#include "Math.h"

class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3()
		:x(0.0f)
		, y(0.0f)
		, z(0.0f)
	{}

	explicit Vector3(float inX, float inY, float inZ)
		:x(inX)
		, y(inY)
		, z(inZ)
	{}


	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&x);
	}

	void Set(float inX, float inY, float inZ)
	{
		x = inX;
		y = inY;
		z = inZ;
	}

	friend Vector3 operator+(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	friend Vector3 operator-(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	friend Vector3 operator*(const Vector3& left, const Vector3& right)
	{
		return Vector3(left.x * right.x, left.y * right.y, left.z * right.z);
	}

	friend Vector3 operator*(const Vector3& vec, float scalar)
	{
		return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}

	friend Vector3 operator*(float scalar, const Vector3& vec)
	{
		return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}

	Vector3& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}


	Vector3& operator+=(const Vector3& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	}

	Vector3& operator-=(const Vector3& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	}

	float LengthSq() const
	{
		return (x * x + y * y + z * z);
	}

	float Length() const
	{
		return (Math::Sqrt(LengthSq()));
	}

	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
		z /= length;
	}

	static Vector3 Normalize(const Vector3& vec)
	{
		Vector3 temp = vec;
		temp.Normalize();
		return temp;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Vector3& v) {
		return stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	}
};

const Vector3 Zero3(0.0f, 0.0f, 0.f);
const Vector3 UnitX3(1.0f, 0.0f, 0.0f);
const Vector3 UnitY3(0.0f, 1.0f, 0.0f);
const Vector3 UnitZ3(0.0f, 0.0f, 1.0f);
const Vector3 NegUnitX3(-1.0f, 0.0f, 0.0f);
const Vector3 NegUnitY3(0.0f, -1.0f, 0.0f);
const Vector3 NegUnitZ3(0.0f, 0.0f, -1.0f);
const Vector3 Infinity(Math::Infinity, Math::Infinity, Math::Infinity);
const Vector3 NegInfinity(Math::NegInfinity, Math::NegInfinity, Math::NegInfinity);


float Dot(const Vector3& a, const Vector3& b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

Vector3 Cross(const Vector3& a, const Vector3& b)
{
	Vector3 temp;
	temp.x = a.y * b.z - a.z * b.y;
	temp.y = a.z * b.x - a.x * b.z;
	temp.z = a.x * b.y - a.y * b.x;
	return temp;
}


Vector3 Lerp(const Vector3& a, const Vector3& b, float f)
{
	return Vector3(a + f * (b - a));
}

Vector3 Reflect(const Vector3& v, const Vector3& n)
{
	return v - 2.0f * Dot(v, n) * n;
}

#endif