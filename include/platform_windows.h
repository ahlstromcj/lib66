#if ! defined LIB66_PLATFORM_WINDOWS_H
#define LIB66_PLATFORM_WINDOWS_H

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
 * \file          platform_windows.h
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
 *  This header file checks for Windows (Windows API), Cygwin (POSIX API),
 *  and Mingw (Windows API).
 *
 *  _WIN32:
 *
 *      The most universal macro is _WIN32 across all C compilers.
 *      The standard macro for any Windows environment (32-bit or 64-bit)
 *      across almost all modern compilers like MSVC, GCC, and Clang.
 *
 *  _WIN64:
 *
 *      Identifies 64-bit Windows environments. On 64-bit systems, it is
 *      defined for compatibility reasons by all major compilers including
 *      MSVC++, GCC, and Clang.
 *
 *  __WIN32__:
 *
 *      Often used by older compilers like Borland C++.
 *
 *  __WINDOWS__:
 *
 *      Primarily used by Watcom C/C++.
 *
 *  WIN32:
 *
 *      While common, often a user-defined project setting rather than a
 *      built-in compiler macro; safer to rely on the underscored version.
 *      This header file makes sure it is defined.
 *
 *  __CYGWIN__:
 *
 *      Defined when compiling in the Cygwin environment.
 *
 *  __MINGW32__ / __MINGW64__:
 *
 *      Defined when using MinGW (GCC for Windows).
 */

#undef PLATFORM_WINDOWS
#undef PLATFORM_WINDOWS_32
#undef PLATFORM_WIN32_STRICT
#undef PLATFORM_WINDOWS_64
#undef PLATFORM_WINDOWS_UNICODE
#undef PLATFORM_CYGWIN
#undef PLATFORM_POSIX_API
#undef PLATFORM_MINGW
#undef PLATFORM_MINGW_W32
#undef PLATFORM_MINGW_W64

#if defined Windows                     /* defined by nar-maven-plugin      */
#define PLATFORM_WINDOWS 1
#endif

#if defined _WIN32 || defined WIN32     /* most compilers, and Mingw        */
#define Windows
#define PLATFORM_WINDOWS 1
#define PLATFORM_WINDOWS_32 1
#endif

#if defined _WIN64 || defined WIN64     /* Microsoft and Mingw?             */
#define Windows
#define PLATFORM_WINDOWS_64 1
#define PLATFORM_WINDOWS 1
#endif

/**
 *  Provides macros that mean 32-bit, and only 32-bit Windows.  For
 *  example, in Windows, _WIN32 is defined for both 32- and 64-bit
 *  systems, because Microsoft didn't want to break people's 32-bit code.
 *  So we need a specific macro.
 *
 *      -  PLATFORM_32_BIT is defined on all platforms. ????????????
 *      -  WIN32 is defined on Windows platforms.
 *
 *  Prefer the former macro.  The second is defined only for legacy
 *  purposes for Windows builds, and might eventually disappear.
 */

#if defined PLATFORM_WINDOWS

#if defined _WIN32 && ! defined _WIN64 && ! defined WIN32
#define WIN32 1                         /* defined for legacy purposes      */
#endif

#if defined _WIN64 && ! defined WIN64
#define WIN64 1
#endif

/*
 *  Without this #define, the InitializeCriticalSectionAndSpinCount() function
 *  is undefined.  This version level means "Windows 2000 and higher".
 *  For Windows 10, the value would be 0x0A00.
 */

#if ! defined _WIN32_WINNT
#define _WIN32_WINNT        0x0500
#endif

#if defined UNICODE || defined _UNICODE
#define PLATFORM_WINDOWS_UNICODE 1
#endif

#endif                                  /* PLATFORM_WINDOWS                 */

/**
 *  Set up for Cygwin. A short section, so we include it here for
 *  convenience.
 *
 *  Note that Cygwin maps the POSIX API to Windows, so we define
 *  PLATFORM_POSIX_API here as well.
 */

#if defined __CYGWIN__

#define PLATFORM_CYGWIN 1
#define PLATFORM_POSIX_API 1

#if defined __CYGWIN32__
#define PLATFORM_WINDOWS_32 1
#elif defined __CYGWIN64__
#endif
#define PLATFORM_WINDOWS_64 1

#elif defined PLATFORM_WINDOWS_32

/*
 * PLATFORM_WIN32_STRICT replaces checks for WIN32 with CYGWIN undefined.
 */

#define PLATFORM_WIN32_STRICT 1         /* i.e. not Cygwin or Win 64        */

#endif

/**
 *  Set up for Mingw. A short section, so we include it here for
 *  convenience.
 *
 *  MinGW (Minimalist GNU for Windows) uses the native Windows Win32 API.
 *  It creates executables that run directly on Windows without external
 *  compatibility layers.
 *
 *  Macros:
 *
 *      __MINGW32__: Defined in both 32-bit and 64-bit MinGW
 *      __MINGW64__: Defined specifically for the 64-bit MinGW.
 *      _WIN32: Defined for any Windows target, including MinGW and MSVC.
 *      _WIN64: Defined when targeting 64-bit Windows.
 *
 *      Note that the latter two will automatically define the macros
 *      Windows, PLATFORM_WINDOWS, PLATFORM_WINDOWS_32, and
 *      PLATFORM_WINDOWS_64.
 *
 *  Version Macros:
 *
 *      __GNUC__: The major version of the GCC compiler.
 *      __GNUC_MINOR__: The minor version of the GCC compiler.
 *      __GNUC_PATCHLEVEL__: The patch level of the GCC compiler.
 *      __MINGW32_MAJOR_VERSION / __MINGW32_MINOR_VERSION: runtime version.
 *      __MINGW64_VERSION_MAJOR / __MINGW64_VERSION_MINOR: Similar.
 */

#if defined __MINGW32__
#define PLATFORM_MINGW 1
#define PLATFORM_MINGW_W32 1
#endif

#if defined __MINGW64__
#define PLATFORM_MINGW 1
#define PLATFORM_MINGW_W64 1
#endif

#endif                                  /* LIB66_PLATFORM_WINDOWS_H         */

/*
 * platform_windows.h
 *
 * vim: ts=4 sw=4 wm=4 et ft=c
 */
