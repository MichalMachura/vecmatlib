#ifndef VECTORTEST_HPP
#define VECTORTEST_HPP

#include <iostream>
#include <gtest/gtest.h>
#include "Vector.hpp"
#include <cmath>


TEST ( VectorTest, CreateVector_Default_TestCase1 )
	{
	using type = float;
	const unsigned size = 4;
	type value = 0.0;
	Vector<type, size> v;
	}

TEST ( VectorTest, CreateVector_FilledByNumberTheSameType_TestCase2 )
	{
	using type = float;
	const unsigned size = 4;
	type value = 5.4;
	Vector<type, size> v ( value );

	EXPECT_FLOAT_EQ ( v.x[0], value ) << "Filling constructor of vector does not give expected value at pos 0";
	EXPECT_FLOAT_EQ ( v.x[1], value ) << "Filling constructor of vector does not give expected value at pos 1";
	EXPECT_FLOAT_EQ ( v.x[2], value ) << "Filling constructor of vector does not give expected value at pos 2";
	EXPECT_FLOAT_EQ ( v.x[3], value ) << "Filling constructor of vector does not give expected value at pos 3";
	}

TEST ( VectorTest, CreateVector_FillFcn_TestCase3 )
	{
	using type = float;
	const unsigned size = 4;
	int value = 5;
	Vector<type, size> v;
	v.fill ( value );

	EXPECT_FLOAT_EQ ( v.x[0], value ) <<
									  "Filling one elem. sequence constructor of vector does not give expected value at pos 0";
	EXPECT_FLOAT_EQ ( v.x[1], value ) << "Filling one elem. sequence constructor of vector does not give 0 at pos 1";
	EXPECT_FLOAT_EQ ( v.x[2], value ) << "Filling one elem. sequence constructor of vector does not give 0 at pos 2";
	EXPECT_FLOAT_EQ ( v.x[3], value ) << "Filling one elem. sequence constructor of vector does not give 0 at pos 3";
	}

TEST ( VectorTest, CreateVector_FillByInitializer_TestCase4 )
	{
	using type = float;
	const unsigned size = 4;
	type value1 = 4.5f;
	type value2 = 7.0f;
	Vector<type, size> v {value1, value2};

	EXPECT_FLOAT_EQ ( v.x[0], type ( value1 ) ) << "Sequence constructor of vector does not give expected value at pos 0";
	EXPECT_FLOAT_EQ ( v.x[1], type ( value2 ) ) << "Sequence constructor of vector does not give expected value at pos 1";
	EXPECT_FLOAT_EQ ( v.x[2], type ( 0 ) ) 		<< "Sequence constructor of vector does not give 0 at pos 2";
	EXPECT_FLOAT_EQ ( v.x[3], type ( 0 ) ) 		<< "Sequence constructor of vector does not give 0 at pos 3";
	}

TEST ( VectorTest, AddVectors_TestCase5 )
	{
	using type = float;
	using type2 = int;
	const unsigned size = 4;
	type value1 = 4.5f;
	type value2 = 7.0f;
	type value3 = 9.0f;
	Vector<type, size> v1 {value1, value2};
	Vector<type2, size> v2;
	v2.fill ( value3 );
	Vector<type, size> v3 = v1 + v2;

	EXPECT_FLOAT_EQ ( v3.x[0], value1+value3 ) 	<< "Vector add error at pos 0";
	EXPECT_FLOAT_EQ ( v3.x[1], value2+value3 ) 	<< "Vector add error at pos 1";
	EXPECT_FLOAT_EQ ( v3.x[2], value3 ) 		<< "Vector add error at pos 2";
	EXPECT_FLOAT_EQ ( v3.x[3], value3 ) 		<< "Vector add error at pos 3";
	}

TEST ( VectorTest, SubtractVectors_TestCase6 )
	{
	using type = float;
	const unsigned size = 4;
	type value1 = 4.5f;
	type value2 = 7.0f;
	type value3 = 9.0f;
	Vector<type, size> v1 {value1, value2};
	Vector<type, size> v2;
	v2.fill ( value3 );
	Vector<type, size> v3;
	v3 = v1 - v2;

	EXPECT_FLOAT_EQ ( v3.x[0], value1-value3 ) 	<< "Vector subtract error at pos 0";
	EXPECT_FLOAT_EQ ( v3.x[1], value2-value3 ) 	<< "Vector subtract error at pos 1";
	EXPECT_FLOAT_EQ ( v3.x[2], -value3 ) 		<< "Vector subtract error at pos 2";
	EXPECT_FLOAT_EQ ( v3.x[3], -value3 ) 		<< "Vector subtract error at pos 3";
	}

TEST ( VectorTest, MultiplyVectors_TestCase7 )
	{
	using type = float;
	const unsigned size = 4;
	type value1 = 4.5f;
	type value2 = 7.0f;
	type value3 = 9.0f;
	Vector<type, size> v1 {value1, value2};
	Vector<type, size> v2;
	v2.fill ( value3 );
	Vector<type, size> v3 = v1 * v2;

	EXPECT_FLOAT_EQ ( v3.x[0], value1*value3 ) 	<< "Vector multiply error at pos 0";
	EXPECT_FLOAT_EQ ( v3.x[1], value2*value3 ) 	<< "Vector multiply error at pos 1";
	EXPECT_FLOAT_EQ ( v3.x[2], 0.0f ) 			<< "Vector multiply error at pos 2";
	EXPECT_FLOAT_EQ ( v3.x[3], 0.0f ) 			<< "Vector multiply error at pos 3";
	}

TEST ( VectorTest, AddVectorValue_TestCase8 )
	{
	using type = float;
	const unsigned size = 4;
	type value1 = 4.5f;
	type value2 = 7.0f;
	type value3 = 9.0f;
	Vector<type, size> v1 {value1, value2};
	Vector<type, size> v3 = v1 + value3;

	EXPECT_FLOAT_EQ ( v3.x[0], value1+value3 ) 	<< "Vector+value error at pos 0";
	EXPECT_FLOAT_EQ ( v3.x[1], value2+value3 ) 	<< "Vector+value error at pos 1";
	EXPECT_FLOAT_EQ ( v3.x[2], value3 ) 		<< "Vector+value error at pos 2";
	EXPECT_FLOAT_EQ ( v3.x[3], value3 ) 		<< "Vector+value error at pos 3";
	}

TEST ( VectorTest, SubtractVectorValue_TestCase9 )
	{
	using type = float;
	const unsigned size = 4;
	type value1 = 4.5f;
	type value2 = 7.0f;
	type value3 = 9.0f;
	Vector<type, size> v1 {value1, value2};
	Vector<type, size> v3 = v1 - value3;

	EXPECT_FLOAT_EQ ( v3.x[0], value1-value3 ) 	<< "Vector-value error at pos 0";
	EXPECT_FLOAT_EQ ( v3.x[1], value2-value3 ) 	<< "Vector-value error at pos 1";
	EXPECT_FLOAT_EQ ( v3.x[2], -value3 ) 		<< "Vector-value error at pos 2";
	EXPECT_FLOAT_EQ ( v3.x[3], -value3 ) 		<< "Vector-value error at pos 3";
	}

TEST ( VectorTest, MultiplyVectorValue_TestCase10 )
	{
	using type = float;
	const unsigned size = 4;
	type value1 = 4.5f;
	type value2 = 7.0f;
	type value3 = 9.0f;
	Vector<type, size> v1 {value1, value2};
	Vector<type, size> v3 = v1 * value3;

	EXPECT_FLOAT_EQ ( v3.x[0], value1*value3 ) 	<< "Vector*value error at pos 0";
	EXPECT_FLOAT_EQ ( v3.x[1], value2*value3 ) 	<< "Vector*value error at pos 1";
	EXPECT_FLOAT_EQ ( v3.x[2], 0.0f*value3 ) 	<< "Vector*value error at pos 2";
	EXPECT_FLOAT_EQ ( v3.x[3], 0.0f*value3 ) 	<< "Vector*value error at pos 3";
	}

TEST ( VectorTest, DivideVectorValue_TestCase11 )
	{
	using type = float;
	const unsigned size = 4;
	type value1 = 4.5f;
	type value2 = 7.0f;
	type value3 = 9.0f;
	Vector<type, size> v1 {value1, value2};
	Vector<type, size> v3 = v1 / value3;

	EXPECT_FLOAT_EQ ( v3.x[0], value1/value3 ) 	<< "Vector/value error at pos 0";
	EXPECT_FLOAT_EQ ( v3.x[1], value2/value3 ) 	<< "Vector/value error at pos 1";
	EXPECT_FLOAT_EQ ( v3.x[2], 0.0f/value3 )	<< "Vector/value error at pos 2";
	EXPECT_FLOAT_EQ ( v3.x[3], 0.0f/value3 ) 	<< "Vector/value error at pos 3";

	EXPECT_THROW ( v1 / 0.0, std::exception ) << "Dividing vector by 0.0 does not throw.";
	}

TEST ( VectorTest, AddValueVector_TestCase12 )
	{
	using type = float;
	const unsigned size = 4;
	type value1 = 4.5f;
	type value2 = 7.0f;
	type value3 = 9.0f;
	Vector<type, size> v1 {value1, value2};
	Vector<type, size> v3 = value3 + v1;

	EXPECT_FLOAT_EQ ( v3.x[0], value1+value3 ) 	<< "value+Vector error at pos 0";
	EXPECT_FLOAT_EQ ( v3.x[1], value2+value3 ) 	<< "value+Vector error at pos 1";
	EXPECT_FLOAT_EQ ( v3.x[2], value3 ) 		<< "value+Vector error at pos 2";
	EXPECT_FLOAT_EQ ( v3.x[3], value3 ) 		<< "value+Vector error at pos 3";
	}

TEST ( VectorTest, SubtractValueVector_TestCase13 )
	{
	using type = float;
	const unsigned size = 4;
	type value1 = 4.5f;
	type value2 = 7.0f;
	type value3 = 9.0f;
	Vector<type, size> v1 {value1, value2};
	Vector<type, size> v3 = value3 - v1;

	EXPECT_FLOAT_EQ ( v3.x[0], value3 - value1 ) 	<< "value-Vector error at pos 0";
	EXPECT_FLOAT_EQ ( v3.x[1], value3 - value2 ) 	<< "value-Vector error at pos 1";
	EXPECT_FLOAT_EQ ( v3.x[2], value3 ) 			<< "value-Vector error at pos 2";
	EXPECT_FLOAT_EQ ( v3.x[3], value3 ) 			<< "value-Vector error at pos 3";
	}

TEST ( VectorTest, MultiplyValueVector_TestCase14 )
	{
	using type = float;
	const unsigned size = 4;
	type value1 = 4.5f;
	type value2 = 7.0f;
	type value3 = 9.0f;
	Vector<type, size> v1 {value1, value2};
	Vector<type, size> v3 = value3 * v1;

	EXPECT_FLOAT_EQ ( v3.x[0], value1*value3 ) 	<< "Vector*value error at pos 0";
	EXPECT_FLOAT_EQ ( v3.x[1], value2*value3 ) 	<< "Vector*value error at pos 1";
	EXPECT_FLOAT_EQ ( v3.x[2], 0.0f*value3 ) 	<< "Vector*value error at pos 2";
	EXPECT_FLOAT_EQ ( v3.x[3], 0.0f*value3 ) 	<< "Vector*value error at pos 3";
	}


TEST ( VectorTest, VectorNorm_TestCase15 )
	{
	using type = float;
	const unsigned size = 3;
	Vector<type, size> v1 {1, 0, 0};
	Vector<type, size> v2{0, 1, 0};
	Vector<type, size> v3{0, 0, 1};
	Vector<type, size> v4 = v1+v2+v3;

	EXPECT_FLOAT_EQ ( v1.norm(), 1.0f ) 	<< "Norm error";
	EXPECT_FLOAT_EQ ( v2.norm(), 1.0f ) 	<< "Norm error";
	EXPECT_FLOAT_EQ ( v3.norm(), 1.0f )		<< "Norm error";
	EXPECT_FLOAT_EQ ( v4.norm(), std::sqrt ( 3.0f ) ) 	<< "Norm error";
	}

TEST ( VectorTest, VectorSum_TestCase16 )
	{
	using type = float;
	const unsigned size = 3;
	Vector<type, size> v1 {1, 0, 0};
	Vector<type, size> v2{0, 1, 0};
	Vector<type, size> v3{0, 0, 1};
	Vector<type, size> v4 = v1+v2+v3;

	EXPECT_FLOAT_EQ ( Container::sum ( v1 ), 1.0f ) 	<< "Sum error";
	EXPECT_FLOAT_EQ ( Container::sum ( v2 ), 1.0f ) 	<< "Sum error";
	EXPECT_FLOAT_EQ ( Container::sum ( v3 ), 1.0f )	<< "Sum error";
	EXPECT_FLOAT_EQ ( Container::sum ( v4 ), 3.0f ) 	<< "Sum error";
	}

TEST ( VectorTest, VectorMul_TestCase17 )
	{
	using type = float;
	const unsigned size = 3;
	Vector<type, size> v1 {1, 0, 0};
	Vector<type, size> v2{0, 1, 0};
	Vector<type, size> v3{0, 0, 1};
	Vector<type, size> v4 = v1+v2+v3;

	EXPECT_FLOAT_EQ ( Container::mul ( v1 ), 0.0f ) 	<< "Mul error";
	EXPECT_FLOAT_EQ ( Container::mul ( v2 ), 0.0f ) 	<< "Mul error";
	EXPECT_FLOAT_EQ ( Container::mul ( v3 ), 0.0f )	<< "Mul error";
	EXPECT_FLOAT_EQ ( Container::mul ( v4 ), 1.0f ) 	<< "Mul error";
	}

TEST ( VectorTest, VectorDot_TestCase18 )
	{
	using type = float;
	const unsigned size = 3;
	Vector<type, size> v1 {1, 0, 0};
	Vector<type, size> v2{0, 1, 0};
	Vector<type, size> v3{0, 0, 1};
	Vector<type, size> v4 = v1+v2+v3;
	Vector<type, size> v5 = v4+v4;

	EXPECT_FLOAT_EQ ( v1.dot ( v1 ), 1.0f ) 	<< "Dot product error";
	EXPECT_FLOAT_EQ ( v1.dot ( v2 ), 0.0f ) 	<< "Dot product error";
	EXPECT_FLOAT_EQ ( v2.dot ( v1 ), 0.0f ) 	<< "Dot product error";
	EXPECT_FLOAT_EQ ( v3.dot ( v2 ), 0.0f )		<< "Dot product error";
	EXPECT_FLOAT_EQ ( v3.dot ( v1 ), 0.0f )		<< "Dot product error";
	EXPECT_FLOAT_EQ ( v4.dot ( v1 ), 1.0f ) 	<< "Dot product error";
	EXPECT_FLOAT_EQ ( v4.dot ( v2 ), 1.0f ) 	<< "Dot product error";
	EXPECT_FLOAT_EQ ( v4.dot ( v3 ), 1.0f ) 	<< "Dot product error";
	EXPECT_FLOAT_EQ ( v4.dot ( v4 ), 3.0f ) 	<< "Dot product error";
	EXPECT_FLOAT_EQ ( v5.dot ( v4 ), 6.0f ) 	<< "Dot product error";
	EXPECT_FLOAT_EQ ( v5.dot ( v5 ), 12.0f ) 	<< "Dot product error";
	}

TEST ( VectorTest, CreateVector_FromAnotherVectorOfDifferentSize_TestCase19 )
	{
	using type = float;
	using type2 = double;
	const unsigned size = 4;
	const unsigned size2 = 2;
	Vector<type2, size2> v1{2.4f, -3.6f};
	Vector<type, size> v2 ( v1, 1.0f );

	EXPECT_FLOAT_EQ ( v2.x[0], 2.4f ) << "Constructor from another smaller vector error";
	EXPECT_FLOAT_EQ ( v2.x[1], -3.6f ) << "Constructor from another smaller vector error";
	EXPECT_FLOAT_EQ ( v2.x[2], 1.0f ) << "Constructor from another smaller vector error";
	EXPECT_FLOAT_EQ ( v2.x[3], 1.0f ) << "Constructor from another smaller vector error";
	}

TEST ( VectorTest, Vector_ContainerOperations_DifferentTypes_TestCase20 )
	{
	using type = float;
	using type2 = double;
	const unsigned size = 4;
	Vector<type2, size> v1{2.4f, -3.6f};
	Vector<type, size> v2 ( 1.0f );
	Vector<int, size> v3;
	Container::executeContainersOperation<Add> ( v1, v2, v3 );

	for ( unsigned i=0; i < v3.size(); ++i )
		EXPECT_EQ ( v3.x[i], int ( v1.x[i] +v2.x[i] ) );
	}

TEST ( VectorTest, VectorAddAssign_DifferentTypes_TestCase21 )
	{
	using type = float;
	using type2 = double;
	const unsigned size = 4;
	type2 value = 3.0;
	Vector<type2, size> v1{2.4f, -3.6f};
	Vector<type, size> v2_aux ( 1.0f );
	Vector<type, size> v2 = v2_aux;
	Vector<type, size> v3 = v2_aux;
	v2 += v1;
	v3 += value;

	for ( unsigned i=0; i < v3.size(); ++i )
		{
		EXPECT_FLOAT_EQ ( v2.x[i], float ( v2_aux.x[i] + v1.x[i] ) ) << "Error += Vector";
		EXPECT_FLOAT_EQ ( v3.x[i], float ( v2_aux.x[i] + value ) ) << "Error += value";
		}
	}

TEST ( VectorTest, VectorSubtractAssign_DifferentTypes_TestCase22 )
	{
	using type = float;
	using type2 = double;
	const unsigned size = 4;
	type2 value = 3.0;
	Vector<type2, size> v1{2.4f, -3.6f};
	Vector<type, size> v2_aux ( 1.0f );
	Vector<type, size> v2 = v2_aux;
	Vector<type, size> v3 = v2_aux;
	v2 -= v1;
	v3 -= value;

	for ( unsigned i=0; i < v3.size(); ++i )
		{
		EXPECT_FLOAT_EQ ( v2.x[i], float ( v2_aux.x[i] - v1.x[i] ) ) 	<< "Error -= Vector";
		EXPECT_FLOAT_EQ ( v3.x[i], float ( v2_aux.x[i] - value ) ) 		<< "Error -= value";
		}
	}

TEST ( VectorTest, VectorMultiplyAssign_DifferentTypes_TestCase23 )
	{
	using type = float;
	using type2 = double;
	const unsigned size = 4;
	type2 value = 3.0;
	Vector<type2, size> v1{2.4f, -3.6f};
	Vector<type, size> v2_aux ( 1.0f );
	Vector<type, size> v2 = v2_aux;
	Vector<type, size> v3 = v2_aux;
	v2 *= v1;
	v3 *= value;

	for ( unsigned i=0; i < v3.size(); ++i )
		{
		EXPECT_FLOAT_EQ ( v2.x[i], float ( v2_aux.x[i] * v1.x[i] ) ) 	<< "Error *= Vector";
		EXPECT_FLOAT_EQ ( v3.x[i], float ( v2_aux.x[i] * value ) ) 		<< "Error *= value";
		}
	}

TEST ( VectorTest, VectorDivideAssign_DifferentTypes_TestCase24 )
	{
	using type = float;
	using type2 = double;
	const unsigned size = 4;
	type2 value = 3.0;
	Vector<type2, size> v1{2.4f, -3.6f};
	Vector<type, size> v2_aux ( 1.0f );
	Vector<type, size> v2 = v2_aux;
	v2 /= value;

	for ( unsigned i=0; i < v2.size(); ++i )
		{
		EXPECT_FLOAT_EQ ( v2.x[i], float ( v2_aux.x[i] / value ) ) 		<< "Error /= value";
		}
	}


TEST ( VectorTest, AccessOperators_TestCase25 )
	{
	using type = float;
	const unsigned size = 4;
	type value = 3.0;
	Vector<type, size> v1{0, 3, 4, 5};

	for ( unsigned i=0; i < v1.size(); ++i )
		{
		EXPECT_FLOAT_EQ ( v1.x[i], v1.get ( i ) )	<< "Error get()";
		EXPECT_FLOAT_EQ ( v1.x[i], v1[i] )	<< "Error operator[]";
		v1.set ( i, value );
		EXPECT_FLOAT_EQ ( v1.x[i], value )	<< "Error set()";
		EXPECT_FLOAT_EQ ( v1.get ( i ), value )	<< "Error get()";
		EXPECT_FLOAT_EQ ( v1[i], value )	<< "Error operator[]";
		}
	}


#endif // VECTORTEST_HPP