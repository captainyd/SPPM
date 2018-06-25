/*
Orchid source code is Copyright(c) 2018
Li Wei.
This file is part of Orchid.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:
- Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#ifdef  _MSC_VER
#pragma once
#endif //  _MSC_VER

#ifndef _COMMONH_
#define _COMMONH_

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <string>
#include <typeinfo>
#include <type_traits>

// ----------------------------------------------------------------------------
// Parameter constants
// ----------------------------------------------------------------------------
static const double PI = 4.0 * atan(1.0);
static const double INV_PI = 1.0 / PI;
static const double INFTY = 1.0e32;
static const double EPS = 1.0e-6;

#if (defined(WIN32) || defined(_WIN32) || defined(WINCE) || defined(__CYGWIN__))
#   define PACKED(__declare__) __pragma(pack(push,1)) __declare__ __pragma(pack(pop)) 
#else
#   define PACKED(__declare__) __declare__ __attribute__((__packed__))
#endif

// ----------------------------------------------------------------------------
// Parallel for
// ----------------------------------------------------------------------------
#ifdef _OPENMP
#include <omp.h>
#if defined(_WIN32) || defined(__WIN32__)
#define ompfor __pragma(omp parallel for) for
#define omplock __pragma(omp critical)
#else
#define ompfor _Pragma("omp parallel for") for
#define omplock _Pragma("omp critical")
#endif
const int kNumThreads = omp_get_max_threads();
inline int omp_thread_id() { return omp_get_thread_num(); }
#else  // _OPENMP
#define ompfor for
#define omplock
const int kNumThreads = 1;
inline int omp_thread_id() { return 0; }
#endif  // _OPENMP


// -----------------------------------------------------------------------------
// Alignment
// -----------------------------------------------------------------------------

#if defined(_WIN32) || defined(__WIN32__)
#define align_attrib(typ, siz) __declspec(align(siz)) typ
#else
#define align_attrib(typ, siz) typ __attribute__((aligned(siz)))
#endif

#if defined(_WIN32) || defined(__WIN32__)
inline void* align_alloc(size_t size, size_t alignsize) {
	return _aligned_malloc(size, alignsize);
}
inline void align_free(void* mem) { _aligned_free(mem); }
#else
inline void* align_alloc(size_t size, size_t alignsize) {
	void* mem = nullptr;
	int ret = posix_memalign((void**)&mem, alignsize, size);
	return (ret == 0) ? mem : nullptr;
}
inline void align_free(void* mem) { free(mem); }
#endif

// -----------------------------------------------------------------------------
// Message handlers
// -----------------------------------------------------------------------------

#ifndef NDEBUG
#define OrchidInfo(MSG) \
do { \
    std::cout << "[INFO] " << (MSG) << std::endl; \
} while (false);
#define OrchidWarn(MSG) \
do { \
    std::cerr << "[WARNING] " << (MSG) << std::endl; \
} while (false);
#else
#define OrchidInfo(MSG)
#define OrchidWarn(MSG)
#endif
#define OrchidError(MSG) \
do { \
    std::cerr << "[ERROR] " << (MSG) << std::endl; \
    std::abort(); \
} while (false);

// -----------------------------------------------------------------------------
// Assertion with message
// -----------------------------------------------------------------------------
#ifndef __FUNCTION_NAME__
#if defined(_WIN32) || defined(__WIN32__)
#define __FUNCTION_NAME__ __FUNCTION__
#else
#define __FUNCTION_NAME__ __func__
#endif
#endif

#define Assertion(PREDICATE, MSG) \
do {\
if (!(PREDICATE)) {	\
	std::cerr << "Asssertion \"" \
	<< #PREDICATE << "\" failed in " << __FILE__ \
	<< " line " << __LINE__ \
	<< " in function \"" << (__FUNCTION_NAME__) << "\"" \
	<< " : " << (MSG) << std::endl; \
	std::abort(); \
} \
} while (false)


// ----------------------------------------------------------------------------
// Utility functions
// ----------------------------------------------------------------------------

extern void* enabler;

template <class T,
	typename std::enable_if<std::is_arithmetic<T>::value>::type *& = enabler>
	inline T clamp(T v, T lo, T hi) {
	if (v < lo) v = lo;
	if (v > hi) v = hi;
	return v;
}

template <class T,
	typename std::enable_if<std::is_arithmetic<T>::value>::type *& = enabler>
	inline T max3(T a, T b, T c) {
	return std::max(a, std::max(b, c));
}

template <class T,
	typename std::enable_if<std::is_arithmetic<T>::value>::type *& = enabler>
	inline T min3(T a, T b, T c) {
	return std::min(a, std::min(b, c));
}

#endif // !_COMMONH_
