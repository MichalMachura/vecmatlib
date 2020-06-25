#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <type_traits>
#include <initializer_list>
#include <cassert>
#include <cmath>
#include <ostream>
#include <exception>

#include "Utility.hpp"

template<typename T, unsigned size = 3>
struct Vector
	{
	public:
		T x[size];

	public:
		/**
		 * @brief Constract Vector with non initialized fields
		 *
		 */
		Vector()
			{
			}

		Vector ( const Vector< T, size >& other )
			{
			T* it = this->x;
			const T* it_end = this->x + size;
			const T* it_other = other.x;

			// copy
			while ( it != it_end )
				*it++ = *it_other++;
			}

		/**
		 * @brief Construct Vector with all fields initialized
		 *  of value val
		 *
		 * @param val
		 */
		Vector ( T val )
			{
			T* it = x;
			T const* it_end = x + size;
			// assign val for each field
			while ( it != it_end )
				*it++ = val;
			}

		/**
		 * @brief Vector with args given by parameters
		 *
		 * @param args parameters must be converetable to T
		 */
		Vector ( std::initializer_list<T> args )
			{
			if ( args.size() > size )
				throw std::runtime_error ( "Too many arguments in constructor params." );

			T* it = x;
			T const* it_end = x + size;
			for ( auto&& arg : args )
				*it++ = T ( arg );

			// fill rest by 0
			while ( it != it_end )
				*it++ = T ( 0 );
			}

		/**
		 * @brief Vector created from another vector could be smaller size.
		 * If smaller then rest fields are filled by value fill_value.
		 *
		 * @tparam U
		 * @tparam size_U
		 * @param other
		 * @param fill_value
		 */
		template<typename U, unsigned size_U>
		Vector ( const Vector<U, size_U>& other, T fill_value=T ( 0 ) )
			{
			static_assert ( size_U <= size, "Too large Vector in constructor." );

			T* it = x;
			T const* it_end = end();
			const U* it_other = other.x;
			U const* it_other_end = other.end();

			while ( it_other != it_other_end )
				*it++ = T ( *it_other++ );

			// fill rest by 0
			while ( it != it_end )
				*it++ = fill_value;
			}

		/**
		 * @brief Forward begin iterator
		 *
		 * @return T*
		 */
		inline T* begin() const
			{
			return const_cast<T*> ( x );
			}

		/**
		 * @brief Forward end iterator
		 *
		 * @return const T*
		 */
		inline const T* end() const
			{
			return x+size;
			}

		/**
		 * @brief Fill all vector fields by value
		 *
		 * @param value
		 */
		void fill ( T value )
			{
			Container::fill(begin(), end(), value);
			}

		/**
		 * @brief Calculting dot product this Vector and
		 *
		 * other vector to
		 * @return T
		 */
		T dot ( const Vector<T, size>& other ) const
			{
			T sum = T ( 0 );
			const T* it = x;
			const T* it_other = other.x;
			T const* it_end = x+size;

			// iterate over all fields and sum each
			while ( it != it_end )
				sum += ( *it++ )* ( *it_other++ );

			return sum;
			}

		/**
		 * @brief Euclidian norm of Vector
		 *
		 * @return T
		 */
		inline T norm() const
			{
			return std::sqrt ( dot ( *this ) );
			}

		/**
		 * @brief Sum of all vector elements
		 *
		 * @return T
		 */
		T sum() const
			{
			return Container::sum(begin(), end());
			}

		/**
		 * @brief Multiplication of all vector elements
		 *
		 * @return T
		 */
		T mul() const
			{
			return Container::mul(begin(), end());
			}

		/**
		 * @brief Executing operation on Vectors corresponding elements and return corresponding Vector of result
		 *
		 * @tparam U type of other Vector
		 * @tparam operation function T_U(*)(T, U)
		 * @tparam ( std::declval<T>() + std::declval<U>() ) returned Vector type
		 * @param other second operand of size size
		 * @return Vector<T_U, size>
		 */
		template<operator_T_U<T, T, T> operation>
		inline Vector<T, size>  vectorElemetsOperation ( const Vector<T, size>& other ) const
			{
			Vector<T, size> ans;
			/*
			T* it_ans = ans.x;
			const T* it_other = other.x;
			const T* it_this = x;
			const T* it_this_end = x+size;

			// iterate over all fields and sum each corresponding fields
			while ( it_this != it_this_end )
				*it_ans++ = operation ( *it_this++, *it_other++ );*/

			Container::rangeElemetsOperation<T, operation>(begin(), end(), other.begin(), ans.begin());

			return ans;
			}

		/**
		 * @brief Add corresponding Vectors elements and return it as corresponding Vector
		 *
		 * @param other Vector of the same size
		 * @return Vector<T, size>
		 */
		Vector<T, size> operator+ ( const Vector<T, size>& other ) const
			{
			return vectorElemetsOperation< add<T, T> > ( other );
			}

		/**
		 * @brief Subtract corresponding Vectors elements and return it as corresponding Vector
		 *
		 * @param other Vector of the same size
		 * @return Vector<T, size>
		 */
		Vector<T, size> operator- ( const Vector<T, size>& other ) const
			{
			return vectorElemetsOperation<subtract<T, T> > ( other );
			}

		/**
		 * @brief Multiply corresponding Vectors elements and return it as corresponding Vector
		 *
		 * @param other Vector of the same size
		 * @return Vector<T, size>
		 */
		Vector<T, size> operator* ( const Vector<T, size>& other ) const
			{
			return vectorElemetsOperation<multiply<T, T> > ( other );
			}

		/**
		 * @brief Execute operation on each element of Vector and value.
		 * Result is Vector of corresponding to input Vector values.
		 *
		 * @tparam U Type of value
		 * @tparam T_U = ( T() + U() ) type of returned Vector
		 * @tparam operation operation to execute for each Vector element
		 * @param value
		 * @return Vector<T_U, size>
		 */
		template<operator_T_U<T, T, T> operation>
		inline Vector<T, size>  vectorValueOperation ( T value ) const
			{
			Vector<T, size> ans;
			T* it_ans = ans.x;
			const T* it_this = x;
			const T* it_this_end = x+size;

			// iterate over all fields and execute operation on each corresponding fields
			while ( it_this != it_this_end )
				*it_ans++ = operation ( *it_this++, value );

			return ans;
			}

		/**
		 * @brief Add value to each Vector element. Result is also Vector.
		 *
		 * @param value value to add
		 * @return Vector<T, size>
		 */
		Vector<T, size> operator+ ( T value ) const
			{
			return vectorValueOperation<add<T, T> > ( value );
			}

		/**
		 * @brief Subtract value from each Vector element. Result is also Vector.
		 *
		 * @param value value to subtract
		 * @return Vector<T, size>
		 */
		Vector<T, size> operator- ( T value ) const
			{
			return vectorValueOperation<subtract<T, T> > ( value );
			}

		/**
		 * @brief Multiply value by each Vector element. Result is also Vector.
		 *
		 * @param value value to multiply
		 * @return Vector<T, size>
		 */
		Vector<T, size> operator* ( T value ) const
			{
			return vectorValueOperation<multiply<T, T> > ( value );
			}

		/**
		 * @brief Divide by value each Vector element. Result is also Vector.
		 *
		 * @param value value as divisor
		 * @return Vector<T, size>
		 */
		Vector<T, size> operator/ ( T value ) const
			{
			if ( value == T ( 0 ) )
				throw std::runtime_error ( "Dividing by 0" );

			return vectorValueOperation<multiply<T, T> > ( 1/ value );
			}

		template<typename Tt, unsigned U>
		friend std::ostream& operator<< ( std::ostream& out, const Vector<Tt, U>& v );

		~Vector()
			{}
	};

/**
 * @brief Add Vector to value
 *
 * @tparam T type of Vector
 * @tparam size Vector size
 * @param value value to add
 * @param v vector
 * @return Vector<T, size>
 */
template<typename T, unsigned size>
Vector<T, size> operator+ ( T value, const Vector<T, size>& v )
	{
	return v + value;
	}

/**
 * @brief Subtract Vector from value
 *
 * @tparam T type of Vector
 * @tparam size Vector size
 * @param value value to be subtracted
 * @param v vector
 * @return Vector<T, size>
 */
template<typename T, unsigned size>
Vector<T, size> operator- ( T value, const Vector<T, size>& v )
	{
	return v.template vectorValueOperation<subtract_inverse<T, T, T>> ( value );
	}

/**
 * @brief Multiply Vector by value
 *
 * @tparam T type of Vector
 * @tparam size Vector size
 * @param value value to add
 * @param v vector
 * @return Vector<T, size>
 */
template<typename T, unsigned size>
Vector<T, size> operator* ( T value, const Vector<T, size>& v )
	{
	return v * value;
	}

template <typename Tt, unsigned U>
std::ostream& operator<< ( std::ostream& out, const Vector<Tt, U>& v )
	{
	out << "[ ";
	for ( Tt x : v.x )
		out << x << " ";
	out << "]";

	return out;
	}

#endif //VECTOR_HPP
