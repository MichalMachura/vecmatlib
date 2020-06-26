#include <iostream>
#include <gtest/gtest.h>

#include "VectorTest.hpp"
#include "MatrixTest.hpp"
#include "MatrixVectorTest.hpp"

int main ( int argn, char* args[] )
	{
	// initialize Google Test
	testing::InitGoogleTest();// ( &argn, args );
	// execute tests
	return RUN_ALL_TESTS();;
	}