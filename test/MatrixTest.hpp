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
	Matrix<type, rows, cols> M;

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
	Matrix<type, rows, cols> M;

	EXPECT_FLOAT_EQ ( M.sum(), 16.0f ) << "Error sum.";
	}

TEST ( MatrixTest, Matrix_ElementsMultiplication_TestCase8 )
	{
	using type = float;
	const unsigned rows = 4;
	const unsigned cols = 4;
	Matrix<type, rows, cols> M;

	EXPECT_FLOAT_EQ ( M.mul(), 0.0f ) << "Error mul.";
	}




#endif // MATRIXTEST_HPP