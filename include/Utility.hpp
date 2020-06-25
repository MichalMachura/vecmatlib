#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <exception>


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

namespace Container
{
	// type pointed by Iterator
	template<typename Iterator>
	using ret_type = typename std::remove_reference< decltype(*Iterator())>::type;
	
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
	inline ret_type<Iterator> sum(Iterator it_beg, ConstIterator it_end)
		{
		ret_type<Iterator> aux( 0 );
		
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
	inline ret_type<Iterator> mul(Iterator it_beg, ConstIterator it_end)
		{
		ret_type<Iterator> aux( 1.0 );
		// iterate over all fields and multiply by each
		while ( it_beg != it_end )
			aux *= *it_beg++;

		return aux;
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
	inline void fill(Iterator it_beg, ConstIterator it_end, ret_type<Iterator> value)
		{
		// iterate over all fields
		while ( it_beg != it_end )
			*it_beg++ = value;
		}
		
		/**
		 * @brief 
		 * 
		 * @tparam T operator argument types must be equivalent to ret_type<Iterator>
		 * @tparam operation 
		 * @tparam Iterator Forward Iterator
		 * @tparam ConstIterator Const Forward Iterator
		 * @param first_beg iterator at beginning of range first container
		 * @param first_end iterator after end of range first container
		 * @param second_beg iterator at beginning of range second container
		 * @param out_beg iterator at beginning of range output container
		 */
		template<typename T,
				operator_T_U<T, T, T> operation,
				typename Iterator, 
			 	typename ConstIterator>
		inline void rangeElemetsOperation ( Iterator first_beg, 
											 ConstIterator first_end,
											 Iterator second_beg,
											 Iterator out_beg  )
			{
			// iterate over all fields and execute operation on each corresponding fields
			while ( first_beg != first_end )
				*out_beg++ = operation ( *first_beg++, *second_beg++ );
			}
}

#endif // UTILITY_HPP