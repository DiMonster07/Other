#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include "vec4.h"
#include "mat4.h"
#include <set>

Mat4::Mat4(float x11, float x12, float x13, float x14, 
	       float x21, float x22, float x23, float x24, 
	       float x31, float x32, float x33, float x34,
	       float x41, float x42, float x43, float x44)
{
	this->matrix[0][0] = x11; this->matrix[0][1] = x12; this->matrix[0][2] = x13; this->matrix[0][3] = x14;
	this->matrix[1][0] = x21; this->matrix[1][1] = x22; this->matrix[1][2] = x23; this->matrix[1][3] = x24;
	this->matrix[2][0] = x31; this->matrix[2][1] = x32; this->matrix[2][2] = x33; this->matrix[2][3] = x34;
	this->matrix[3][0] = x41; this->matrix[3][1] = x42; this->matrix[3][2] = x43; this->matrix[3][3] = x44;  
}

Mat4::Mat4(Vec4 v1, Vec4 v2, Vec4 v3, Vec4 v4)
{
	this->matrix[0][0] = v1.x; this->matrix[0][1] = v1.y; this->matrix[0][2] = v1.z; this->matrix[0][3] = v1.w;
	this->matrix[1][0] = v2.x; this->matrix[1][1] = v2.y; this->matrix[1][2] = v2.z; this->matrix[1][3] = v2.w;
	this->matrix[2][0] = v3.x; this->matrix[2][1] = v3.y; this->matrix[2][2] = v3.z; this->matrix[2][3] = v3.w;
	this->matrix[3][0] = v4.x; this->matrix[3][1] = v4.y; this->matrix[3][2] = v4.z; this->matrix[3][3] = v4.w;
}

Mat4::Mat4(const Mat4 &v)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			this->matrix[i][j] = v.matrix[i][j];
}

Mat4 Mat4::operator+(Mat4& b)
{
	Mat4 result = Mat4();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.matrix[i][j] = this->matrix[i][j] + b.matrix[i][j];
	return result;
}

Mat4 Mat4::operator+(const int& b)
{
	Mat4 result = Mat4();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.matrix[i][j] = this->matrix[i][j] + b;
	return result;
}

Mat4 Mat4::operator+(const float& b)
{
	Mat4 result = Mat4();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.matrix[i][j] = this->matrix[i][j] + b;
	return result;
}

Mat4 Mat4::operator-(Mat4& b)
{
	Mat4 result = Mat4();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.matrix[i][j] = this->matrix[i][j] - b.matrix[i][j];
	return result;
}

Mat4 Mat4::operator-(const int& b)
{
	Mat4 result = Mat4();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.matrix[i][j] = this->matrix[i][j] - b;
	return result;
}

Mat4 Mat4::operator-(const float& b)
{
	Mat4 result = Mat4();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.matrix[i][j] = this->matrix[i][j] - b;
	return result;
}

Mat4 Mat4::operator*(Mat4& b)
{
    Mat4 result(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
			    result.matrix[i][j] += this->matrix[i][k] * b.matrix[k][j];
	return result;
}
Mat4 Mat4::operator*(const int& b)
{
	Mat4 result = Mat4();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.matrix[i][j] = this->matrix[i][j] * b;
	return result;
}

Mat4 Mat4::operator*(const float& b)
{
	Mat4 result = Mat4();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.matrix[i][j] = this->matrix[i][j] * b;
	return result;
}

Mat4 Mat4::operator/(const float& b)
{
	if (b == 0) return Mat4();
	Mat4 result = Mat4();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.matrix[i][j] = this->matrix[i][j] / b;
	return result;
}

bool Mat4::operator==(const Mat4 &v) const
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (this->matrix[i][j] != v.matrix[i][j]) return false;
	return true;
}

bool Mat4::operator!=(const Mat4 &v) const
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (this->matrix[i][j] != v.matrix[i][j]) return true;
	return false;
}

Mat4 Mat4::transpose ()
{
	Mat4 result = Mat4();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.matrix[i][j] = this->matrix[j][i];
	return result;
}

float Mat4::det2(int c1, int c2, int r1, int r2)
{
	return this->matrix[c1][r1]*this->matrix[c2][r2] - this->matrix[c2][r1]*this->matrix[c1][r2];
}

float Mat4::det3(int c1, int c2, int c3, int r1, int r2, int r3)
{
    float result = 0;
    result = this->matrix[c1][r1]*this->matrix[c2][r2]*this->matrix[c3][r3] + 
    		 this->matrix[c2][r1]*this->matrix[c3][r2]*this->matrix[c1][r3] +
		     this->matrix[c3][r1]*this->matrix[c1][r2]*this->matrix[c2][r3] - 
		     this->matrix[c1][r3]*this->matrix[c2][r2]*this->matrix[c3][r1] -
		     this->matrix[c2][r3]*this->matrix[c3][r2]*this->matrix[c1][r1] - 
		     this->matrix[c3][r3]*this->matrix[c1][r2]*this->matrix[c2][r1];
    return result;
}

float Mat4::det()
{
	float result = 0;
	result += this->matrix[0][0]*this->det3(1, 2, 3, 1, 2, 3);
	result -= this->matrix[0][1]*this->det3(1, 2, 3, 0, 2, 3);
	result += this->matrix[0][2]*this->det3(1, 2, 3, 0, 1, 3);
	result -= this->matrix[0][3]*this->det3(1, 2, 3, 0, 1, 2);
	return result;
}

Mat4 Mat4::inverse()
{
	Mat4 result = Mat4();
	float det = this->det();
	result.matrix[0][0] =  det3(1, 2, 3, 1, 2, 3)/det;
	result.matrix[0][1] = -det3(0, 2, 3, 1, 2, 3)/det;
	result.matrix[0][2] =  det3(0, 1, 3, 1, 2, 3)/det;
	result.matrix[0][3] = -det3(0, 1, 2, 1, 2, 3)/det;
	result.matrix[1][0] = -det3(1, 2, 3, 0, 2, 3)/det;
	result.matrix[1][1] =  det3(0, 2, 3, 0, 2, 3)/det;
	result.matrix[1][2] = -det3(0, 1, 3, 0, 2, 3)/det;
	result.matrix[1][3] =  det3(0, 1, 2, 0, 2, 3)/det;
	result.matrix[2][0] =  det3(1, 2, 3, 0, 1, 3)/det;
	result.matrix[2][1] = -det3(0, 2, 3, 0, 1, 3)/det;
	result.matrix[2][2] =  det3(0, 1, 3, 0, 1, 3)/det;
	result.matrix[2][3] = -det3(0, 1, 2, 0, 1, 3)/det;
	result.matrix[3][0] = -det3(1, 2, 3, 0, 1, 2)/det;
    result.matrix[3][1] =  det3(0, 2, 3, 0, 1, 2)/det;
	result.matrix[3][2] = -det3(0, 1, 3, 0, 1, 2)/det;
	result.matrix[3][3] =  det3(0, 1, 2, 0, 1, 2)/det;
	return result;
}

void Mat4::print()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout << this->matrix[i][j] << " ";
		std::cout << std::endl;
	}
}