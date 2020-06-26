#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <exception>
#include <type_traits>

template<typename T, unsigned ROWS, unsigned COLS>
class Matrix;

template<typename T, unsigned SIZE>
struct Vector;

template<typename T, typename U, typename T_U = decltype ( T() + U() )>
using operator_T_U = T_U ( * ) ( T, U );

template<typename T, typename U, typename T_U>
inline T_U add ( T t, U u )
	{
	return t + u;
	}

template<typename T, typename U, typename T_U>
inline T_U subtract ( T t, U u )
	{
	return t - u;
	}

template<typename T, typename U, typename T_U>
inline T_U multiply ( T t, U u )
	{
	return t * u;
	}

template<typename T, typename U, typename T_U>
inline T_U divide ( T t, U u )
	{
	return t / u;
	}


template<typename T, typename U, typename T_U>
inline T_U subtract_inverse ( T t, U u )
	{
	return u - t;
	}


template<typename T, typename U, typename T_U = decltype ( T() + U() )>
struct Add
	{
	inline static T_U operation ( T t, U u )
		{
		return t + u;
		}

	inline static void operationAssign ( T& t, const U u )
		{
		t += u;
		}
	};


template<typename T, typename U, typename T_U = decltype ( T() - U() )>
struct Subtract
	{
	inline static T_U operation ( T t, U u )
		{
		return t - u;
		}

	inline static void operationAssign ( T& t, const U u )
		{
		t -= u;
		}
	};

template<typename T, typename U, typename T_U = decltype ( T() * U() )>
struct Multiply
	{
	inline static T_U operation ( T t, U u )
		{
		return t * u;
		}

	inline static void operationAssign ( T& t, const U u )
		{
		t *= u;
		}
	};

template<typename T, typename U, typename T_U = decltype ( T() / U() )>
struct Divide
	{
	inline static T_U operation ( T t, U u )
		{
		return t / u;
		}

	inline static void operationAssign ( T& t, const U u )
		{
		t /= u;
		}
	};


template<typename T, typename U, typename T_U = decltype ( U() - T() )>
struct SubtractInverse
	{
	inline static T_U operation ( T t, U u )
		{
		return u - t;
		}
	};

namespace Container
	{
	// type pointed by Iterator
	template<typename Iterator>
	using ret_type = typename std::remove_reference< decltype ( *Iterator() )>::type;

	/**
	 * @brief Sum all elements in range
	 *
	 * @tparam Iterator Forward iterator
	 * @tparam ConstIterator Const Forward iterator
	 * @param it_beg iterator at range beginning
	 * @param it_end iterator after end of range
	 * @return ret_type<Iterator> sum value
	 */
	template<typename Iterator,
			 typename ConstIterator >
	inline ret_type<Iterator> sum ( Iterator it_beg, ConstIterator it_end )
		{
		ret_type<Iterator> aux ( 0 );

		// iterate over all fields and sum each
		while ( it_beg != it_end )
			aux += *it_beg++;

		return aux;
		}

	/**
	 * @brief Multiplication of all elements in range
	 *
	 * @tparam Iterator Forward Iterator
	 * @tparam ConstIterator Const Forward Iterator
	 * @param it_beg iterator at beginning of range
	 * @param it_end iterator after end of range
	 * @return ret_type<Iterator>  multiplication value
	 */
	template<typename Iterator,
			 typename ConstIterator >
	inline ret_type<Iterator> mul ( Iterator it_beg, ConstIterator it_end )
		{
		ret_type<Iterator> aux ( 1.0 );
		// iterate over all fields and multiply by each
		while ( it_beg != it_end )
			aux *= *it_beg++;

		return aux;
		}

	template<class C>
	inline auto sum ( const C& container )
	-> decltype ( sum ( container.begin(), container.end() ) )
		{
		return sum ( container.begin(), container.end() );
		}

	template<class C>
	inline auto mul ( const C& container )
	-> decltype ( mul ( container.begin(), container.end() ) )
		{
		return mul ( container.begin(), container.end() );
		}

	/**
	 * @brief /**
	 * @brief Fill all elements in range by value
	 *
	 * @tparam Iterator Forward Iterator
	 * @tparam ConstIterator Const Forward Iterator
	 * @param it_beg iterator at beginning of range
	 * @param it_end iterator after end of range
	 * @param value value to fill by
	 */
	template<typename Iterator,
			 typename ConstIterator >
	inline void fill ( Iterator it_beg, ConstIterator it_end, ret_type<Iterator> value )
		{
		// iterate over all fields
		while ( it_beg != it_end )
			*it_beg++ = value;
		}


	template<typename Iterator1,
			 typename ConstIterator1,
			 typename Iterator2 >
	inline void copy ( Iterator1 it_beg, ConstIterator1 it_end, Iterator2 it_beg2 )
		{
		// iterate over all fields
		while ( it_beg != it_end )
			*it_beg++ = *it_beg2++;
		}

	/* OPERATION */
	/**
	 * @brief Execute operation on range of elements
	 * Containers pointered by out_beg and second_beg must be the same size
	 * as container pointered by first_beg
	 *
	 * @tparam operation operation to execution on corresponding container elements
	 * @tparam Iterator1 Forward Iterator
	 * @tparam ConstIterator1 Const Forward Iterator
	 * @tparam Iterator2 Forward Iterator
	 * @tparam Iterator3 Forward Iterator
	 * @param first_beg iterator at beginning of range first container
	 * @param first_end iterator after end of range first container
	 * @param second_beg iterator at beginning of range second container
	 * @param out_beg iterator at beginning of range output container
	 */
	template<template<typename, typename, typename> class operation,
			 typename Iterator1,
			 typename ConstIterator1,
			 typename Iterator2,
			 typename Iterator3>
	inline void rangeElemetsOperation ( Iterator1 first_beg,
										ConstIterator1 first_end,
										Iterator2 second_beg,
										Iterator3 out_beg  )
		{
		// iterate over all fields and execute operation on each corresponding fields
		while ( first_beg != first_end )
			*out_beg++ = operation<ret_type<Iterator1>, ret_type<Iterator2>, ret_type<Iterator3>>::operation
						 ( *first_beg++, *second_beg++ );
		}

	/**
	 * @brief Execute operation between Container operation and value
	 * Container pointered by out_beg must be the same size
	 * as container pointered by first_beg
	 *
	 * @tparam operation operation to execution on corresponding container elements
	 * @tparam Iterator1 Forward Iterator
	 * @tparam ConstIterator1 Const Forward Iterator
	 * @tparam T2 value type
	 * @tparam Iterator3 Forward Iterator
	 * @param first_beg iterator at beginning of range first container
	 * @param first_end iterator after end of range first container
	 * @param value second operation argument
	 * @param out_beg iterator at beginning of range output container
	 */
	template<template<typename, typename, typename> class operation,
			 typename Iterator1,
			 typename ConstIterator1,
			 typename T2,
			 typename Iterator3>
	inline void rangeElemetsValueOperation ( Iterator1 first_beg,
			ConstIterator1 first_end,
			T2 value,
			Iterator3 out_beg  )
		{
		// iterate over all fields and execute operation on each corresponding fields
		while ( first_beg != first_end )
			*out_beg++ = operation<ret_type<Iterator1>, T2, ret_type<Iterator3>>::operation
						 ( *first_beg++, value );
		}

	/**
	 * @brief Execute operation on containers.
	 * Conteiners must be the same size!
	 *
	 * @tparam operation structure with defined static method type3 operation(type1, type2).
	 * @tparam T container1 type
	 * @tparam U container2 type
	 * @tparam T_U = ( T() +U() ) container out type
	 * @param in_container1 first arguments
	 * @param in_container2 second arguments
	 * @param out_container3 results
	 */
	template<template<typename, typename, typename> class operation,
			 typename T,
			 typename U,
			 typename T_U = decltype ( T() +U() )>
	inline void executeContainersOperation ( const T& in_container1, const U& in_container2, T_U& out_container3 )
		{
		rangeElemetsOperation<operation> ( in_container1.begin(),
										   in_container1.end(),
										   in_container2.begin(),
										   out_container3.begin() );
		}

	/**
	 * @brief Execute operation on container and value.
	 * Conteiners must be the same size!
	 *
	 * @tparam operation structure with defined static method type3 operation(type1, type2).
	 * @tparam T container1 type
	 * @tparam U container2 type
	 * @tparam T_U = ( T() +U() ) container out type
	 * @param in_container1 first arguments
	 * @param value second arguments
	 * @param out_container3 results
	 */
	template<template<typename, typename, typename> class operation,
			 typename T,
			 typename U,
			 typename T_U = decltype ( T() +U() )>
	inline void executeContainerValueOperation ( const T& in_container1, U value, T_U& out_container3 )
		{
		rangeElemetsValueOperation<operation> ( in_container1.begin(),
												in_container1.end(),
												value,
												out_container3.begin() );
		}

	/* OPERATION WITH ASSIGN */
	/**
	 * @brief Execute operation with asssign to first container elements on range of elements
	 * Container pointered by second_beg must be the same size
	 * as container pointered by first_beg
	 *
	 * @tparam operation operation to execution on corresponding container elements
	 * @tparam Iterator1 Forward Iterator
	 * @tparam ConstIterator1 Const Forward Iterator
	 * @tparam Iterator2 Forward Iterator
	 * @param first_beg iterator at beginning of range first container
	 * @param first_end iterator after end of range first container
	 * @param second_beg iterator at beginning of range second container
	 */
	template<template<typename, typename, typename> class operation,
			 typename Iterator1,
			 typename ConstIterator1,
			 typename Iterator2>
	inline void rangeElemetsOperationAssign ( Iterator1 first_beg,
			ConstIterator1 first_end,
			Iterator2 second_beg  )
		{
		// iterate over all fields and execute operation on each corresponding fields
		while ( first_beg != first_end )
			operation<ret_type<Iterator1>, ret_type<Iterator2>, ret_type<Iterator1>>::operationAssign
					( *first_beg++, *second_beg++ );
		}

	/**
	 * @brief Execute operation between Container operation
	 * and value with assign result to first container
	 *
	 * @tparam operation operation to execution on corresponding container elements
	 * @tparam Iterator Forward Iterator
	 * @tparam ConstIterator Const Forward Iterator
	 * @tparam T2 value type
	 * @param first_beg iterator at beginning of range first container
	 * @param first_end iterator after end of range first container
	 * @param value second operation argument
	 */
	template<template<typename, typename, typename> class operation,
			 typename Iterator1,
			 typename ConstIterator1,
			 typename T2>
	inline void rangeElemetsValueOperationAssign ( Iterator1 first_beg,
			ConstIterator1 first_end,
			T2 value )
		{
		// iterate over all fields and execute operation on each corresponding fields
		while ( first_beg != first_end )
			operation<ret_type<Iterator1>, T2, ret_type<Iterator1>>::operationAssign
					( *first_beg++, value );
		}

	/**
	 * @brief Execute operation on containers with assign result to in_container1.
	 * Conteiners must be the same size!
	 *
	 * @tparam operation structure with defined static method type3 operation(type1, type2).
	 * @tparam T container1 type
	 * @tparam U container2 type
	 * @param in_container1 first arguments
	 * @param in_container2 second arguments
	 */
	template<template<typename, typename, typename> class operation,
			 typename T,
			 typename U>
	inline void executeContainersOperationAssign ( T& in_container1, const U& in_container2 )
		{
		rangeElemetsOperationAssign<operation> ( in_container1.begin(),
				in_container1.end(),
				in_container2.begin() );
		}

	/**
	 * @brief Execute operation on container and value with assign result to container.
	 *
	 * @tparam operation structure with defined static method type3 operation(type1, type2).
	 * @tparam T container1 type
	 * @tparam U value type
	 * @param in_container1 first arguments
	 * @param value second arguments
	 * @param out_container3 results
	 */
	template<template<typename, typename, typename> class operation,
			 typename T,
			 typename U>
	inline void executeContainerValueOperationAssign ( const T& in_container1, U value )
		{
		rangeElemetsValueOperationAssign<operation> ( in_container1.begin(),
				in_container1.end(),
				value );
		}

	}

#endif // UTILITY_HPP