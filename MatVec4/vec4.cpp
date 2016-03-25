#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include "vec4.h"

using namespace std;

Vec4::Vec4(const Vec4 &v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = v.w;
}

Vec4 Vec4::operator+(const Vec4& b) const
{
	return Vec4(this->x + b.x, this->y + b.y, this->z + b.z, this->w + b.w);
}

Vec4 Vec4::operator+(const int& b) const
{
	return Vec4(this->x + b, this->y + b, this->z + b, this->w + b);
}

Vec4 Vec4::operator+(const float& b) const
{
	return Vec4(this->x + b, this->y + b, this->z + b, this->w + b);
}

Vec4 Vec4::operator-(const Vec4& b) const
{
	return Vec4(this->x - b.x, this->y - b.y, this->z - b.z, this->w - b.w);
}

Vec4 Vec4::operator-(const int& b) const
{
	return Vec4(this->x - b, this->y - b, this->z - b, this->w - b);
}

Vec4 Vec4::operator-(const float& b) const
{
	return Vec4(this->x - b, this->y - b, this->z - b, this->w - b);
}

Vec4 Vec4::operator*(const Vec4& b) const
{
	return Vec4(this->x * b.x, this->y * b.y, this->z * b.z, this->w * b.w);
}

Vec4 Vec4::operator*(const int& b) const
{
	return Vec4(this->x * b, this->y * b, this->z * b, this->w * b);
}

Vec4 Vec4::operator*(const float& b) const
{
	return Vec4(this->x * b, this->y * b, this->z * b, this->w * b);
}

Vec4 Vec4::operator/(const Vec4& b) const
{
	return Vec4(this->x / b.x, this->y / b.y, this->z / b.z, this->w / b.w);
}
	
Vec4 Vec4::operator/(const float& b) const
{
	return Vec4(this->x / b, this->y / b, this->z / b, this->w / b);
}

Vec4& Vec4::operator=(Vec4 &v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = v.w;
}

bool Vec4::operator==(const Vec4 &v) const
{
	if (this->x != v.x || this->y != v.y || this->z != v.z || this->w != v.w) return false;
	return true;
}

bool Vec4::operator!=(const Vec4 &v) const
{
	if (this->x != v.x || this->y != v.y || this->z != v.z || this->w != v.w) return true;
	return false;
}

float Vec4::length() const { return sqrt(x*x + y*y + z*z + w*w); } 

Vec4 Vec4::normalize()
{
	float l = length();
	return l > 0 ? (Vec4(x/l, y/l, z/l, w/l)) : (Vec4());
};

void Vec4::normalize_in_place()
{
	float l = length();
	if (l > 0){ x /= l; y /= l; z /= l; w/= l; }
};

float Vec4::dot(Vec4 b)
{
	return (this->x * b.x + this->y * b.y + this->z * b.z + this->w * b.w);
};

Vec4 Vec4::cross(Vec4 b)
{
	return Vec4(this->y * b.z - this->z * b.y, this->z * b.x - 
				this->x * b.z, this->x * b.y - this->y * b.x);
};
