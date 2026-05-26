#if ! defined LIB66_PLATFORM_COMPILERS_H
#define LIB66_PLATFORM_COMPILERS_H

/*
 *  This file is free software; you can redistribute it and/or modify it under
 *  the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 2 of the License, or (at your option)
 *  any later version.
 *
 *  It is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 *  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 *  details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this file; if not, write to the Free Software Foundation, Inc., 59
 *  Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/**
 * \file          platform_compilers.h
 *
 *  Provides a rationale and a set of macros to make compile-time
 *  decisions covering Windows versus Linux, GNU versus Microsoft, and
 *  MINGW versus GNU.
 *
 * \library       Any application or library
 * \author        Chris Ahlstrom
 * \date          2026-05-26
 * \updates       2026-05-26
 * \license       GNU GPLv2 or above
 *
 * Compiler-Specific Detection.
 *
 *  To see exactly how Clang or Gcc detects the environment, what paths
 *  it is using, and all the #defines it sets up, run:
 *
 *      clang++ -v -dM -E - < /dev/null
 *      g++ -v -dM -E - < /dev/null
 *      Gcc:  cpp -dM myheaderfile
 */

#undef PLATFORM_CLANG
#undef PLATFORM_MSVC
#undef PLATFORM_GNU
#undef PLATFORM_XSI
#undef PLATFORM_CPP_98
#undef PLATFORM_CPP_11
#undef PLATFORM_CPP_14
#undef PLATFORM_CPP_17
#undef PLATFORM_CPP_20
#undef PLATFORM_CPP_26
#undef UNUSED
#undef UNUSED_FUNCTION
#undef UNUSED_VOID

/**
 *  Provides macros that indicate if Microsoft C/C++ versus GNU are being
 *  used.  THe compiler being used normally provides test macros for itself.
 *
 *      -  PLATFORM_CLANG (replaces __clang__)
 *      -  PLATFORM_MSVC (replaces _MSC_VER)
 *      -  PLATFORM_GNU (replaces __GNUC__)
 *      -  PLATFORM_XSI
 */

#if defined __clang__
#define PLATFORM_CLANG 1
#endif

#if defined _MSC_VER                    /* Microsoft Visual C/C++           */
#define PLATFORM_MSVC 1
#endif

#if defined __GNUC__
#define PLATFORM_GNU 1
#endif

#if (_POSIX_C_SOURCE >= 200112L) && ! _GNU_SOURCE
#define PLATFORM_XSI 1

/*
 * Hit this one compiling in Qt Creator on Linux.
 *
 * #error XSI defined, this is just a test
 */

#endif

/**
 *  Provides a way to flag unused parameters at each "usage", without
 *  disabling them globally.  Use it like this:
 *
 *     void foo(int UNUSED(bar)) { ... }
 *     static void UNUSED_FUNCTION(foo)(int bar) { ... }
 *
 *  The UNUSED macro won't work for arguments which contain parenthesis,
 *  so an argument like float (*coords)[3] one cannot do,
 *
 *      float UNUSED((*coords)[3]) or float (*UNUSED(coords))[3].
 *
 *  This is the only downside to the UNUSED macro; in these cases fall back to
 *
 *      (void) coords;
 *
 *  Another possible definition is casting the unused value to void in the
 *  function body.
 */

#if defined __GNUC__
#define UNUSED(x)               UNUSED_ ## x __attribute__((__unused__))
#endif

#if defined __GNUC__
#define UNUSED_FUNCTION(x)      __attribute__((__unused__)) UNUSED_ ## x
#endif

#define UNUSED_VOID(x)          (void) (x)

/**
 *  Provides macros to indicate the level standards support for some key
 *  cases.  We may have to play with this a bit to get it right.  The main
 *  use-case right now is in avoiding defining the nullptr macro in C++11.
 */

#if defined PLATFORM_MSVC

#if _MSC_VER >= 1700                /* __cplusplus value doesn't work, MS!  */
#define PLATFORM_CPP_11 1
#endif

#endif

#if __cplusplus == 199711L          /* i.e. C++11                           */
#define PLATFORM_CPP_98 1
#endif

#if __cplusplus == 201103L          /* i.e. C++11                           */
#define PLATFORM_CPP_11 1
#endif

#if __cplusplus == 201402L          /* i.e. C++14                           */
#define PLATFORM_CPP_14 1
#endif

#if __cplusplus == 201703L          /* i.e. C++17                           */
#define PLATFORM_CPP_17 1
#endif

#if __cplusplus == 202002L          /* i.e. C++20                           */
#define PLATFORM_CPP_20 1
#endif

#if __cplusplus > 202302L           /* i.e. C++26                           */
#define PLATFORM_CPP_26 1
#endif

#endif                                  /* LIB66_PLATFORM_COMPILERS_H       */

/*
 * platform_compilers.h
 *
 * vim: ts=4 sw=4 wm=4 et ft=c
 */
