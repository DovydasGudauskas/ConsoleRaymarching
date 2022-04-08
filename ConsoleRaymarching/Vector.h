#pragma once

#include <string>

# define PI 3.14159265358979323846  /* pi */
const static double Deg2Rad = (PI * 2.) / 360.;
const static double Rad2Deg = 360. / (PI * 2.);

class Vector2
{
public:
	static Vector2 up, down, right, left, zero, one;

	double x, y;

	Vector2();
	Vector2(double X, double Y);
	~Vector2();

	Vector2 operator +(Vector2 foo);
	Vector2 operator -(Vector2 foo);

	Vector2 operator -();

	Vector2 operator *(float foo);
	Vector2 operator *(double foo);

	Vector2 operator /(float foo);
	Vector2 operator /(double foo);

	void operator +=(Vector2 foo);
	void operator -=(Vector2 foo);

	bool operator ==(Vector2 foo);
	bool operator !=(Vector2 foo);

	Vector2 Normalize();
	Vector2 Absolute();
	double Scalar(Vector2 foo);

	double VectorAngle(Vector2 foo);

	double Magnitude();

	std::string toString();
};

class Vector3
{
public:
	double x, y, z;

	static Vector3 up, down, right, left, forwards, backwards, zero, one;

	Vector3();
	Vector3(Vector2 vec);
	Vector3(double X, double Y, double Z);

	~Vector3();

	Vector3 operator +(Vector3 foo);
	Vector3 operator -(Vector3 foo);

	Vector3 operator -();

	Vector3 operator *(float foo);
	Vector3 operator *(double foo);

	Vector3 operator /(float foo);
	Vector3 operator /(double foo);

	void operator +=(Vector3 foo);
	void operator -=(Vector3 foo);

	bool operator ==(Vector3 foo);
	bool operator !=(Vector3 foo);

	Vector3 Normalize();
	Vector3 Absolute();

	double VectorAngle(Vector3 foo);
	double Scalar(Vector3 foo);

	double Magnitude();

	static Vector3 RotateByX(Vector3 vec, float alpha)
	{
		float Y = vec.y;
		float Z = vec.z;

		vec.y = Y * cos(alpha) - Z * sin(alpha);
		vec.z = Y * sin(alpha) + Z * cos(alpha);

		return vec;
	}

	static Vector3 RotateByY(Vector3 vec, float alpha)
	{
		float X = vec.x;
		float Y = vec.y;
		float Z = vec.z;

		vec.x = X * cos(alpha) - Y * sin(alpha);
		vec.z = -X * sin(alpha) + Z * cos(alpha);

		return vec;
	}

	static Vector3 RotateByZ(Vector3 vec, float alpha)
	{
		float X = vec.x;
		float Y = vec.y;

		vec.x = X * cos(alpha) - Y * sin(alpha);
		vec.y = X * sin(alpha) + Y * cos(alpha);

		return vec;
	}
};

/*Vector2 operator*(double bar, const Vector2& foo)
{
	return Vector2(bar * foo.x, bar * foo.y);
}

Vector2 operator*(float bar, const Vector2& foo)
{
	return Vector2((double)bar * foo.x, (double)bar * foo.y);
}*/