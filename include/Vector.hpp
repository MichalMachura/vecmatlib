#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <type_traits>
#include <initializer_list>
#include <cassert>
#include <cmath>
#include <ostream>
#include <exception>

#include "Utility.hpp"

template<typename T, unsigned SIZE = 3>
struct Vector
	{
	public:
		static const unsigned length = SIZE;
	public:
		T x[SIZE];

	public:
		/**
		 * @brief Constract Vector with non initialized fields
		 *
		 */
		Vector()
			{
			}

		Vector ( const Vector< T, SIZE >& other )
			{
			T* it = this->x;
			const T* it_end = this->x + SIZE;
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
			T const* it_end = x + SIZE;
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
			if ( args.size() > SIZE )
				throw std::runtime_error ( "Too many arguments in constructor params." );

			T* it = x;
			T const* it_end = x + SIZE;
			for ( auto&& arg : args )
				*it++ = T ( arg );

			// fill rest by 0
			while ( it != it_end )
				*it++ = T ( 0 );
			}

		/**
		 * @brief Vector created from another vector could be smaller SIZE.
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
			static_assert ( size_U <= SIZE, "Too large Vector in constructor." );

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


		template<typename U>
		Vector<T, SIZE>& operator= ( const Vector<U, SIZE>& other )
			{
			Container::copy ( begin(), end(), other.begin() );

			return *this;
			}

		template<typename U>
		Vector<T, SIZE>& operator= ( const Vector<U, SIZE>&& other )
			{
			Container::copy ( begin(), end(), other.begin() );

			return *this;
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
		inline T* end() const
			{
			return begin()+SIZE;
			}

		/**
		 * @brief Return size of Vector
		 *
		 * @return unsigned
		 */
		inline static unsigned size()
			{
			return SIZE;
			}

		/**
		 * @brief Fill all vector fields by value
		 *
		 * @param value
		 */
		void fill ( T value )
			{
			Container::fill ( begin(), end(), value );
			}

		/**
		 * @brief Calculting dot product this Vector and
		 *
		 * other vector to
		 * @return T
		 */
		T dot ( const Vector<T, SIZE>& other ) const
			{
			T sum = T ( 0 );
			const T* it = x;
			const T* it_other = other.x;
			T const* it_end = x+SIZE;

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
		 * @brief Add corresponding Vectors elements  return it as corresponding Vector
		 *
		 * @tparam U type of second argument
		 * @tparam T_U = ( T()+U() ) output Vector type
		 * @param other second argument
		 * @return Vector<T_U, SIZE> result
		 */
		template<typename U,
				 typename T_U = decltype ( T()+U() )>
		inline Vector<T_U, SIZE> operator+ ( const Vector<U, SIZE>& other ) const
			{
			Vector<T_U, SIZE> ans;
			Container::executeContainersOperation <Add> ( *this, other, ans );

			return ans;
			}

		/**
		 * @brief Subtract corresponding Vectors elements  return it as corresponding Vector
		 *
		 * @tparam U type of second argument
		 * @tparam T_U = ( T()+U() ) output Vector type
		 * @param other second argument
		 * @return Vector<T_U, SIZE> result
		 */
		template<typename U,
				 typename T_U = decltype ( T()+U() )>
		inline Vector<T_U, SIZE> operator- ( const Vector<U, SIZE>& other ) const
			{
			Vector<T_U, SIZE> ans;
			Container::executeContainersOperation <Subtract> ( *this, other, ans );

			return ans;
			}

		/**
		 * @brief Multiply corresponding Vectors elements  return it as corresponding Vector
		 *
		 * @tparam U type of second argument
		 * @tparam T_U = ( T()+U() ) output Vector type
		 * @param other second argument
		 * @return Vector<T_U, SIZE> result
		 */
		template<typename U,
				 typename T_U = decltype ( T()+U() )>
		inline Vector<T_U, SIZE> operator* ( const Vector<U, SIZE>& other ) const
			{
			Vector<T_U, SIZE> ans;
			Container::executeContainersOperation <Multiply> ( *this, other, ans );

			return ans;
			}

		/**
		 * @brief Add Vector elements and value return it as Vector
		 *
		 * @tparam U value type
		 * @tparam T_U = ( T()+U() ) output Vector type
		 * @param other second argument
		 * @return Vector<T_U, SIZE> result
		 */
		template<typename U,
				 typename T_U = decltype ( T()+U() )>
		inline Vector<T_U, SIZE> operator+ ( U value ) const
			{
			Vector<T_U, SIZE> ans;
			Container::executeContainerValueOperation<Add> ( *this, value, ans );

			return ans;
			}

		/**
		 * @brief Subtract Vector elements and value return it as Vector
		 *
		 * @tparam U value type
		 * @tparam T_U = ( T()+U() ) output Vector type
		 * @param other second argument
		 * @return Vector<T_U, SIZE> result
		 */
		template<typename U,
				 typename T_U = decltype ( T()+U() )>
		inline Vector<T_U, SIZE> operator- ( U value ) const
			{
			Vector<T_U, SIZE> ans;
			Container::executeContainerValueOperation<Subtract> ( *this, value, ans );

			return ans;
			}

		/**
		 * @brief Multiply Vector elements and value return it as Vector
		 *
		 * @tparam U value type
		 * @tparam T_U = ( T()+U() ) output Vector type
		 * @param other second argument
		 * @return Vector<T_U, SIZE> result
		 */
		template<typename U,
				 typename T_U = decltype ( T()+U() )>
		inline Vector<T_U, SIZE> operator* ( U value ) const
			{
			Vector<T_U, SIZE> ans;
			Container::executeContainerValueOperation<Multiply> ( *this, value, ans );

			return ans;
			}

		/**
		 * @brief Divide Vector elements by value return it as Vector
		 *
		 * @tparam U value type
		 * @tparam T_U = ( T()+U() ) output Vector type
		 * @param other second argument
		 * @return Vector<T_U, SIZE> result
		 */
		template<typename U,
				 typename T_U = decltype ( T()+U() )>
		inline Vector<T_U, SIZE> operator/ ( U value ) const
			{
			if ( value == T ( 0 ) )
				throw std::runtime_error ( "Dividing by 0" );

			Vector<T_U, SIZE> ans;
			Container::executeContainerValueOperation<Multiply> ( *this, 1/value, ans );

			return ans;;
			}

		/* OPERATORS WITH ASSIGNMENT*/
		/**
		 * @brief Add Vector to this Vector.
		 *
		 * @tparam U type of second argument
		 * @param other second argument
		 * @return Vector<T, SIZE>& reference to this
		 */
		template<typename U>
		inline Vector<T, SIZE>& operator+= ( const Vector<U, SIZE>& other )
			{
			Container::executeContainersOperationAssign <Add> ( *this, other );

			return *this;
			}

		/**
		 * @brief Subtract Vector from this Vector.
		 *
		 * @tparam U type of second argument
		 * @param other second argument
		 * @return Vector<T, SIZE>& reference to this
		 */
		template<typename U>
		inline Vector<T, SIZE>& operator-= ( const Vector<U, SIZE>& other )
			{
			Container::executeContainersOperationAssign <Subtract> ( *this, other );

			return *this;
			}

		/**
		 * @brief Multiply element wise this Vector by other
		 *
		 * @tparam U type of second argument
		 * @param other second argument
		 * @return Vector<T, SIZE>& reference to this
		 */
		template<typename U>
		inline Vector<T, SIZE>& operator*= ( const Vector<U, SIZE>& other )
			{
			Container::executeContainersOperationAssign <Multiply> ( *this, other );

			return *this;
			}

		/**
		 * @brief Add value to this Vector
		 *
		 * @tparam U type of value
		 * @param value value to add to Vector
		 * @return Vector<T, SIZE>& this Vector
		 */
		template<typename U>
		inline Vector<T, SIZE>& operator+= ( U value )
			{
			Container::executeContainerValueOperationAssign<Add> ( *this, value );
			return *this;
			}

		/**
		 * @brief Subtract value from this Vector
		 *
		 * @tparam U type of value
		 * @param value value to subtract from Vector
		 * @return Vector<T, SIZE>& this Vector
		 */
		template<typename U>
		inline Vector<T, SIZE>& operator-= ( U value )
			{
			Container::executeContainerValueOperationAssign<Subtract> ( *this, value );
			return *this;
			}

		/**
		 * @brief Multiply this Vector by value
		 *
		 * @tparam U type of value
		 * @param value value to multiply by
		 * @return Vector<T, SIZE>& this Vector
		 */
		template<typename U>
		inline Vector<T, SIZE>& operator*= ( U value )
			{
			Container::executeContainerValueOperationAssign<Multiply> ( *this, value );
			return *this;
			}

		/**
		 * @brief Divide this Vector by value
		 *
		 * @tparam U type of value
		 * @param value value to add to Vector
		 * @return Vector<T, SIZE>& this Vector
		 */
		template<typename U>
		inline Vector<T, SIZE>& operator/= ( U value )
			{
			if ( value == T ( 0 ) )
				throw std::runtime_error ( "Dividing by 0" );

			Container::executeContainerValueOperationAssign<Multiply> ( *this, 1/value );
			return *this;
			}

		/**
		 * @brief Get reference to value from position idx
		 * Throw runtime_error while out of range.
		 *
		 * @param idx
		 * @return T&
		 */
		T& operator[] ( unsigned idx )
			{
			if ( ! ( idx < length ) )
				throw std::runtime_error ( "Out of range!" );

			return x[idx];
			}

		/**
		 * @brief Get value from position idx
		 * Throw runtime_error while out of range.
		 *
		 * @param idx position index
		 * @return T valeu at position idx
		 */
		T get ( unsigned idx )
			{
			if ( ! ( idx < length ) )
				throw std::runtime_error ( "Out of range!" );

			return x[idx];
			}

		/**
		 * @brief Set value at position idx
		 *
		 * @param idx position index
		 * @param value value to set
		 */
		void set ( unsigned idx, T value )
			{
			if ( idx < length )
				x[idx] = value;
			}

		template<typename Tt, unsigned U>
		friend std::ostream& operator<< ( std::ostream& out, const Vector<Tt, U>& v );

		~Vector()
			{}
	};

/**
 * @brief Add value to Vector
 *
 * @tparam T Vector type
 * @tparam U value type
 * @tparam T_U = ( T()+U() ) result Vector type
 * @tparam SIZE Vector size
 * @param value value to add
 * @param v Vector
 * @return Vector<T_U, SIZE>
 */
template<typename T,
		 typename U,
		 typename T_U = decltype ( T()+U() ),
		 unsigned SIZE>
inline Vector<T_U, SIZE> operator+ ( U value, const Vector<T, SIZE>& v )
	{
	return v + value;
	}

/**
 * @brief Subtract Vector from value => result Vector
 *
 * @tparam T Vector type
 * @tparam U value type
 * @tparam T_U = ( T()+U() ) result Vector type
 * @tparam SIZE Vector size
 * @param value value
 * @param v Vector to subtract
 * @return Vector<T_U, SIZE>
 */
template<typename T,
		 typename U,
		 typename T_U = decltype ( T()+U() ),
		 unsigned SIZE>
inline Vector<T_U, SIZE> operator- ( U value, const Vector<T, SIZE>& v )
	{
	Vector<T_U, SIZE> ans;
	Container::executeContainerValueOperation<SubtractInverse> ( v, value, ans );

	return ans;
	}

/**
 * @brief Multiply value and Vector => result Vector
 *
 * @tparam T Vector type
 * @tparam U value type
 * @tparam T_U = ( T()+U() ) result Vector type
 * @tparam SIZE Vector size
 * @param value value
 * @param v Vector
 * @return Vector<T_U, SIZE>
 */
template<typename T,
		 typename U,
		 typename T_U = decltype ( T()+U() ),
		 unsigned SIZE>
inline Vector<T_U, SIZE> operator* ( U value, const Vector<T, SIZE>& v )
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
