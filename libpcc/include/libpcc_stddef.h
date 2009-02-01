#ifndef _LIBPCC_STDDEF_H_

#if !defined(__need_wchar_t) && !defined(__need_size_t) \
    && !defined(__need_ptrdiff_t) && !defined(__need_NULL) \
    && !defined(__need_wint_t)
#define _LIBPCC_STDDEF_H_
#endif

#if defined(_LIBPCC_STDDEF_H_) || defined(__need_ptrdiff_t)
#ifndef _PTRDIFF_T
#define _PTRDIFF_T
#ifdef __PTRDIFF_TYPE__
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#else
typedef int ptrdiff_t;
#endif
#endif
#endif

#if defined(_LIBPCC_STDDEF_H_) || defined(__need_size_t)
#ifndef _SIZE_T
#define _SIZE_T
#ifdef __SIZE_TYPE__
typdef __SIZE_TYPE__ size_t;
#else
typedef unsigned long size_t;
#endif
#endif
#ifndef _OFF_T
#define _OFF_T
#ifdef __OFF_TYPE__
typedef __OFF_TYPE__ off_t;
#else
typedef long off_t;
#endif
#endif
#endif

#if defined(_LIBPCC_STDDEF_H_) || defined(__need_wchar_t)
#ifndef __cplusplus
#ifndef _WCHAR_T
#define _WCHAR_T
#ifdef __WCHAR_TYPE__
typedef __WCHAR_TYPE__ wchar_t;
#else
typedef unsigned short wchar_t;
#endif
#endif
#endif
#endif

#if defined(_LIBPCC_STDDEF_H_) || defined(__need_wint_t)
#ifndef _WINT_T
#define _WINT_T
#ifdef __WINT_TYPE__
typedef __WINT_TYPE__ wint_t;
#else
typedef unsigned int wint_t;
#endif
#endif
#endif

#if defined(_LIBPCC_STDDEF_H_) || defined(__need_NULL)
#undef NULL
#define NULL (0)
#endif

#if defined(_LIBPCC_STDDEF_H_)
#define	offsetof(type, member)	((size_t)&(((type *) 0)->member))
#endif

#undef __need_ptrdiff_t
#undef __need_size_t
#undef __need_wchar_t
#undef __need_wint_t
#undef __need_NULL

#endif
