#pragma once

#include <iostream>
#include <string>

class MyVector3
{
private:
	float x;
	float y;
	float z;

public:
	MyVector3();
	~MyVector3();
	MyVector3(float X, float Y, float Z);
	float getX();
	float getY();
	float getZ();
	void setX(float X);
	void setY(float Y);
	void setZ(float Z);
	float length();
	float lengthSquared();
	void normalise();
	MyVector3 operator +(MyVector3 V2);
	MyVector3 operator -(MyVector3 V2);
	MyVector3 operator -();
	float operator *(MyVector3 V2);
	MyVector3 operator *(double k);
	MyVector3 operator *(float k);
	MyVector3 operator *(int k);
	MyVector3 operator ^(MyVector3 V2);
	MyVector3 crossProduct(MyVector3 V2);
	//std::string toString();
};
