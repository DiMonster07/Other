#pragma once
#include "vec4.h"

using namespace std;

class Mat4
{
public:
	float matrix[4][4];
	Mat4(float x11 = 1, float x12 = 0, float x13 = 0, float x14 = 0, 
		 float x21 = 0, float x22 = 1, float x23 = 0, float x24 = 0, 
		 float x31 = 0, float x32 = 0, float x33 = 1, float x34 = 0,
		 float x41 = 0, float x42 = 0, float x43 = 0, float x44 = 1);
	Mat4(Vec4 v1, Vec4 v2, Vec4 v3, Vec4 v4);
	Mat4(const Mat4 &v);
	Mat4 operator+(Mat4& b);
	Mat4 operator+(const int& b);
	Mat4 operator+(const float& b);
	Mat4 operator-(Mat4& b);
	Mat4 operator-(const int& b);
	Mat4 operator-(const float& b);
	Mat4 operator*(Mat4& b);
	Mat4 operator*(const int& b);
	Mat4 operator*(const float& b);
	Mat4 operator/(const float& b);
	bool operator==(const Mat4 &v) const;
	bool operator!=(const Mat4 &v) const;
	Mat4 transpose ();
	float det2(int c1, int c2, int r1, int r2);
	float det3(int r1, int r2, int r3, int c1, int c2, int c3);
	float det();
	Mat4 inverse();
	void print();
};
