
#include <Vector.h>
#include <math.h>

Vector2 Vector2::up(.0, 1.0), Vector2::down(.0, -1.), Vector2::right(1.0, .0), Vector2::left(-1.0, .0), Vector2::zero(0, 0), Vector2::one(1, 1);

Vector2::Vector2() :x(0.), y(0.)
{
}

Vector2::Vector2(double X, double Y) : x(X), y(Y)
{
}

Vector2::~Vector2()
{
}

Vector2 Vector2::operator+(Vector2 foo)
{
	return Vector2(x + foo.x, y + foo.y);
}

Vector2 Vector2::operator-(Vector2 foo)
{
	return Vector2(x - foo.x, y - foo.y);
}

Vector2 Vector2::operator-()
{
	return Vector2(-x, -y);
}


Vector2 Vector2::operator*(double foo)
{
	return Vector2(x * foo, y * foo);
}

Vector2 Vector2::operator*(float foo)
{
	return Vector2(x * (double)foo, y * (double)foo);
}


Vector2 Vector2::operator/(double foo)
{
	return Vector2(x / foo, y / foo);
}

Vector2 Vector2::operator/(float foo)
{
	return Vector2(x / (double)foo, y / (double)foo);
}


double Vector2::Scalar(Vector2 foo)
{
	return x * foo.x + y * foo.y;
}

void Vector2::operator+=(Vector2 foo)
{
	x += foo.x;
	y += foo.y;
}

void Vector2::operator-=(Vector2 foo)
{
	x -= foo.x;
	y -= foo.y;
}

bool Vector2::operator==(Vector2 foo)
{
	return x == foo.x && y == foo.y;
}

bool Vector2::operator!=(Vector2 foo)
{
	return x != foo.x || y != foo.y;
}

Vector2 Vector2::Normalize()
{
	Vector2 normalizedVec = *this;
	double magnitude = normalizedVec.Magnitude();

	Vector2 newVec(normalizedVec.x / magnitude, normalizedVec.y / magnitude);
	return newVec;
}

Vector2 Vector2::Absolute()
{
	return Vector2(abs(x), abs(y));
}

double Vector2::VectorAngle(Vector2 foo) // IN RADIANS
{
	return acos(((*this).Scalar(foo)) / (Magnitude() * foo.Magnitude()));
}

double Vector2::Magnitude()
{
	return sqrt(x * x + y * y);
}

std::string Vector2::toString()
{
	int X = (int)x;
	int Y = (int)y;

	return std::to_string(X) + " " + std::to_string(Y);
}

// ************************************
// VECTOR3

Vector3 Vector3::up(.0, 1.0, 0),
Vector3::down(.0, -1., 0), 
Vector3::right(1.0, .0, 0),
Vector3::left(-1.0, .0, 0),
Vector3::forwards(0., .0, 1.),
Vector3::backwards(0., .0, -1.),
Vector3::zero(0, 0, 0),
Vector3::one(1, 1, 1);

Vector3::Vector3() : x(0.), y(0.), z(0.)
{
}

Vector3::Vector3(Vector2 vec) : x(vec.x), y(vec.y), z(0.)
{
}

Vector3::Vector3(double X, double Y, double Z) : x(X), y(Y), z(Z)
{
}

Vector3::~Vector3()
{
}

Vector3 Vector3::operator+(Vector3 foo)
{
	return Vector3(x + foo.x, y + foo.y, z + foo.z);
}

Vector3 Vector3::operator-(Vector3 foo)
{
	return Vector3(x - foo.x, y - foo.y,z - foo.z);
}

Vector3 Vector3::operator-()
{
	return Vector3(-x, -y, -z);
}


Vector3 Vector3::operator*(double foo)
{
	return Vector3(x * foo, y * foo, z * foo);
}

Vector3 Vector3::operator*(float foo)
{
	return Vector3(x * (double)foo, y * (double)foo, z * (double)foo);
}


Vector3 Vector3::operator/(double foo)
{
	return Vector3(x / foo, y / foo, z / foo);
}

Vector3 Vector3::operator/(float foo)
{
	return Vector3(x / (double)foo, y / (double)foo, z / (double)foo);
}

void Vector3::operator+=(Vector3 foo)
{
	x += foo.x;
	y += foo.y;
	z += foo.z;
}

void Vector3::operator-=(Vector3 foo)
{
	x -= foo.x;
	y -= foo.y;
	z -= foo.z;
}

bool Vector3::operator==(Vector3 foo)
{
	return x == foo.x && y == foo.y && z == foo.z;
}

bool Vector3::operator!=(Vector3 foo)
{
	return x != foo.x || y != foo.y || z != foo.z;
}

Vector3 Vector3::Normalize()
{
	Vector3 normalizedVec = *this;
	double magnitude = normalizedVec.Magnitude();

	Vector3 newVec(normalizedVec.x / magnitude, normalizedVec.y / magnitude, normalizedVec.z / magnitude);
	return newVec;
}

Vector3 Vector3::Absolute()
{
	return Vector3(abs(x), abs(y), abs(z));
}

double Vector3::VectorAngle(Vector3 foo) // IN RADIANS
{
	return acos(((*this).Scalar(foo)) / (Magnitude() * foo.Magnitude()));
}

double Vector3::Magnitude()
{
	return sqrt(x * x + y * y + z * z);
}

double Vector3::Scalar(Vector3 foo)
{
	return x * foo.x + y * foo.y + z * foo.z;
}
