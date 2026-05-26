#if ! defined LIB66_PLATFORM_POSIX_H
#define LIB66_PLATFORM_POSIX_H

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
 * \file          platform_posix.h
 *
 *  Provides a set of macros to make compile-time
 *  decisions covering POSIX-conformant operating systems.
 *
 * \library       Any application or library
 * \author        Chris Ahlstrom
 * \date          2026-05-26
 * \updates       2026-05-26
 * \license       GNU GPLv2 or above
 *
 * Linux, FreeeBSD, and MacOS are all POSIX-compliant or largely compliant.
 */

/**
 * Operating systems.
 */

#undef PLATFORM_UNIX
#undef PLATFORM_FREEBSD
#undef PLATFORM_NETBSD
#undef PLATFORM_OPENBSD
#undef PLATFORM_DRAGONBSD
#undef PLATFORM_LINUX
#undef PLATFORM_MACOSX
#undef PLATFORM_POSIX_API

/**
 *  It can be unix (unofficial) without being POSIX, we think.
 */

#if defined __unix__                    /* defined by the Clang compiler    */
#define PLATFORM_UNIX 1
#endif

/**
 *  BSD macros.
 *  To detect specific versions or additional BSD characteristics, you should
 *  include <sys/param.h>
 */

#if defined __FreeBSD__
#define PLATFORM_FREEBSD 1
#define PLATFORM_UNIX 1
#define PLATFORM_POSIX_API 1
#endif

#if defined __NetBSD__
#define PLATFORM_NETBSD 1
#define PLATFORM_UNIX 1
#define PLATFORM_POSIX_API 1
#endif

#if defined __OpenBSD__
#define PLATFORM_OPENBSD 1
#define PLATFORM_UNIX 1
#define PLATFORM_POSIX_API 1
#endif

#if defined __Dragonfly__               /* another BSD operating system     */
#define PLATFORM_DRAGONFLY 1
#define PLATFORM_UNIX 1
#define PLATFORM_POSIX_API 1
#endif

/**
 *  Provides a "Linux" macro, in case the environment doesn't provide it.
 *  This macro is defined if not already defined.
 */

#if defined Linux                       /* defined by nar-maven-plugin      */
#define PLATFORM_LINUX 1
#else
#if defined __linux__                   /* defined by the GNU compiler      */
#define Linux 1
#define PLATFORM_LINUX 1
#endif
#endif

#if defined PLATFORM_LINUX
#define PLATFORM_UNIX 1
#define PLATFORM_POSIX_API 1
#endif

/**
 *  Provides a "MacOSX" macro, in case the environment doesn't provide it.
 *  This macro is defined if not already defined and __APPLE__ and
 *  __MACH__ are encountered. __unix__ is not defined on Mac OS X.
 */

#if defined MacOSX
#define PLATFORM_MACOSX 1
#else
#if defined __APPLE__ && defined __MACH__
#define PLATFORM_MACOSX 1
#define MacOSX
#endif
#endif

#if defined PLATFORM_MACOSX
#define PLATFORM_UNIX 1
#define PLATFORM_POSIX_API 1
#endif

/*
 *  To do: detect these platforms.
 *
 * #define PLATFORM_IPHONE_OS
 * #define PLATFORM_ANDROID
 */

/**
 *  Universal macros; they adapt POSIX conventions.
 *
 *  Provides a check for error return codes from applications.  It is a
 *  non-error value for most POSIX-conformant functions.  This macro defines
 *  the integer value returned by many POSIX functions when they succeed --
 *  zero (0).
 *
 * \note
 *      Rather than testing this value directory, the macro functions
 *      is_posix_success() and not_posix_success() should be used.  See the
 *      descriptions of those macros for more information.
 */

#if ! defined PLATFORM_POSIX_SUCCESS
#define PLATFORM_POSIX_SUCCESS              0
#endif

/**
 *  PLATFORM_POSIX_ERROR is returned from a string function when it has
 *  processed an error.  It indicates that an error is in force.  Normally,
 *  the caller then uses this indicator to set a class-based error message.
 *  This macro defines the integer value returned by many POSIX functions when
 *  they fail -- minus one (-1).  The EXIT_FAILURE and
 *  PLATFORM_POSIX_ERROR macros also have the same value.
 *
 * \note
 *      Rather than testing this value directory, the macro functions
 *      is_posix_error() and not_posix_error() should be used.  See the
 *      descriptions of those macros for more information.
 */

#if ! defined PLATFORM_POSIX_ERROR
#define PLATFORM_POSIX_ERROR              (-1)
#endif

/*
 * Can also include unistd.h and use the _POSIX_VERSION macro.
 */

#if defined PLATFORM_POSIX_API
#define PLATFORM_PTHREADS 1
#define PLATFORM_UNIX 1
#define POSIX 1                        /* defined for legacy code purposes  */
#endif

/**
 *  Universally defined, regardless of environment.
 *
 *   These macro tests the integer value against PLATFORM_POSIX_SUCCESS.
 *   Other related macros are:
 *
 *       -  is_posix_success()
 *       -  is_posix_error()
 *       -  not_posix_success()
 *       -  not_posix_error()
 *       -  set_posix_success()
 *       -  set_posix_error()
 *
 * \note
 *      -   Some functions return values other than PLATFORM_POSIX_ERROR
 *          when an error occurs.
 *      -   Some functions return values other than
 *          PLATFORM_POSIX_SUCCESS when the function succeeds.
 *      -   Please refer to the online documentation for these quixotic
 *          functions, and decide which macro one want to use for the test, if
 *          any.
 *      -   In some case, one might want to use a clearer test.  For example,
 *          the socket functions return a result that is
 *          PLATFORM_POSIX_ERROR (-1) if the function fails, but
 *          non-zero integer values are returned if the function succeeds.
 *          For these functions, the is_valid_socket() and not_valid_socket()
 *          macros are much more appropriate to use.
 */

#if ! defined is_posix_success
#define is_posix_success(x)      ((x) == PLATFORM_POSIX_SUCCESS)
#endif

/**
 *  This macro tests the integer value against PLATFORM_POSIX_ERROR (-1).
 */

#if ! defined is_posix_error
#define is_posix_error(x)        ((x) == PLATFORM_POSIX_ERROR)
#endif

/**
 *  This macro tests the integer value against PLATFORM_POSIX_SUCCESS (0).
 */

#if ! defined not_posix_success
#define not_posix_success(x)     ((x) != PLATFORM_POSIX_SUCCESS)
#endif

/**
 *  This macro tests the integer value against PLATFORM_POSIX_ERROR (-1).
 */

#if ! defined not_posix_error
#define not_posix_error(x)       ((x) != PLATFORM_POSIX_ERROR)
#endif

/**
 *  This macro set the integer value to PLATFORM_POSIX_SUCCESS (0).  The
 *  parameter must be an lvalue, as the assignment operator is used.
 */

#if ! defined set_posix_success
#define set_posix_success(x)     ((x) = PLATFORM_POSIX_SUCCESS)
#endif

/**
 *  This macro set the integer value to PLATFORM_POSIX_ERROR (-1).  The
 *  parameter must be an lvalue, as the assignment operator is used.
 */

#if ! defined set_posix_error
#define set_posix_error(x)       ((x) = PLATFORM_POSIX_ERROR)
#endif

#endif                                  /* LIB66_PLATFORM_POSIX_H           */

/*
 * platform_posix.h
 *
 * vim: ts=4 sw=4 wm=4 et ft=c
 */
