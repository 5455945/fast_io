#pragma once

#ifdef __cpp_exceptions
#include<system_error>
#endif

#if defined(__linux__)
#ifdef __x86_64__
#include"amd64.h"
#endif
#endif

#include"terminate.h"


namespace fast_io
{

template<std::integral I>
requires(sizeof(I)>=1)
inline void system_call_throw_error(I v)
{
#if defined(__linux__) && defined(__x86_64__)
	using unsigned_t = std::make_unsigned_t<I>;
	if(static_cast<unsigned_t>(v)+static_cast<unsigned_t>(4096)<static_cast<unsigned_t>(4096))
#ifdef __cpp_exceptions
		throw std::system_error(static_cast<int>(-v),std::generic_category());
#else
		fast_terminate();
#endif
#else
	if(v<0)
#ifdef __cpp_exceptions
		throw std::system_error(errno,std::generic_category());
#else
		fast_terminate();
#endif
#endif
}

}