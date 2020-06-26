#ifndef MATRIXTEST_HPP
#define MATRIXTEST_HPP

#include "Matrix.hpp"
#include <gtest/gtest.h>
#include <sstream>

TEST ( MatrixTest, MatrixCreate_DefaultConstructor_TestCase1 )
	{
	using type = float;
	const unsigned rows = 4;
	const unsigned cols = 4;
	Matrix<type, rows, cols> M;
	}

TEST ( MatrixTest, MatrixIterator_TestCase2 )
	{
	using type = float;
	const unsigned rows = 4;
	const unsigned cols = 4;
	Matrix<type, rows, cols> M;
	type* it_beg = M.begin();
	type const* it_end = M.end();
	unsigned counter = 0;

	while ( it_beg++ != it_end )
		++counter;

	EXPECT_EQ ( counter, rows*cols ) << "Iteration error.";
	}


TEST ( MatrixTest, MatrixCreate_FillConstructor_TestCase4 )
	{
	using type = float;
	const unsigned rows = 4;
	const unsigned cols = 4;
	Matrix<type, rows, cols> M ( 1 );

	EXPECT_FLOAT_EQ ( M ( 0, 0 ), 1.0f ) << "Error fill.";
	}

TEST ( MatrixTest, Matrix_ParentesisOperators_TestCase5 )
	{
	using type = float;
	const unsigned rows = 4;
	const unsigned cols = 4;
	Matrix<type, rows, cols> M;

	EXPECT_FLOAT_EQ ( M ( 1, 2 ), M.x[1][2] ) << "Error operator()(unsigned, unsigned)";
	EXPECT_FLOAT_EQ ( M ( 3 ), M.x[0][3] ) << "Error operator()(unsigned)";
	}


TEST ( MatrixTest, Matrix_GetSize_TestCase6 )
	{
	using type = float;
	const unsigned rows = 4;
	const unsigned cols = 4;
	Matrix<type, rows, cols> M;

	EXPECT_EQ ( M .size(), rows*cols ) << "Error get size";
	EXPECT_EQ ( M .size(), M.rows*M.cols ) << "Error get size";
	}

TEST ( MatrixTest, Matrix_ElementsSum_TestCase7 )
	{
	using type = float;
	const unsigned rows = 4;
	const unsigned cols = 4;
	Matrix<type, rows, cols> M ( 1.0f );

	EXPECT_FLOAT_EQ ( Container::sum ( M ), 16.0f ) << "Error sum.";
	}

TEST ( MatrixTest, Matrix_ElementsMultiplication_TestCase8 )
	{
	using type = float;
	const unsigned rows = 4;
	const unsigned cols = 4;
	Matrix<type, rows, cols> M ( 1.0f );

	EXPECT_FLOAT_EQ ( Container::mul ( M ), 1.0f ) << "Error mul.";
	}

TEST ( MatrixTest, Matrix_Add_TestCase9 )
	{
	using type = float;
	using type2 = double;
	const unsigned rows = 4;
	const unsigned cols = 4;
	type2 value = 5.4;
	Matrix<type, rows, cols> M1 ( 1.0f );
	Matrix<type2, rows, cols> M2 ( 1.0f );
	Matrix<type, rows, cols> M3;

	M3 = M1+M2;
	for ( type v : M3 )
		EXPECT_FLOAT_EQ ( v, 2.0f ) << "Error M1+M2";

	M3 += M1+M2;
	for ( type v : M3 )
		EXPECT_FLOAT_EQ ( v, 4.0f ) << "Error M3 += M1+M2";

	M3 = M1 + value;
	for ( type v : M3 )
		EXPECT_FLOAT_EQ ( v, 6.4f ) << "Error M3 = M1 + value";

	M3 = value + M1;
	for ( type v : M3 )
		EXPECT_FLOAT_EQ ( v, 6.4f ) << "Error M3 = value + M1";

	M3 += value;
	for ( type v : M3 )
		EXPECT_FLOAT_EQ ( v, 11.8f ) << "Error M3 += value";
	}

TEST ( MatrixTest, Matrix_Subtract_TestCase10 )
	{
	using type = float;
	using type2 = double;
	const unsigned rows = 4;
	const unsigned cols = 4;
	type2 value = 5.4;
	Matrix<type, rows, cols> M1 ( 1.0f );
	Matrix<type2, rows, cols> M2 ( 1.0f );
	Matrix<type, rows, cols> M3;

	M3 = M1 - M2;
	for ( type v : M3 )
		EXPECT_FLOAT_EQ ( v, 0.0f ) << "Error M1-M2";

	M3 -= M2;
	for ( type v : M3 )
		EXPECT_FLOAT_EQ ( v, -1.0f ) << "Error M3 -= M2";

	M3 = M1 - value;
	for ( type v : M3 )
		EXPECT_FLOAT_EQ ( v, -4.4f ) << "Error M3 = M1 - value";

	M3 = value - M1;
	for ( type v : M3 )
		EXPECT_FLOAT_EQ ( v, 4.4f ) << "Error M3 = value - M1";

	M3 -= value;
	for ( type v : M3 )
		EXPECT_FLOAT_EQ ( v, -1.0f ) << "Error M3 -= value";
	}

TEST ( MatrixTest, Matrix_Multiply_TestCase11 )
	{
	using type = float;
	using type2 = double;
	const unsigned rows = 4;
	const unsigned cols = 4;
	type2 value = 5.4;
	Matrix<type, rows, cols> M1 ( 3.0f );
	Matrix<type2, rows, cols> M2 ( 2.0f );
	Matrix<type, rows, cols> M3;

	M3 = M1.hadamardProduct ( M2 );
	for ( type v : M3 )
		EXPECT_FLOAT_EQ ( v, 6.0f ) << "Error M1*M2";

	M3.hadamardProductAssign ( M1.hadamardProduct ( M2 ) );
	for ( type v : M3 )
		EXPECT_FLOAT_EQ ( v, 36.0f ) << "Error M3 *= M1*M2";

	M3 = M1 * value;
	for ( type v : M3 )
		EXPECT_FLOAT_EQ ( v, 16.2f ) << "Error M3 = M1*value";

	M3 = value * M1;
	for ( type v : M3 )
		EXPECT_FLOAT_EQ ( v, 16.2f ) << "Error M3 = value*M1";

	M3 *= value;
	for ( type v : M3 )
		EXPECT_FLOAT_EQ ( v, 16.2f*value ) << "Error M3 *= value";
	}

TEST ( MatrixTest, Matrix_Divide_TestCase12 )
	{
	using type = float;
	using type2 = double;
	const unsigned rows = 4;
	const unsigned cols = 4;
	type2 value = 5.4;
	Matrix<type, rows, cols> M1 ( 6.0f );
	Matrix<type, rows, cols> M3;

	M3 = M1 / value;
	for ( type v : M3 )
		EXPECT_FLOAT_EQ ( v, type ( 6.0f/value ) ) << "Error M3 += value";

	M3 /= value;
	for ( type v : M3 )
		EXPECT_FLOAT_EQ ( v, type ( type ( 6.0f/value )/value ) ) << "Error M3 += value";
	}


TEST ( MatrixTest, Matrix_Iteration_TestCase13 )
	{
	using type = float;
	const unsigned rows = 4;
	const unsigned cols = 4;
	Matrix<type, rows, cols> M;
	auto it_beg = M.begin();
	auto it_end = M.end();

	for ( unsigned i = 0; i < M.rows; ++i )
		{
		auto it_row_beg = M.begin ( i );
		auto it_row_end = M.end ( i );

		for ( unsigned j = 0; j < M.cols; ++j )
			{
			EXPECT_FLOAT_EQ ( *it_row_beg++, M ( i, j ) ) << "Error iterator row.";
			EXPECT_FLOAT_EQ ( *it_beg++, M ( i, j ) ) << "Error iterator.";
			EXPECT_FLOAT_EQ ( M.x[i][j], M ( i, j ) ) << "Error operator[].";
			}
		EXPECT_EQ ( it_row_beg, it_row_end ) << "Error iterator row.";
		}

	EXPECT_EQ ( it_beg, it_end ) << "Error iterator.";
	}
TEST ( MatrixTest, Eye_TestCase14 )
	{
	using type = int;
	const unsigned rows = 3;
	const unsigned cols = 3;
	Matrix<type, rows, cols> M1;
	Matrix<type, rows, cols> M2{1, 0, 0, 0, 1, 0, 0, 0, 1};
	eye ( M1 );
	auto it_beg1 = M1.begin();
	auto it_end1 = M1.end();
	auto it_beg2 = M2.begin();

	//std::cout << M1 << std::endl;

	while ( it_beg1 != it_end1 )
		EXPECT_EQ ( *it_beg1++, *it_beg2++ ) << "Error eye.";

	}


#endif // MATRIXTEST_HPP