#include "Vector3.h"

/// <summary>
/// Constructor
/// </summary>
MyVector3::MyVector3() {};

/// <summary>
/// Deconstructor
/// </summary>
MyVector3::~MyVector3() {};

/// <summary>
/// Second Contructor
/// </summary>
MyVector3::MyVector3(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
};

/// <summary>
/// Get the value of x
/// </summary>
float MyVector3::getX()
{
	return x;
};

/// <summary>
/// Set the value of x
/// </summary>
void MyVector3::setX(float X)
{
	x = X;
}

/// <summary>
/// Set the value of Y
/// </summary>
void MyVector3::setY(float Y)
{
	y = Y;
}

/// <summary>
/// Set the value of Z
/// </summary>
void MyVector3::setZ(float Z)
{
	z = Z;
}

/// <summary>
/// Returns the value of y
/// </summary>
float MyVector3::getY()
{
	return y;
}

/// <summary>
/// Returns the value of z
/// </summary>
float MyVector3::getZ()
{
	return z;
}

/// <summary>
/// A method to return the length of the vector
/// </summary>
/// <returns></returns>
float MyVector3::length()
{
	return (double)(std::sqrt(x*x + y*y + z*z));
}

/// <summary>
/// A method to return the length squared of the vector
/// </summary>
/// <returns></returns>
float MyVector3::lengthSquared()
{
	return (x*x + y*y + z*z);
}

/// <summary>
/// A method to reduce the length of the vector to 1.0
/// keeping the direction the same
/// </summary>
void MyVector3::normalise()
{
	if (length() > 0)	//Check for divide by zero
	{
		double magnit = length();
		x /= magnit;
		y /= magnit;
		z /= magnit;
	}
}

/// <summary>
/// An overloaded operator + to return the sum of 2 vectors
/// </summary>
/// <param name="V2"></param>
/// <returns></returns>
MyVector3 MyVector3::operator +(MyVector3 V2)
{
	return MyVector3(x + V2.x, y + V2.y, z + V2.z);
}

/// <summary>
/// An overloaded operator - to return the difference of 2 vectors
/// </summary>
/// <param name="V2"></param>
/// <returns></returns>
MyVector3 MyVector3::operator -(MyVector3 V2)
{
	return MyVector3(x - V2.x, y - V2.y, z - V2.z);
}

/// <summary>
/// An overloaded operator - to return the negation of a single vector
/// </summary>
/// <returns></returns>
MyVector3 MyVector3::operator -()
{
	MyVector3 V1 = MyVector3();
	V1.x = -x;
	V1.y = -y;
	V1.z = -z;
	return V1;
}

/// <summary>
/// An overloaded operator * to return the scalar product of 2 vectors
/// </summary>
/// <param name="V2"></param>
/// <returns></returns>
float MyVector3::operator *(MyVector3 V2)
{
	return (x * V2.x + y * V2.y + z * V2.z);
}

/// <summary>
/// An overloaded operator * to return the product of a scalar by a vector
/// </summary>
/// <param name="k"></param>
/// <returns></returns>
MyVector3 MyVector3::operator *(double k)
{
	return MyVector3(x * k, y * k, z * k);
}

/// <summary>
/// An overloaded operator * to return the product of a scalar by a vector
/// </summary>
/// <param name="k"></param>
/// <returns></returns>
MyVector3 MyVector3::operator *(float k)
{
	return MyVector3(x * k, y * k, z * k);
}

/// <summary>
/// An overloaded operator * to return the product of a scalar by a vector
/// </summary>
/// <param name="k"></param>
/// <returns></returns>
MyVector3 MyVector3::operator *(int k)
{
	return MyVector3(x * k, y * k, z * k);
}

/// <summary>
/// An overloaded operator ^ to return the vector product of 2 vectors
/// </summary>
/// <param name="V2"></param>
/// <returns></returns>
MyVector3 MyVector3::operator ^(MyVector3 V2)
{
	return MyVector3(y * V2.z - z * V2.y, z * V2.x - x * V2.z, x * V2.y - y * V2.x);
}

MyVector3 MyVector3::crossProduct(MyVector3 v2)
{
	return MyVector3(-1 * ((z * v2.y) - (y * v2.z)), (z * v2.x) - (x * v2.z), (x * v2.y) - (y * v2.x));
}