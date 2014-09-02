#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "ppport.h"

#ifdef __MINGW32__
#include <stdint.h>
#endif

#ifdef _MSC_VER
#include <stdlib.h>
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#endif

#define MATH_INT64_NATIVE_IF_AVAILABLE 1
#include "perl_math_int64.h"

#define U64 uint64_t
#define I64 int64_t

#endif
