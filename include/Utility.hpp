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

#endif // UTILITY_HPP