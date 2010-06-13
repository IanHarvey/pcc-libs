#ifndef _LIBPCC_LIMITS_H_
#define _LIBPCC_LIMITS_H_

#if defined __GNUC__
#  if !defined _GCC_LIMITS_H_
/* this is needed to make limits.h from the glibc headers happy, which uses
   #include_next <limits.h>
   when __GNUC__ is defined and  _GCC_LIMITS_H_ is not defined 
*/
#  define __GCC_LIMITS_H_
#  endif

#endif

#endif

