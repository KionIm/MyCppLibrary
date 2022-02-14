#ifndef VECTOR2_H
#define VECTOR2_H
#include <iostream>
#include <cmath>
#include "Math.h"

class Vector2
{
public:
	float x;
	float y;

	Vector2()
		:x(0.0f)
		, y(0.0f)
	{}

	explicit Vector2(float inX, float inY)
		:x(inX)
		, y(inY)
	{}


	void Set(float inX, float inY)
	{
		x = inX;
		y = inY;
	}

	friend Vector2 operator+(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x + b.x, a.y + b.y);
	}

	friend Vector2 operator-(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x - b.x, a.y - b.y);
	}


	friend Vector2 operator*(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x * b.x, a.y * b.y);
	}


	friend Vector2 operator*(const Vector2& vec, float scalar)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}

	friend Vector2 operator*(float scalar, const Vector2& vec)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}

	friend Vector2 operator/(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x / b.x, a.y / b.y);
	};
	friend Vector2 operator/(const Vector2& a, float k)
	{
		return Vector2(a.x / k, a.y / k);
	};
	friend Vector2 operator/(float k, const Vector2& v) 
	{
		return Vector2(k / v.x, k / v.y);
	}

	Vector2& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}


	Vector2& operator+=(const Vector2& right)
	{
		x += right.x;
		y += right.y;
		return *this;
	}


	Vector2& operator-=(const Vector2& right)
	{
		x -= right.x;
		y -= right.y;
		return *this;
	}

	float operator[](int i) const {
		if (i == 0) return x;
		else if (i == 1) return y;
	};

	friend std::ostream& operator<<(std::ostream& stream, const Vector2& v) {
		return stream << "(" << v.x << ", " << v.y << ")";
	}

	float LengthSq() const
	{
		return (x * x + y * y);
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
	}

	static Vector2 Normalize(const Vector2& vec)
	{
		Vector2 temp = vec;
		temp.Normalize();
		return temp;
	}

};

const Vector2 Zero2(0.0f, 0.0f);
const Vector2 UnitX2(1.0f, 0.0f);
const Vector2 UnitY2(0.0f, 1.0f);
const Vector2 NegUnitX2(-1.0f, 0.0f);
const Vector2 NegUnitY2(0.0f, -1.0f);

float Dot(const Vector2& a, const Vector2& b)
{
	return (a.x * b.x + a.y * b.y);
}


Vector2 Lerp(const Vector2& a, const Vector2& b, float f)
{
	return a + f * (b - a);
}


Vector2 Reflect(const Vector2& v, const Vector2& n)
{
	return v - 2.0f * Dot(v, n) * n;
}



#endif