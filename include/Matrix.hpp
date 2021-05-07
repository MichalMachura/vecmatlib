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


template<typename Tt,
		 typename U,
		 typename T_U = decltype ( Tt()*U() ),
		 unsigned ROWS1,
		 unsigned COLS1,
		 unsigned ROWS2,
		 unsigned COLS2,
		 std::enable_if_t<std::is_convertible<U, Tt>::value, int> = 0>
static void cauchyProduct ( const Matrix<Tt, ROWS1, COLS1>& first,
							const Matrix<U, ROWS2, COLS2>& second,
							Matrix<T_U, ROWS1, COLS2>& output );

template<typename Tt,
		 typename U,
		 typename T_U = decltype ( Tt()*U() ),
		 unsigned ROWS1,
		 unsigned COLS1,
		 unsigned SIZE2,
		 std::enable_if_t<std::is_convertible<U, Tt>::value, int> = 0>
static void cauchyProduct ( const Matrix<Tt, ROWS1, COLS1>& first,
							const Vector<U, SIZE2>& second,
							Vector<T_U, ROWS1>& output );

template<typename Tt,
		 typename U,
		 typename T_U = decltype ( Tt()*U() ),
		 unsigned SIZE1,
		 unsigned COLS2,
		 std::enable_if_t<std::is_convertible<U, Tt>::value, int> = 0>
static void cauchyProduct ( const Vector<Tt, SIZE1>& first,
							const Matrix<U, 1, COLS2>& second,
							Matrix<T_U, SIZE1, COLS2>& output );

template<typename Tt,
		 typename U,
		 typename T_U = decltype ( Tt()*U() ),
		 unsigned ROWS1,
		 unsigned COLS1,
		 unsigned SIZE2,
		 std::enable_if_t<std::is_convertible<U, Tt>::value, int> = 0>
static void transposedCauchyProduct ( const Matrix<Tt, ROWS1, COLS1>& first,
									  const Vector<U, SIZE2>& second,
									  Vector<T_U, ROWS1>& output );

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
		 * @brief Matrix filled by parameters given by { }
		 *
		 * @tparam U type of initializer_list arguments
		 * @param args initializer_list must by the same type and cenvertable to T
		 */
		template<typename U,
				 std::enable_if_t<std::is_convertible<U, T>::value, int> = 0>
		Matrix ( const std::initializer_list<U>& args )
			{
			if ( args.size() > length )
				throw std::runtime_error ( "Too many arguments in constructor params." );

			T* it = begin();
			T const* it_end = end();

			for ( auto&& arg : args )
				*it++ = T ( arg );

			// fill rest by 0
			while ( it != it_end )
				*it++ = T ( 0 );
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

		/**
		 * @brief Assign the same size Matrix
		 *
		 * @tparam U type of other Matrix
		 * @param other Matrix to assign
		 * @return Matrix<T, ROWS, COLS>& *this
		 */
		template<typename U,
				 std::enable_if_t<std::is_convertible<U, T>::value, int> = 0>
		Matrix<T, ROWS, COLS>& operator= ( const Matrix<U, ROWS, COLS>& other )
			{
			Container::copy ( begin(), end(), other.begin() );

			return *this;
			}

		/**
		 * @brief Assign the same size Matrix given by r-reference
		 *
		 * @tparam U type of other Matrix
		 * @param other Matrix to assign
		 * @return Matrix<T, ROWS, COLS>& *this
		 */
		template<typename U,
				 std::enable_if_t<std::is_convertible<U, T>::value, int> = 0>
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
				 typename T_U = decltype ( T()+U() ),
				 std::enable_if_t<std::is_convertible<U, T>::value, int> = 0>
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
				 typename T_U = decltype ( T()+U() ),
				 std::enable_if_t<std::is_convertible<U, T>::value, int> = 0>
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
				 typename T_U = decltype ( T()+U() ),
				 std::enable_if_t<std::is_convertible<U, T>::value, int> = 0>
		inline Matrix<T_U, ROWS, COLS> hadamardProduct ( const Matrix<U, ROWS, COLS>& other ) const
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
				 typename T_U = decltype ( T()+U() ),
				 std::enable_if_t<std::is_convertible<U, T>::value, int> = 0>
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
				 typename T_U = decltype ( T()+U() ),
				 std::enable_if_t<std::is_convertible<U, T>::value, int> = 0>
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
				 typename T_U = decltype ( T()*U() ),
				 std::enable_if_t<std::is_convertible<U, T>::value, int> = 0>
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
				 typename T_U = decltype ( T()+U() ),
				 std::enable_if_t<std::is_convertible<U, T>::value, int> = 0>
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
		template<typename U,
				 std::enable_if_t<std::is_convertible<U, T>::value, int> = 0>
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
		template<typename U,
				 std::enable_if_t<std::is_convertible<U, T>::value, int> = 0>
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
		template<typename U,
				 std::enable_if_t<std::is_convertible<U, T>::value, int> = 0>
		inline Matrix<T, ROWS, COLS>& hadamardProductAssign ( const Matrix<U, ROWS, COLS>& other )
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
		template<typename U,
				 std::enable_if_t<std::is_convertible<U, T>::value, int> = 0>
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
		template<typename U,
				 std::enable_if_t<std::is_convertible<U, T>::value, int> = 0>
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
		template<typename U,
				 std::enable_if_t<std::is_convertible<U, T>::value, int> = 0>
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
		template<typename U,
				 std::enable_if_t<std::is_convertible<U, T>::value, int> = 0>
		inline Matrix<T, ROWS, COLS>& operator/= ( U value )
			{
			if ( value == T ( 0 ) )
				throw std::runtime_error ( "Dividing by 0" );

			Container::executeContainerValueOperationAssign<Multiply> ( *this, 1/value );
			return *this;
			}

		/* MATRIX VECTOR ARITHMETICS */

		/**
		* @brief Computing standard Matrix multiplication.
		* Must be fullfill assumption COLS == ROWS2
		*
		* @tparam U type of second Matrix
		* @tparam T_U = ( Tt()*U() ) type of output Matrix
		* @tparam ROWS2 number of rows of second Matrix
		* @tparam COLS2 number of cols of second Matrix
		* @param second second Matrix
		* @return Matrix result of multiplication
		*/
		template<typename U,
				 typename T_U = decltype ( T()*U() ),
				 unsigned ROWS2,
				 unsigned COLS2,
				 std::enable_if_t<std::is_convertible<U, T>::value, int> = 0>
		Matrix<T_U, ROWS, COLS2> operator* ( const Matrix<U, ROWS2, COLS2>& second ) const
			{
			static_assert ( COLS == ROWS2, "First matrix columns number must be equal to second matrix rows number." );

			Matrix<T_U, ROWS, COLS2> ans;
			cauchyProduct<T, U, T_U> ( *this, second, ans );

			return ans;
			}

		/**
		* @brief Computing standard Matrix multiplication,
		* with assign result to first, as *this.
		* Must be fullfill assumption COLS == ROWS2 AND COLS == COLS2
		*
		* @tparam Tt type of first Matrix
		* @tparam U type of second Matrix
		* @tparam ROWS2 number of rows of second Matrix
		* @tparam COLS2 number of cols of second Matrix
		* @param second second Matrix
		* @return *this
		*/
		template<typename U,
				 unsigned ROWS2,
				 unsigned COLS2,
				 std::enable_if_t<std::is_convertible<U, T>::value, int> = 0>
		Matrix<T, ROWS, COLS>& operator*= ( const Matrix<U, ROWS2, COLS2>& second )
			{
			static_assert ( COLS == ROWS2, "First matrix columns number must be equal to second matrix rows number." );
			static_assert ( COLS == COLS2, "Number of columns of matrices must be equal." );

			Matrix aux = *this;
			cauchyProduct<T, U, T> ( aux, second, *this );

			return *this;
			}

		/**
		* @brief Computing standard Matrix Vector multiplication.
		* Must be fullfill assumption COLS == SIZE2
		*
		* @tparam U type of second Vector
		* @tparam T_U = ( Tt()*U() ) type of output Vector
		* @tparam SIZE2 size of second Vector
		* @param second second Vector
		* @return Vector result of multiplication
		*/
		template<typename U,
				 typename T_U = decltype ( T()*U() ),
				 unsigned SIZE2,
				 std::enable_if_t<std::is_convertible<U, T>::value, int> = 0>
		Vector<T_U, ROWS> operator* ( const Vector<U, SIZE2>& second ) const
			{
			Vector<T_U, ROWS> ans;
			cauchyProduct<T, U, T_U> ( *this, second, ans );

			return ans;
			}

		/**
		* @brief Computing standard Matrix Vector multiplication with matrix transposition.
		* Must be fullfill assumption ROWS == SIZE2
		*
		* @tparam U type of second Vector
		* @tparam T_U = ( Tt()*U() ) type of output Vector
		* @tparam SIZE2 size of second Vector
		* @param second second Vector
		* @return Vector result of multiplication
		*/
		template<typename U,
				 typename T_U = decltype ( T()*U() ),
				 unsigned SIZE2,
				 std::enable_if_t<std::is_convertible<U, T>::value, int> = 0>
		Vector<T_U, COLS> transposedMul ( const Vector<U, SIZE2>& second ) const
			{
			Vector<T_U, COLS> ans;
			transposedCauchyProduct<T, U, T_U> ( *this, second, ans );

			return ans;
			}



		template<typename T_, unsigned ROWS_, unsigned COLS_>
		friend std::ostream& operator<< ( std::ostream& out, const Matrix<T_, ROWS_, COLS_>& m );

		~Matrix()
			{
			}
	};


/**
 * @brief Add value and Matrix => result Matrix
 *
 * @tparam T type of Matrix
 * @tparam U type of value
 * @tparam T_U = ( T()+U() ) type of result
 * @tparam ROWS number of rows in Matrix
 * @tparam COLS number of columns in Matrix
 * @param value value to add
 * @param m Matrix
 * @return Matrix<T_U, ROWS, COLS>
 */
template<typename T,
		 typename U,
		 typename T_U = decltype ( T()+U() ),
		 unsigned ROWS,
		 unsigned COLS,
		 std::enable_if_t<std::is_convertible<U, T>::value, int> = 0>
inline Matrix<T_U, ROWS, COLS> operator+ ( U value, const Matrix<T, ROWS, COLS>& m )
	{
	return m + value;
	}

/**
 * @brief Subtract Matrix from value => result Matrix
 *
 * @tparam T type of Matrix
 * @tparam U type of value
 * @tparam T_U = ( T()+U() ) type of result
 * @tparam ROWS number of rows in Matrix
 * @tparam COLS number of columns in Matrix
 * @param value value from which Matrix is subtraced
 * @param m Matrix
 * @return Matrix<T_U, ROWS, COLS>
 */
template<typename T,
		 typename U,
		 typename T_U = decltype ( T()+U() ),
		 unsigned ROWS,
		 unsigned COLS,
		 std::enable_if_t<std::is_convertible<U, T>::value, int> = 0>
inline Matrix<T_U, ROWS, COLS> operator- ( U value, const Matrix<T, ROWS, COLS>& m )
	{
	Matrix<T_U, ROWS, COLS> ans;
	Container::executeContainerValueOperation<SubtractInverse> ( m, value, ans );

	return ans;
	}

/**
 * @brief Multiply value and Matrix => result Matrix
 *
 * @tparam T type of Matrix
 * @tparam U type of value
 * @tparam T_U = ( T()+U() ) type of result
 * @tparam ROWS number of rows in Matrix
 * @tparam COLS number of columns in Matrix
 * @param value value to multiply by
 * @param m Matrix
 * @return Matrix<T_U, ROWS, COLS>
 */
template<typename T,
		 typename U,
		 typename T_U = decltype ( T()*U() ),
		 unsigned ROWS,
		 unsigned COLS,
		 std::enable_if_t<std::is_convertible<U, T>::value, int> = 0>
inline Matrix<T_U, ROWS, COLS> operator* ( U value, const Matrix<T, ROWS, COLS>& m )
	{
	static_assert ( std::is_convertible<U, T>::value, "U type must be convertabe to type T" );

	return m*value;
	}

/**
 * @brief Display matrix using std::ostream
 *
 * @tparam T type of matrix
 * @tparam ROWS number of matrix rows
 * @tparam COLS number of matrix cols
 * @param out std::ostream output stream
 * @param m Matrix to display
 * @return std::ostream&
 */
template<typename T, unsigned ROWS, unsigned COLS>
std::ostream& operator<< ( std::ostream& out, const Matrix<T, ROWS, COLS>& m )
	{
	unsigned display_width = std::is_floating_point<T>::value ? 9 : 5;
	unsigned width = COLS* ( display_width+1 );

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
			out.width ( display_width );
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

/* VECTOR AND MATRIX*/
/**
 * @brief Computing standard Matrix multiplication.
 * Must be fullfill assumption COLS1 == ROWS2
 *
 * @tparam Tt type of first Matrix
 * @tparam U type of second Matrix
 * @tparam T_U = ( Tt()*U() ) type of output Matrix
 * @tparam ROWS1 number of rows of first Matrix
 * @tparam COLS1 number of cols of first Matrix
 * @tparam ROWS2 number of rows of second Matrix
 * @tparam COLS2 number of cols of second Matrix
 * @param first first Matrix
 * @param second second Matrix
 * @param output Matrix result of multiplication
 */
template<typename Tt,
		 typename U,
		 typename T_U = decltype ( Tt()*U() ),
		 unsigned ROWS1,
		 unsigned COLS1,
		 unsigned ROWS2,
		 unsigned COLS2,
		 std::enable_if_t<std::is_convertible<U, Tt>::value, int> = 0>
static void cauchyProduct ( const Matrix<Tt, ROWS1, COLS1>& first,
							const Matrix<U, ROWS2, COLS2>& second,
							Matrix<T_U, ROWS1, COLS2>& output )
	{
	static_assert ( COLS1 == ROWS2, "First matrix columns number must be equal to second matrix rows number." );
	// iterator to result beginning
	T_U* it_output_beg = output.begin();

	// for each result element
	for ( unsigned i=0; i < output.rows; ++i )
		{
		for ( unsigned j=0; j < output.cols; ++j )
			{
			Tt* it_first_beg = first.begin ( i );
			Tt* it_first_end = first.end ( i );
			// will be incremented by COLS2
			U* it_second_beg = second.begin () + j;
			// value for (i, j) position
			T_U value = T_U ( 0 );

			// multiply and sum elements from first(i, :) and second(:, j)
			while ( it_first_beg != it_first_end )
				{
				value += *it_first_beg++ * *it_second_beg;
				it_second_beg += COLS2;
				}
			// assign to result
			*it_output_beg++ = value;
			}
		}
	}

/**
* @brief Computing standard Matrix Vector multiplication.
* Must be fullfill assumption COLS1 == SIZE2
*
* @tparam Tt type of first Matrix
* @tparam U type of second Vector
* @tparam T_U = ( Tt()*U() ) type of output Vector
* @tparam ROWS1 number of rows of first Matrix
* @tparam COLS1 number of cols of first Matrix
* @tparam SIZE2 size of second Vector
* @param first first Matrix
* @param second second Vector
* @param output Vector result of multiplication
*/
template<typename Tt,
		 typename U,
		 typename T_U = decltype ( Tt()*U() ),
		 unsigned ROWS1,
		 unsigned COLS1,
		 unsigned SIZE2,
		 std::enable_if_t<std::is_convertible<U, Tt>::value, int> = 0>
static void cauchyProduct ( const Matrix<Tt, ROWS1, COLS1>& first,
							const Vector<U, SIZE2>& second,
							Vector<T_U, ROWS1>& output )
	{
	static_assert ( COLS1 == SIZE2, "First matrix columns number must be equal to vector size." );
	// iterator to result beginning
	T_U* it_output_beg = output.begin();

	// for each output vector element
	for ( unsigned i=0; i < ROWS1; ++i )
		{
		Tt* it_first_beg = first.begin ( i );
		Tt* it_first_end = first.end ( i );
		// will be incremented by COLS2
		U* it_second_beg = second.begin ();
		// value for (i) position
		T_U value = T_U ( 0 );

		// multiply and sum elements from first(i, :) and second(:)
		while ( it_first_beg != it_first_end )
			{
			value += *it_first_beg++ * *it_second_beg++;
			}

		// assign to result
		*it_output_beg++ = value;
		}
	}


/**
* @brief Computing standard Matrix Vector multiplication with transposition of first matrix.
* Must be fullfill assumption COLS1 == SIZE2
*
* @tparam Tt type of first Matrix
* @tparam U type of second Vector
* @tparam T_U = ( Tt()*U() ) type of output Vector
* @tparam ROWS1 number of rows of first Matrix
* @tparam COLS1 number of cols of first Matrix
* @tparam SIZE2 size of second Vector
* @param first first Matrix which will be calculated as transposed
* @param second second Vector
* @param output Vector result of multiplication
*/
template<typename Tt,
		 typename U,
		 typename T_U = decltype ( Tt()*U() ),
		 unsigned ROWS1,
		 unsigned COLS1,
		 unsigned SIZE2,
		 std::enable_if_t<std::is_convertible<U, Tt>::value, int> = 0>
static void transposedCauchyProduct ( const Matrix<Tt, ROWS1, COLS1>& first,
									  const Vector<U, SIZE2>& second,
									  Vector<T_U, ROWS1>& output )
	{
	static_assert ( ROWS1 == SIZE2, "First transposed matrix rows number must be equal to vector size." );
	// iterator to result beginning
	T_U* it_output_beg = output.begin();

	// for each output vector element
	for ( unsigned i=0; i < COLS1; ++i )
		{
		Tt* it_first_beg = first.end () -1 -i;
		U* it_second_beg = second.begin ();
		U* it_second_end = second.end ();
		// value for (i) position
		T_U value = T_U ( 0 );

		// multiply and sum elements from first(:, ROWS1 - i-1) and second(:)
		while ( it_second_beg != it_second_end )
			{
			value += *it_first_beg * *it_second_beg++;
			it_first_beg -= COLS1;
			}

		// assign to result
		*it_output_beg++ = value;
		}
	}

/**
* @brief Computing standard Vector Matrix multiplication.
* Must be fullfill assumption SIZE1 == COLS2 AND ROWS2 == 1
*
* @tparam Tt type of first Vector
* @tparam U type of second Matrix
* @tparam T_U = ( Tt()*U() ) type of output Matrix
* @tparam SIZE1 size of first Vector
* @tparam ROWS2 number of rows of second Matrix
* @tparam COLS2 number of cols of second Matrix
* @param first first Vector
* @param second second Matrix
* @param output Matrix result of multiplication
*/
template<typename Tt,
		 typename U,
		 typename T_U = decltype ( Tt()*U() ),
		 unsigned SIZE1,
		 unsigned COLS2,
		 std::enable_if_t<std::is_convertible<U, Tt>::value, int> = 0>
static void cauchyProduct ( const Vector<Tt, SIZE1>& first,
							const Matrix<U, 1, COLS2>& second,
							Matrix<T_U, SIZE1, COLS2>& output )
	{
	// iterator to result beginning
	T_U* it_output_beg = output.begin();
	Tt* it_first_beg = first.begin ();

	// for each result element
	for ( unsigned i=0; i < output.rows; ++i )
		{
		U* it_second_beg = second.begin ();
		for ( unsigned j=0; j < output.cols; ++j )
			{
			// assign to result
			*it_output_beg++ = *it_first_beg * *it_second_beg++;
			}

		it_first_beg++;
		}
	}


/**
* @brief Computing standard Vector Matrix multiplication.
* Must be fullfill assumption SIZE1 == COLS2 AND ROWS2 == 1
*
* @tparam Tt type of first Vector
* @tparam U type of second Matrix
* @tparam T_U = ( Tt()*U() ) type of output Matrix
* @tparam SIZE1 size of first Vector
* @tparam ROWS2 number of rows of second Matrix
* @tparam COLS2 number of cols of second Matrix
* @param first first Vector
* @param second second Matrix
* @param output Matrix result of multiplication
*/
template<typename Tt,
		 typename U,
		 typename T_U = decltype ( Tt()*U() ),
		 unsigned SIZE1,
		 unsigned COLS2,
		 std::enable_if_t<std::is_convertible<U, Tt>::value, int> = 0>
inline Matrix<T_U, SIZE1, COLS2> operator* ( const Vector<Tt, SIZE1>& first,
		const Matrix<U, 1, COLS2>& second )
	{
	Matrix<T_U, SIZE1, COLS2> ans;
	cauchyProduct<Tt, U, T_U, SIZE1, COLS2> ( first, second, ans );

	return ans;
	}

template<typename T,
		 unsigned SIZE>
inline void eye ( Matrix<T, SIZE, SIZE>& m )
	{
	T* it_beg = m.begin();
	T* it_end_aux;
	T* const it_end = m.end();

	while ( it_beg != it_end )
		{
		*it_beg++ = T ( 1 ); // TO TEST

		// it's last row and last col
		if ( it_beg == it_end )
			break;

		// iterate over next SIZE elements
		it_end_aux = it_beg + SIZE;
		while ( it_beg != it_end_aux )
			*it_beg++ = T ( 0 );
		}
	}

// x
template<typename T>
Matrix<T, 3, 3> rotationX ( T angle )
	{
	T cos_angle = cos ( angle );
	T sin_angle = sin ( angle );

	return Matrix<T, 3, 3> { T ( 1 ), T ( 0 ), T ( 0 ),
							 T ( 0 ), cos_angle, -sin_angle,
							 T ( 0 ), sin_angle, cos_angle
						   };
	}

// y
template<typename T>
Matrix<T, 3, 3> rotationY ( T angle )
	{
	T cos_angle = cos ( angle );
	T sin_angle = sin ( angle );

	return Matrix<T, 3, 3> { cos_angle, T ( 0 ), sin_angle,
							 T ( 0 ), T ( 1 ), T ( 0 ),
							 -sin_angle, T ( 0 ), cos_angle
						   };
	}

// z
template<typename T>
Matrix<T, 3, 3> rotationZ ( T angle )
	{
	T cos_angle = cos ( angle );
	T sin_angle = sin ( angle );

	return Matrix<T, 3, 3> { cos_angle, -sin_angle, T ( 0 ),
							 sin_angle, cos_angle, T ( 0 ),
							 T ( 0 ), T ( 0 ), T ( 1 ),
						   };
	}

template<typename T>
Matrix<T, 3, 3> rotationMatrix ( const Vector<T, 3>& angles )
	{
	return rotationZ ( angles.x[2] ) *
		   rotationY ( angles.x[1] ) *
		   rotationX ( angles.x[0] );
	}

#endif //MATRIX_HPP