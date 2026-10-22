#include "tmatrix.h"

#include <gtest/gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 1; m[0][1] = 2;
	m[1][0] = 3; m[1][1] = 4;

	TDynamicMatrix<int> m1(m);

	EXPECT_TRUE(m == m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 1; m[0][1] = 2;
	m[1][0] = 3; m[1][1] = 4;

	TDynamicMatrix<int> m1(m);
	m1[0][0] = 100; m1[1][1] = 200;

	EXPECT_EQ(1, m[0][0]);
	EXPECT_EQ(2, m[0][1]);
	EXPECT_EQ(3, m[1][0]);
	EXPECT_EQ(4, m[1][1]);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(5);
	EXPECT_EQ(5, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(3);
	m[1][2] = 7;

	EXPECT_EQ(7, m[1][2]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(4);
	ASSERT_ANY_THROW(m[0].at(-1));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(4);
	ASSERT_ANY_THROW(m[0].at(m[0].size()));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 1; m[0][1] = 2;
	m[1][0] = 3; m[1][1] = 4;

	m = m;

	EXPECT_EQ(1, m[0][0]);
	EXPECT_EQ(2, m[0][1]);
	EXPECT_EQ(3, m[1][0]);
	EXPECT_EQ(4, m[1][1]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> a(2), b(2);
	a[0][0] = 1; a[0][1] = 2;
	a[1][0] = 3; a[1][1] = 4;

	b[0][0] = 10; b[0][1] = 20;
	b[1][0] = 30; b[1][1] = 40;

	a = b;

	EXPECT_EQ(10, a[0][0]);
	EXPECT_EQ(20, a[0][1]);
	EXPECT_EQ(30, a[1][0]);
	EXPECT_EQ(40, a[1][1]);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m(2), m1(3);

	m = m1;

	EXPECT_EQ(3, m[0].size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m(2), m1(3);
	m[0][0] = 1; m[0][1] = 2;
	m[1][0] = 3; m[1][1] = 4;

	m1[0][0] = 10; m1[0][1] = 20; m1[0][2] = 30;
	m1[1][0] = 40; m1[1][1] = 50; m1[1][2] = 60;
	m1[2][0] = 70; m1[2][1] = 80; m1[2][2] = 90;

	m = m1;

	ASSERT_EQ(3, m[0].size());
	EXPECT_EQ(10, m[0][0]);
	EXPECT_EQ(20, m[0][1]);
	EXPECT_EQ(30, m[0][2]);
	EXPECT_EQ(90, m[2][2]);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> a(2), b(2);
	a[0][0] = 1; a[0][1] = 2;
	a[1][0] = 3; a[1][1] = 4;

	b[0][0] = 1; b[0][1] = 2;
	b[1][0] = 3; b[1][1] = 4;

	EXPECT_TRUE(a == b);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 1; m[0][1] = 2;
	m[1][0] = 3; m[1][1] = 4;

	EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> a(2), b(3);

	EXPECT_FALSE(a == b);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> a(2), b(2);
	a[0][0] = 1; a[0][1] = 2;
	a[1][0] = 3; a[1][1] = 4;

	b[0][0] = 10; b[0][1] = 20;
	b[1][0] = 30; b[1][1] = 40;

	TDynamicMatrix<int> c = a + b;

	EXPECT_EQ(11, c[0][0]);
	EXPECT_EQ(22, c[0][1]);
	EXPECT_EQ(33, c[1][0]);
	EXPECT_EQ(44, c[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> a(2), b(3);
	ASSERT_ANY_THROW(a + b);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> a(2), b(2);
	a[0][0] = 10; a[0][1] = 20;
	a[1][0] = 30; a[1][1] = 40;

	b[0][0] = 1; b[0][1] = 2;
	b[1][0] = 3; b[1][1] = 4;

	TDynamicMatrix<int> c = a - b;

	EXPECT_EQ(9, c[0][0]);
	EXPECT_EQ(18, c[0][1]);
	EXPECT_EQ(27, c[1][0]);
	EXPECT_EQ(36, c[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> a(2), b(3);
	ASSERT_ANY_THROW(a - b);
}

