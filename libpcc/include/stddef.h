#ifndef _STDDEF_H_

#if !defined(__need_wchar_t) && !defined(__need_size_t) \
    && !defined(__need_ptrdiff_t) && !defined(__need_NULL) \
    && !defined(__need_wint_t)
#define _STDDEF_H_
#endif

#if defined(__STDDEF_H__) || defined(__need_ptrdiff_t)
#ifndef _PTRDIFF_T_
#define _PTRDIFF_T_
typedef int ptrdiff_t;
#endif
#endif

#if defined(_STDDEF_H_) || defined(__need_size_t)
#ifndef _SIZE_T_
#define _SIZE_T_
typedef unsigned int size_t;
#endif
#endif

#if defined(_STDDEF_H_) || defined(__need_wchar_t)
#ifndef __cplusplus
#ifndef _WCHAR_T_
#define _WCHAR_T_
typedef unsigned short wchar_t;
#endif
#endif
#endif

#if defined(_STDDEF_H_) || defined(__need_wint_t)
#ifndef _WINT_T_
#define _WINT_T_
typedef short wint_t;
#endif
#endif

#if defined(_STDDEF_H_) || defined(__need_NULL)
#undef NULL
#define NULL (0)
#endif

#if defined(_STDDEF_H_)
#define	offsetof(type, member)	((size_t)&(((type *) 0)->member))
#endif

#undef __need_ptrdiff_t
#undef __need_size_t
#undef __need_wchar_t
#undef __need_wint_t
#undef __need_NULL

#endif
