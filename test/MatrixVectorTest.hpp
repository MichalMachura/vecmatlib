#ifndef MATRIXVECTOR_HPP
#define MATRIXVECTOR_HPP

#include <gtest/gtest.h>
#include "Utility.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"


TEST ( MatrixVectorTest, VectorFromMatrix_TestCase1 )
	{
	using type = int;
	const unsigned rows = 5;
	const unsigned cols = 1;
	Matrix<type, rows, cols> M{1, 2, 3, 4};
	Vector<type, rows> v ( M );
	auto it1_beg = M.begin();
	auto it1_end = M.end();
	auto it2_beg = v.begin();

	while ( it1_beg != it1_end )
		EXPECT_EQ ( *it1_beg++, *it2_beg++ ) << "Error in creating Vector from Matrix";
	}


TEST ( MatrixVectorTest, MatricesMultiplication_CauchyProduct_TestCase2 )
	{
	using type = int;
	const unsigned rows = 2;
	const unsigned cols = 2;
	Matrix<type, rows, cols> M1{1, 2, 3, 4};
	Matrix<type, rows, cols> M2{5, 6, 7, 8};
	Matrix<type, rows, cols> M3{5+14, 6+16, 15+28, 18+32 };
	Matrix<type, rows, cols> M4 = M1*M2;
	auto it3_beg = M3.begin();
	auto it4_beg = M4.begin();
	auto it3_end = M3.end();
	auto it4_end = M4.end();

	while ( it3_beg != it3_end )
		EXPECT_EQ ( *it3_beg++, *it4_beg++ ) << "Error in Matrix multiplication M3 = M1*M2";

	M4 = M1;
	M4 *= M2;
	it3_beg = M3.begin();
	it4_beg = M4.begin();
	while ( it3_beg != it3_end )
		EXPECT_EQ ( *it3_beg++, *it4_beg++ ) << "Error in Matrix multiplication (M4=M1) *= M2";
	}

TEST ( MatrixVectorTest, MatrixVectorMultiplication_CauchyProduct_TestCase3 )
	{
	using type = int;
	const unsigned rows = 2;
	const unsigned cols = 2;
	Matrix<type, rows, cols> M1{1, 2, 3, 4};
	Vector<type, rows> v2 {2, 3};
	Vector<type, rows> v3;
	Vector<type, rows> v4{8, 18};
	auto it3_beg = v3.begin();
	auto it3_end = v3.end();
	auto it4_beg = v4.begin();

	v3 = M1*v2;

	while ( it3_beg != it3_end )
		EXPECT_EQ ( *it3_beg++, *it4_beg++ ) << "Error in v3 = M1*v2";
	}

TEST ( MatrixVectorTest, VectorMatrixMultiplication_CauchyProduct_TestCase4 )
	{
	using type = int;
	const unsigned rows = 2;
	const unsigned cols = 2;
	Matrix<type, 1, cols> M1{1, 2};
	Vector<type, rows> v2 {2, 3};
	Matrix<type, rows, cols> M3;
	Matrix<type, rows, cols> M4{2, 4, 3, 6};

	auto it3_beg = M3.begin();
	auto it3_end = M3.end();
	auto it4_beg = M4.begin();

	M3 = v2*M1;

	while ( it3_beg != it3_end )
		EXPECT_EQ ( *it3_beg++, *it4_beg++ ) << "Error in M3 = v2*M1";
	}

#endif // MATRIXVECTOR_HPP