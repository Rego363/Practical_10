#include "Matrix3.h"


Matrix3::Matrix3()
{
	A11 = 0.0;
	A12 = 0.0;
	A13 = 0.0;
	A21 = 0.0;
	A22 = 0.0;
	A23 = 0.0;
	A31 = 0.0;
	A32 = 0.0;
	A33 = 0.0;
}

Matrix3::~Matrix3() {};

float Matrix3::getFirst()
{
	return A11;
}

Matrix3::Matrix3(MyVector3 Row1, MyVector3 Row2, MyVector3 Row3)
{
	A11 = Row1.getX();
	A12 = Row1.getY();
	A13 = Row1.getZ();
	A21 = Row2.getX();
	A22 = Row2.getY();
	A23 = Row2.getZ();
	A31 = Row3.getX();
	A32 = Row3.getY();
	A33 = Row3.getZ();
}
void Matrix3::setMatrix(MyVector3 Row1, MyVector3 Row2, MyVector3 Row3)
{
	A11 = Row1.getX();
	A12 = Row1.getY();
	A13 = Row1.getZ();
	A21 = Row2.getX();
	A22 = Row2.getY();
	A23 = Row2.getZ();
	A31 = Row3.getX();
	A32 = Row3.getY();
	A33 = Row3.getZ();
}
Matrix3::Matrix3(float _A11, float _A12, float _A13,
	float _A21, float _A22, float _A23,
	float _A31, float _A32, float _A33)
{
	A11 = _A11;
	A12 = _A12;
	A13 = _A13;
	A21 = _A21;
	A22 = _A22;
	A23 = _A23;
	A31 = _A31;
	A32 = _A32;
	A33 = _A33;
}

MyVector3 Matrix3::operator *(MyVector3 V1)
{
	return  MyVector3(A11 * V1.getX() + A12 * V1.getY() + A13 * V1.getZ(),
		A21 * V1.getX() + A22 * V1.getY() + A23 * V1.getZ(),
		A31 * V1.getX() + A32 * V1.getY() + A33 * V1.getZ());
}

Matrix3 Matrix3::transpose()
{
	return Matrix3(A11, A21, A31,
		A12, A22, A32,
		A13, A23, A33);
}

Matrix3 Matrix3::operator +(Matrix3 M2)
{
	return Matrix3(A11 + M2.A11, A12 + M2.A12, A13 + M2.A13,
		A21 + M2.A21, A22 + M2.A22, A23 + M2.A23,
		A31 + M2.A31, A32 + M2.A32, A33 + M2.A33);
}

Matrix3 Matrix3::operator *(Matrix3 M2)
{
	Matrix3 answer = Matrix3();
	answer.A11 = row(0) * M2.column(0);
	answer.A12 = row(0) * M2.column(1);
	answer.A13 = row(0) * M2.column(2);
							 
	answer.A21 = row(1) * M2.column(0);
	answer.A22 = row(1) * M2.column(1);
	answer.A23 = row(1) * M2.column(2);
							 
	answer.A31 = row(2) * M2.column(0);
	answer.A32 = row(2) * M2.column(1);
	answer.A33 = row(2) * M2.column(2);


	return answer;
}

Matrix3 Matrix3::operator =(Matrix3 M2)
{
	
	A11 = M2.A11;
	A12 = M2.A12;
	A13 = M2.A13;

	A21 = M2.A21;
	A22 = M2.A22;
	A23 = M2.A23;

	A31 = M2.A31;
	A32 = M2.A32;
	A33 = M2.A33;

	Matrix3 answer = Matrix3(row(0), row(1), row(2));
	return answer;
}

Matrix3 Matrix3::operator -(Matrix3 M2)
{
	return Matrix3(A11 - M2.A11, A12 - M2.A12, A13 - M2.A13,
		A21 - M2.A21, A22 - M2.A22, A23 - M2.A23,
		A31 - M2.A31, A32 - M2.A32, A33 - M2.A33);
}

Matrix3 Matrix3::operator *(float x)
{
	Matrix3 answer = Matrix3();
	answer.A11 = A11 * x;
	answer.A12 = A12 * x;
	answer.A13 = A13 * x;

	answer.A21 = A21 * x;
	answer.A22 = A22 * x;
	answer.A23 = A23 * x;

	answer.A31 = A31 * x;
	answer.A32 = A32 * x;
	answer.A33 = A33 * x;

	return answer;
}

double Matrix3::determinant()
{
	return A11 * A22 * A33 - A11 * A32 * A23 + A21 * A32 * A13 - A31 * A22 * A13 + A31 * A12 * A23 - A21 * A12 * A33;
}

MyVector3 Matrix3::row(int i)
{
	switch (i)
	{
	case 0:
		return MyVector3(A11, A12, A13);
	case 1:
		return MyVector3(A21, A22, A23);
	case 2:
	default:
		return MyVector3(A31, A32, A33);
	}
}

MyVector3 Matrix3::column(int i)
{
	switch (i)
	{
	case 0:
		return MyVector3(A11, A21, A31);
	case 1:
		return MyVector3(A12, A22, A32);
	case 2:
	default:
		return MyVector3(A13, A23, A33);
	}
}

Matrix3 Matrix3::inverse()
{
	double det = determinant();
	if (det == 0)
		return Matrix3();
	else
	{
		double scale = 1 / det;
		Matrix3 answer = Matrix3();
		answer.A11 = scale * (A22 * A33 - A23 * A32); // ei-fh
		answer.A12 = scale * (A13 * A32 - A12 * A33); // ch-bi
		answer.A13 = scale * (A12 * A23 - A13 * A22); // ch-bi

		answer.A21 = scale * (A23 * A31 - A21 * A33); // fg-di
		answer.A22 = scale * (A11 * A33 - A13 * A31); // ai-cg
		answer.A23 = scale * (A13 * A21 - A11 * A23); // cd-af


		answer.A31 = scale * (A21 * A32 - A22 * A31); // dh-eg
		answer.A32 = scale * (A12 * A31 - A11 * A32); // bg-ah
		answer.A33 = scale * (A11 * A22 - A12 * A21); // ae-bd

		return answer;
	}
}

Matrix3 Matrix3::rotation(float _angle)
{
	double radians = PI / 180 * _angle;
	Matrix3 answer = Matrix3();
	answer.A11 = std::cos(radians);
	answer.A12 = std::sin(radians);
	answer.A13 = 0;
	answer.A21 = -std::sin(radians);
	answer.A22 = std::cos(radians);
	answer.A23 = 0;
	answer.A31 = 0;
	answer.A32 = 0;
	answer.A33 = 1;

	return answer;
}

Matrix3 Matrix3::translateX(float dx, float dy)
{
	Matrix3 answer = Matrix3();
	answer.A11 = 1;
	answer.A12 = dx;
	answer.A13 = dy;
	answer.A21 = 0;
	answer.A22 = 1;
	answer.A23 = 0;
	answer.A31 = 0;
	answer.A32 = 0;
	answer.A33 = 1;

	return answer;
}

Matrix3 Matrix3::translateY(float dx, float dy)
{
	Matrix3 answer = Matrix3();
	answer.A11 = 1;
	answer.A12 = 0;
	answer.A13 = 0;
	answer.A21 = dx;
	answer.A22 = 1;
	answer.A23 = dy;
	answer.A31 = 0;
	answer.A32 = 0;
	answer.A33 = 1;

	return answer;
}

Matrix3 Matrix3::translateZ(float dx, float dy)
{
	Matrix3 answer = Matrix3();
	answer.A11 = 1;
	answer.A12 = 0;
	answer.A13 = 0;
	answer.A21 = 0;
	answer.A22 = 1;
	answer.A23 = 0;
	answer.A31 = dx;
	answer.A32 = dy;
	answer.A33 = 1;

	return answer;
}

Matrix3 Matrix3::scale(float dx, float dy)
{
	Matrix3 answer = Matrix3();
	answer.A11 = dx / 100;
	answer.A12 = 0;
	answer.A13 = 0;
	answer.A21 = 0;
	answer.A22 = dy / 100;
	answer.A23 = 0;
	answer.A31 = 0;
	answer.A32 = 0;
	answer.A33 = 1;

	return answer;
}

Matrix3 Matrix3::operator-()
{
	Matrix3 answer;
	answer.A11 = -1 * A11;
	answer.A12 = -1 * A12;
	answer.A13 = -1 * A13;
	answer.A21 = -1 * A21;
	answer.A22 = -1 * A22;
	answer.A23 = -1 * A23;
	answer.A31 = -1 * A31;
	answer.A32 = -1 * A32;
	answer.A33 = -1 * A33;
	return answer;
}

MyVector3 Matrix3::rotVecX(MyVector3 V, float _angle)
{
	float radians = PI / 180 * _angle;
	MyVector3 answer = V;
	Matrix3 mould = Matrix3();
	mould.A11 = 1.0f;
	mould.A12 = 0;
	mould.A13 = 0;
	mould.A21 = 0;
	mould.A22 = std::cos(radians);
	mould.A23 = -std::sin(radians);
	mould.A31 = 0;
	mould.A32 = std::sin(radians);
	mould.A33 = std::cos(radians);

	answer = mould * answer;

	return answer;
}

Matrix3 Matrix3::rotationX(float _angle)
{
	float radians = PI / 180 * _angle;
	Matrix3 answer = Matrix3();
	answer.A11 = 1.0f;
	answer.A12 = 0;
	answer.A13 = 0;
	answer.A21 = 0;
	answer.A22 = std::cos(radians);
	answer.A23 = -std::sin(radians);
	answer.A31 = 0;
	answer.A32 = std::sin(radians);
	answer.A33 = std::cos(radians);

	return answer;
}

MyVector3 Matrix3::rotVecY(MyVector3 V, float _angle)
{
	float radians = PI / 180 * _angle;
	MyVector3 answer = V;
	Matrix3 mould = Matrix3();
	mould.A11 = std::cos(radians);
	mould.A12 = 0;
	mould.A13 = std::sin(radians);
	mould.A21 = 0;
	mould.A22 = 1.0f;
	mould.A23 = 0;;
	mould.A31 = -std::sin(radians);
	mould.A32 = 0;
	mould.A33 = std::cos(radians);

	answer = mould * answer;

	return answer;
}

Matrix3 Matrix3::rotationY(float _angle)
{
	float radians = PI / 180 * _angle;
	Matrix3 answer = Matrix3();
	answer.A11 = std::cos(radians);
	answer.A12 = 0;
	answer.A13 = std::sin(radians);
	answer.A21 = 0;
	answer.A22 = 1.0f;
	answer.A23 = 0;
	answer.A31 = -std::sin(radians);
	answer.A32 = 0;
	answer.A33 = std::cos(radians);

	return answer;
}

Matrix3 Matrix3::rotationZ(float _angle)
{
	float radians = (PI / 180) * _angle;
	Matrix3 answer = Matrix3();
	answer.A11 = std::cos(radians);
	answer.A12 = -std::sin(radians);
	answer.A13 = 0;
	answer.A21 = std::sin(radians);
	answer.A22 = std::cos(radians);
	answer.A23 = 0;
	answer.A31 = 0;
	answer.A32 = 0;
	answer.A33 = 1.0f;

	return answer;
}

Matrix3 Matrix3::Scale3D(int dx)
{
	Matrix3 answer = Matrix3();
	answer.A11 = dx / 100;
	answer.A12 = 0;
	answer.A13 = 0;
	answer.A21 = 0;
	answer.A22 = dx / 100;
	answer.A23 = 0;
	answer.A31 = 0;
	answer.A32 = 0;
	answer.A33 = dx / 100;

	return answer;
}