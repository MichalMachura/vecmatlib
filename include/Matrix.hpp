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
//#include "Vector.hpp"

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
		Matrix ( T value )
			{
			fill ( value );
			}

		/* ASSIGN */

		template<typename U>
		Matrix<T, ROWS, COLS>& operator= ( const Matrix<U, ROWS, COLS>& other )
			{
			Container::copy ( begin(), end(), other.begin() );

			return *this;
			}

		template<typename U>
		Matrix<T, ROWS, COLS>& operator= ( const Matrix<U, ROWS, COLS>&& other )
			{
			Container::copy ( begin(), end(), other.begin() );

			return *this;
			}

		/* ITERATORS AND SIZE*/
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
		 * @brief Return forward iterator to first element of row
		 *
		 * @param row number of matrix row
		 * @return T*
		 */
		inline T* begin ( unsigned row ) const
			{
			return const_cast<T*> ( x[row] );
			}

		/**
		 * @brief Return forward iterator after last element
		 *
		 * @return T const*
		 */
		inline T* end() const
			{
			return begin() + length;
			}

		/**
		 * @brief Return forward iterator after last element of row
		 *
		 * @param row number of matrix row
		 * @return T*
		 */
		inline T* end ( unsigned row ) const
			{
			return begin ( row ) + COLS;
			}

		/**
		 * @brief Get size of Matrix == ROWS*COLS
		 *
		 * @return unsigned
		 */
		static inline unsigned size()
			{
			return length;
			}

		/**
		 * @brief Fill all Matrix fields by value
		 *
		 * @param value
		 */
		void fill ( T value )
			{
			Container::fill ( begin(), end(), value );
			}

		/* ACCESS OPERATORS */
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

		/* ARITHMETIC OPERATORS*/

		/**
		 * @brief Add corresponding Matrix elements return it as corresponding Matrix
		 *
		 * @tparam U type of second argument
		 * @tparam T_U = ( T()+U() ) output Matrix type
		 * @param other second argument
		 * @return Matrix<T_U, ROWS, COLS> result
		 */
		template<typename U,
				 typename T_U = decltype ( T()+U() )>
		inline Matrix<T_U, ROWS, COLS> operator+ ( const Matrix<U, ROWS, COLS>& other ) const
			{
			Matrix<T_U, ROWS, COLS> ans;
			Container::executeContainersOperation <Add> ( *this, other, ans );

			return ans;
			}

		/**
		 * @brief Subtract corresponding Matrix elements  return it as corresponding Matrix
		 *
		 * @tparam U type of second argument
		 * @tparam T_U = ( T()+U() ) output Matrix type
		 * @param other second argument
		 * @return Matrix<T_U, ROWS, COLS> result
		 */
		template<typename U,
				 typename T_U = decltype ( T()+U() )>
		inline Matrix<T_U, ROWS, COLS> operator- ( const Matrix<U, ROWS, COLS>& other ) const
			{
			Matrix<T_U, ROWS, COLS> ans;
			Container::executeContainersOperation <Subtract> ( *this, other, ans );

			return ans;
			}

		/**
		 * @brief Multiply corresponding Vectors elements  return it as corresponding Matrix
		 *
		 * @tparam U type of second argument
		 * @tparam T_U = ( T()+U() ) output Matrix type
		 * @param other second argument
		 * @return Matrix<T_U, ROWS, COLS> result
		 */
		template<typename U,
				 typename T_U = decltype ( T()+U() )>
		inline Matrix<T_U, ROWS, COLS> operator* ( const Matrix<U, ROWS, COLS>& other ) const
			{
			Matrix<T_U, ROWS, COLS> ans;
			Container::executeContainersOperation <Multiply> ( *this, other, ans );

			return ans;
			}

		/**
		 * @brief Add Matrix elements and value return it as Matrix
		 *
		 * @tparam U value type
		 * @tparam T_U = ( T()+U() ) output Matrix type
		 * @param other second argument
		 * @return Matrix<T_U, ROWS, COLS> result
		 */
		template<typename U,
				 typename T_U = decltype ( T()+U() )>
		inline Matrix<T_U, ROWS, COLS> operator+ ( U value ) const
			{
			Matrix<T_U, ROWS, COLS> ans;
			Container::executeContainerValueOperation<Add> ( *this, value, ans );

			return ans;
			}

		/**
		 * @brief Subtract Matrix elements and value return it as Matrix
		 *
		 * @tparam U value type
		 * @tparam T_U = ( T()+U() ) output Matrix type
		 * @param other second argument
		 * @return Matrix<T_U, ROWS, COLS> result
		 */
		template<typename U,
				 typename T_U = decltype ( T()+U() )>
		inline Matrix<T_U, ROWS, COLS> operator- ( U value ) const
			{
			Matrix<T_U, ROWS, COLS> ans;
			Container::executeContainerValueOperation<Subtract> ( *this, value, ans );

			return ans;
			}

		/**
		 * @brief Multiply Matrix elements and value return it as Matrix
		 *
		 * @tparam U value type
		 * @tparam T_U = ( T()+U() ) output Matrix type
		 * @param other second argument
		 * @return Matrix<T_U, ROWS, COLS> result
		 */
		template<typename U,
				 typename T_U = decltype ( T()+U() )>
		inline Matrix<T_U, ROWS, COLS> operator* ( U value ) const
			{
			Matrix<T_U, ROWS, COLS> ans;
			Container::executeContainerValueOperation<Multiply> ( *this, value, ans );

			return ans;
			}

		/**
		 * @brief Divide Matrix elements by value return it as Matrix
		 *
		 * @tparam U value type
		 * @tparam T_U = ( T()+U() ) output Matrix type
		 * @param other second argument
		 * @return Matrix<T_U, ROWS, COLS> result
		 */
		template<typename U,
				 typename T_U = decltype ( T()+U() )>
		inline Matrix<T_U, ROWS, COLS> operator/ ( U value ) const
			{
			if ( value == T ( 0 ) )
				throw std::runtime_error ( "Dividing by 0" );

			Matrix<T_U, ROWS, COLS> ans;
			Container::executeContainerValueOperation<Multiply> ( *this, 1/value, ans );

			return ans;;
			}

		/* OPERATORS WITH ASSIGNMENT*/
		/**
		 * @brief Add Matrix to this Matrix.
		 *
		 * @tparam U type of second argument
		 * @param other second argument
		 * @return Matrix<T, ROWS, COLS>& reference to this
		 */
		template<typename U>
		inline Matrix<T, ROWS, COLS>& operator+= ( const Matrix<U, ROWS, COLS>& other )
			{
			Container::executeContainersOperationAssign <Add> ( *this, other );

			return *this;
			}

		/**
		 * @brief Subtract Matrix from this Matrix.
		 *
		 * @tparam U type of second argument
		 * @param other second argument
		 * @return Matrix<T, ROWS, COLS>& reference to this
		 */
		template<typename U>
		inline Matrix<T, ROWS, COLS>& operator-= ( const Matrix<U, ROWS, COLS>& other )
			{
			Container::executeContainersOperationAssign <Subtract> ( *this, other );

			return *this;
			}

		/**
		 * @brief Multiply element wise this Matrix by other
		 *
		 * @tparam U type of second argument
		 * @param other second argument
		 * @return Matrix<T, ROWS, COLS>& reference to this
		 */
		template<typename U>
		inline Matrix<T, ROWS, COLS>& operator*= ( const Matrix<U, ROWS, COLS>& other )
			{
			Container::executeContainersOperationAssign <Multiply> ( *this, other );

			return *this;
			}

		/**
		 * @brief Add value to this Matrix
		 *
		 * @tparam U type of value
		 * @param value value to add to Matrix
		 * @return Matrix<T, ROWS, COLS>& this Matrix
		 */
		template<typename U>
		inline Matrix<T, ROWS, COLS>& operator+= ( U value )
			{
			Container::executeContainerValueOperationAssign<Add> ( *this, value );
			return *this;
			}

		/**
		 * @brief Subtract value from this Matrix
		 *
		 * @tparam U type of value
		 * @param value value to subtract from Matrix
		 * @return Matrix<T, ROWS, COLS>& this Matrix
		 */
		template<typename U>
		inline Matrix<T, ROWS, COLS>& operator-= ( U value )
			{
			Container::executeContainerValueOperationAssign<Subtract> ( *this, value );
			return *this;
			}

		/**
		 * @brief Multiply this Matrix by value
		 *
		 * @tparam U type of value
		 * @param value value to multiply by
		 * @return Matrix<T, ROWS, COLS>& this Matrix
		 */
		template<typename U>
		inline Matrix<T, ROWS, COLS>& operator*= ( U value )
			{
			Container::executeContainerValueOperationAssign<Multiply> ( *this, value );
			return *this;
			}

		/**
		 * @brief Divide this Matrix by value
		 *
		 * @tparam U type of value
		 * @param value value to add to Matrix
		 * @return Matrix<T, ROWS, COLS>& this Matrix
		 */
		template<typename U>
		inline Matrix<T, ROWS, COLS>& operator/= ( U value )
			{
			if ( value == T ( 0 ) )
				throw std::runtime_error ( "Dividing by 0" );

			Container::executeContainerValueOperationAssign<Multiply> ( *this, 1/value );
			return *this;
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