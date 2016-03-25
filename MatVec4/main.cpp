#include "vec4.h"
#include "mat4.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include </usr/include/gtest/gtest.h>
#include <iostream>

using namespace std;

const double epsilon = 1e-06;

Vec4 vec1(2.f, 234.f, 31.f, 13.f);
glm::vec4 vec11(2.f, 234.f, 31.f, 13.f);

Vec4 vec2(21.11f, 2.223f, 31.114f, 13.4f);
glm::vec4 vec22(21.11f, 2.223f, 31.114f, 13.4f);

Mat4 mat1(Vec4(2, 234, 31, 13), 
		  Vec4(456, 4, 3, 3), 
		  Vec4(2, 4, 31, 13), 
		  Vec4(32, 12, 46, 8));

glm::mat4 mat11(glm::vec4(2, 234, 31, 13), 
				glm::vec4(456, 4, 3, 3), 
				glm::vec4(2, 4, 31, 13), 
				glm::vec4(32, 12, 46, 8));

Mat4 mat2(Vec4(41, 0, 99, 13), 
		  Vec4(4, 23, 689, 3),
		  Vec4(89, 5, 11, 231),
		  Vec4(3, 2, 56, 342));

glm::mat4 mat22(glm::vec4(41, 0, 99, 13), 
				glm::vec4(4, 23, 689, 3), 
		      	glm::vec4(89, 5, 11, 231), 
		        glm::vec4(3, 2, 56, 342));

class Vec4Test : public ::testing::Test {
};

class Mat4Test : public ::testing::Test {
};


void MY_ASSERT_EQUAL_MAT(Mat4 expected, glm::mat4 actual) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			ASSERT_FLOAT_EQ(expected.matrix[i][j], actual[i][j]);
}

void MY_ASSERT_EQUAL_VEC(Vec4 expected, glm::vec4 actual) {
	ASSERT_FLOAT_EQ(expected.x, actual.x);
	ASSERT_FLOAT_EQ(expected.y, actual.y);
	ASSERT_FLOAT_EQ(expected.z, actual.z);
	ASSERT_FLOAT_EQ(expected.w, actual.w);
}

TEST_F(Vec4Test, VEC4_CONSTRUCTOR) {
	MY_ASSERT_EQUAL_VEC(vec1, vec11);
}

TEST_F(Vec4Test, VEC4_COPY_CONSTRUCTOR) {
	ASSERT_EQ(Vec4(vec1), vec1);
	ASSERT_NE(Vec4(vec1 + 1), vec1);
}

TEST_F(Vec4Test, VEC4_ADD) {
	MY_ASSERT_EQUAL_VEC(vec1 + vec2, vec11 + vec22);
	MY_ASSERT_EQUAL_VEC(vec1 + 45.4353f, vec11 + 45.4353f);
}

TEST_F(Vec4Test, VEC4_SUB) {
	MY_ASSERT_EQUAL_VEC(vec1 - vec2, vec11 - vec22);
	MY_ASSERT_EQUAL_VEC(vec1 - 45.4353f, vec11 - 45.4353f);
}

TEST_F(Vec4Test, VEC4_MULT) {
	MY_ASSERT_EQUAL_VEC(vec1 * vec2, vec11 * vec22);
	MY_ASSERT_EQUAL_VEC(vec1 * 45.4353f, vec11 * 45.4353f);
}

TEST_F(Vec4Test, VEC4_DIV) {
	MY_ASSERT_EQUAL_VEC(vec1 / vec2, vec11 / vec22);
	MY_ASSERT_EQUAL_VEC(vec1 / 45.4353f, vec11 / 45.4353f);
}

TEST_F(Vec4Test, VEC4_LENGHT) {
	ASSERT_FLOAT_EQ(vec1.length(), glm::length(vec11));
	ASSERT_FLOAT_EQ((vec2 + 45.4353f).length(), glm::length(vec22 + 45.4353f));
}

TEST_F(Vec4Test, VEC4_NORMALIZE) {
	MY_ASSERT_EQUAL_VEC(vec1.normalize(), glm::normalize(vec11));
	MY_ASSERT_EQUAL_VEC((vec2 + 45.4353f).normalize(), glm::normalize(vec22 + 45.4353f));
}

TEST_F(Vec4Test, VEC4_NORMALIZE_IN_PLACE) {
	Vec4 vec3(vec1);
	vec3.normalize_in_place();
	MY_ASSERT_EQUAL_VEC(vec3, glm::normalize(vec11));
	Vec4 vec4(vec2 + 45.4353f);
	vec4.normalize_in_place();
	MY_ASSERT_EQUAL_VEC(vec4, glm::normalize(vec22 + 45.4353f));
}

TEST_F(Vec4Test, VEC4_DOT) {
	ASSERT_FLOAT_EQ(vec1.dot(vec2), glm::dot(vec11, vec22));
	ASSERT_FLOAT_EQ(vec1.dot(vec2 + 24.435f), glm::dot(vec11, vec22 + 24.435f));
}

TEST_F(Vec4Test, VEC4_CROSS) {
	glm::vec3 t(vec11.x, vec11.y, vec11.z);
	glm::vec3 t1(vec22.x, vec22.y, vec22.z);
	MY_ASSERT_EQUAL_VEC(vec1.cross(vec2), glm::vec4(glm::cross(t, t1), 0));
}


TEST_F(Mat4Test, MAT4_CONSTRUCTOR) {
	MY_ASSERT_EQUAL_MAT(mat1, mat11);
	MY_ASSERT_EQUAL_MAT(mat2, mat22);
}

TEST_F(Mat4Test, MAT4_COPY_CONSTRUCTOR) {
	MY_ASSERT_EQUAL_MAT(Mat4(mat1), mat11);
	MY_ASSERT_EQUAL_MAT(Mat4(mat2), mat22);
}

TEST_F(Vec4Test, MAT4_ADD) {
	MY_ASSERT_EQUAL_MAT(mat1 + mat2, mat11 + mat22);
	MY_ASSERT_EQUAL_MAT(mat1 + 45.4353f, mat11 + 45.4353f);
}

TEST_F(Vec4Test, MAT4_SUB) {
	MY_ASSERT_EQUAL_MAT(mat1 - mat2, mat11 - mat22);
	MY_ASSERT_EQUAL_MAT(mat1 - 45.4353f, mat11 - 45.4353f);
}

TEST_F(Vec4Test, MAT4_MULT) {
	MY_ASSERT_EQUAL_MAT(mat1 * 45.4353f, mat11 * 45.4353f);
}

TEST_F(Vec4Test, MAT4_DIV) {
	MY_ASSERT_EQUAL_MAT(mat1 / 45.4353f, mat11 / 45.4353f);
}

TEST_F(Vec4Test, MAT4_TRANSPOSE) {
	MY_ASSERT_EQUAL_MAT(mat1.transpose(), glm::transpose(mat11));
	MY_ASSERT_EQUAL_MAT(mat2.transpose(), glm::transpose(mat22));
}


TEST_F(Vec4Test, MAT4_DET) {
	ASSERT_NEAR(mat1.det(), glm::determinant(mat11), epsilon);
	ASSERT_NEAR(mat2.det(), glm::determinant(mat22), epsilon);
}

TEST_F(Vec4Test, MAT4_INVERSE) {
	MY_ASSERT_EQUAL_MAT(mat1.inverse(), glm::inverse(mat11));
	MY_ASSERT_EQUAL_MAT(mat2.inverse(), glm::inverse(mat22));
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
