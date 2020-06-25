#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <type_traits>
#include <initializer_list>
#include <cassert>
#include <cmath>
#include <ostream>
#include <iomanip>
#include <exception>

#include "Utility.hpp"
#include "Vector.hpp"

template<typename T, unsigned ROWS=3, unsigned COLS=3>
class Matrix
	{
	public:
		static const unsigned rows = ROWS;
		static const unsigned cols = COLS;
		static const unsigned length = ROWS*COLS;

	public:
		T x[ROWS][COLS];

	public:
		/**
		 * @brief Matrix default constructor
		 *
		 */
		Matrix()
			{
			}

		/**
		 * @brief Matrix filling constructor
		 *
		 * @param value value to fill in the matrix
		 */
		Matrix ( T* value )
			{

			}

		/**
		 * @brief Return forward iterator to first element
		 *
		 * @return T*
		 */
		inline T* begin() const
			{
			return const_cast<T*> ( *x );
			}

		/**
		 * @brief Return forward iterator after last element
		 *
		 * @return T const*
		 */
		inline T const* end() const
			{
			return *x + length;
			}

		/**
		 * @brief Filling matrix by value
		 *
		 * @param value
		 */
		void fill ( T value )
			{
			T* it = begin();
			T const* it_end = end();

			// iterate over all fields
			while ( it != it_end )
				*it++ = value;
			}

		/**
		 * @brief Get size of Matrix == ROWS*COLS
		 *
		 * @return unsigned
		 */
		inline unsigned size() const
			{
			return ROWS*COLS;
			}

		/**
		 * @brief Sum of all Matrix elements
		 *
		 * @return T
		 */
		T sum() const
			{
			return Container::sum(begin(), end());
			}


		/**
		 * @brief Multiplication of all Matrix elements
		 *
		 * @return T
		 */
		T mul() const
			{
			return Container::mul(begin(), end());
			}

		/**
		 * @brief Access to Matrix element at row row and col col.
		 * There is not checked out of range
		 *
		 * @param row
		 * @param col
		 * @return T&
		 */
		inline T& operator() ( unsigned row, unsigned col )
			{
			return x[row][col];
			}

		/**
		 * @brief Access to Matrix element idx in flatten Matrix.
		 * There is not checked out of range
		 *
		 * @param idx
		 * @return T&
		 */
		inline T& operator() ( unsigned idx )
			{
			return * ( begin()+idx );
			}


		template<typename T_, unsigned ROWS_, unsigned COLS_>
		friend std::ostream& operator<< ( std::ostream& out, const Matrix<T_, ROWS_, COLS_>& m );

		~Matrix()
			{
			}
	};


template<typename T, unsigned ROWS, unsigned COLS>
std::ostream& operator<< ( std::ostream& out, const Matrix<T, ROWS, COLS>& m )
	{
	unsigned width = COLS*10;

	out.width ( 1 );
	// open parenthes top
	out << char ( 218 ) << ' ';
	for ( unsigned i = 0; i < width; ++i )
		out << ' ';
	// close parenthes top
	out << char ( 191 ) << '\n';


	out.precision ( 4 );
	for ( unsigned i = 0; i < ROWS; ++i )
		{
		// parenthes middle left
		out << char ( 179 ) << ' ';

		for ( unsigned j = 0; j < COLS; ++j )
			{
			out.width ( 9 );
			out << m.x[i][j] << ' ';
			}
		// parenthes middle right
		out.width ( 1 );
		out << char ( 179 ) << '\n';
		}

	// open parenthes bottom
	out << char ( 192 ) << ' ';
	for ( unsigned i = 0; i < width; ++i )
		out << ' ';
	// close parenthes bottom
	out << char ( 217 );

	return out;
	}


#endif //MATRIX_HPP