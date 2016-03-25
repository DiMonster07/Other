#pragma once

using namespace std;

class Vec4
{
public:
	float x, y, z, w;
	Vec4(float _x = 0, float _y = 0, float _z = 0, float _w = 0) 
		: x(_x), y(_y), z(_z), w(_w){};
	Vec4(const Vec4 &v);
	Vec4 operator+(const Vec4& b) const;
	Vec4 operator+(const int& b) const;
	Vec4 operator+(const float& b) const;
	Vec4 operator-(const Vec4& b) const;
	Vec4 operator-(const int& b) const;
	Vec4 operator-(const float& b) const;
	Vec4 operator*(const Vec4& b) const;
	Vec4 operator*(const int& b) const;
	Vec4 operator*(const float& b) const;
	Vec4 operator/(const Vec4& b) const;
	Vec4 operator/(const float& b) const;
	Vec4& operator=(Vec4 &v);
    bool operator==(const Vec4 &v) const;
    bool operator!=(const Vec4 &v) const;
	float length () const;
	Vec4 normalize ();
	void normalize_in_place ();
	float dot(Vec4 b);
	Vec4 cross(Vec4 b);
};