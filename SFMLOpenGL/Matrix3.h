#pragma once

#include <iostream>
#include "Vector3.h"
#define _USE_MATH_DEFINES
#include <cmath>

class Matrix3
{
private:
	const float PI =2 * std::acos(0.0);
	float A11;
	float A12;
	float A13;
	float A21;
	float A22;
	float A23;
	float A31;
	float A32;
	float A33;

public:
	Matrix3();
	~Matrix3();
	Matrix3(MyVector3 Row1, MyVector3 Row2, MyVector3 Row3);
	Matrix3(float _A11, float _A12, float _A13,
		float _A21, float _A22, float _A23,
		float _A31, float _A32, float _A33);
	void setMatrix(MyVector3 Row1, MyVector3 Row2, MyVector3 Row3);
	MyVector3 operator *(MyVector3 V1);
	MyVector3 rotVecX(MyVector3 V, float _angle);
	MyVector3 rotVecY(MyVector3 V, float _angle);
	Matrix3 transpose();
	Matrix3 operator +(Matrix3 M2);
	Matrix3 operator -(Matrix3 M2);
	Matrix3 operator *(float x);
	Matrix3 operator *(Matrix3 M2);
	Matrix3 operator =(Matrix3 M2);
	double determinant();
	MyVector3 row(int i);
	float getFirst();
	MyVector3 column(int i);
	Matrix3 inverse();
	Matrix3 rotation(float _angle);
	Matrix3 translateX(float dx, float dy);
	Matrix3 translateY(float dx, float dy);
	Matrix3 translateZ(float dx, float dy);
	Matrix3 scale(float dx, float dy);
	Matrix3 operator -();
	Matrix3 rotationX(float _angle);
	Matrix3 rotationY(float _angle);
	Matrix3 rotationZ(float _angle);
	Matrix3 Scale3D(int dx);
};