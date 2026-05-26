#if ! defined LIB66_PLATFORM_MACROS_H
#define LIB66_PLATFORM_MACROS_H

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
 * \file          platform_macros.h
 *
 *  Provides a rationale and a set of macros to make compile-time
 *  decisions covering Windows versus Linux, GNU versus Microsoft, and
 *  MINGW versus GNU.
 *
 * \library       Any application or library
 * \author        Chris Ahlstrom
 * \date          2015-07-24
 * \updates       2026-05-26
 * \license       GNU GPLv2 or above
 *
 *  Copyright (C) 2013-2026 Chris Ahlstrom <ahlstromcj@gmail.com>
 *
 *  We need a uniform way to specify OS and compiler features without
 *  littering the code with macros from disparate compilers.  Put all
 *  the compiler-specific stuff here to define "PLATFORM" macros.
 *
 * Settings to distinguish, based on compiler-supplied macros:
 *
 *    -  Platform macros:
 *       -  Windows
 *       -  Linux
 *       -  MacOSX
 *    -  Platform macros (in the absense of Windows, Linux macros):
 *      -   platform_windows.h
 *          -  PLATFORM_WINDOWS
 *          -  PLATFORM_WINDOWS_32
 *          -  PLATFORM_WIN32_STRICT
 *          -  PLATFORM_WINDOWS_64
 *          -  PLATFORM_WINDOWS_UNICODE
 *          -  PLATFORM_CYGWIN
 *          -  PLATFORM_MINGW
 *          -  PLATFORM_MINGW_W32
 *          -  PLATFORM_MINGW_W64
 *          -  PLATFORM_POSIX_API
 *      -   platform_posix.h
 *          -  PLATFORM_LINUX
 *          -  PLATFORM_FREEBSD, _NETBSD, _OPENBSD, _DRAGONFLY
 *          -  PLATFORM_MACOSX
 *          -  PLATFORM_IPHONE_OS (to do!)
 *          -  PLATFORM_UNIX
 *          -  PLATFORM_POSIX_API
 *    -  Architecture size macros:
 *       -  PLATFORM_32_BIT
 *       -  PLATFORM_64_BIT
 *    -  Debugging macros:
 *       -  PLATFORM_DEBUG
 *       -  PLATFORM_RELEASE
 *    -  platform_compilers.h:
 *       -  PLATFORM_CLANG
 *       -  PLATFORM_CYGWIN
 *       -  PLATFORM_GLOB
 *       -  PLATFORM_GNU
 *       -  PLATFORM_MSVC (alternative to _MSC_VER)
 *       -  PLATFORM_XSI
 *       -  UNUSED(x)
 *       -  UNUSED_FUNCTION(x)
 *       -  UNUSED_VOID(x)
 *       -  Language:
 *          -  PLATFORM_CPP_98
 *          -  PLATFORM_CPP_11
 *          -  PLATFORM_CPP_14
 *          -  PLATFORM_CPP_17
 *          -  PLATFORM_CPP_20
 *          -  PLATFORM_CPP_26
 *    -  platform_hardware.h:
 *          -  PLATFORM_HARDWARE_AMD64
 *          -  PLATFORM_HARDWARE_ARM
 *          -  PLATFORM_HARDWARE_ARM64
 *          -  PLATFORM_HARDWARE_INTEL86
 *          -  PLATFORM_HARDWARE_ITANIUM
 *          -  PLATFORM_HARDWARE_POWERPC
 *          -  PLATFORM_HARDWARE_MIPS
 *          -  PLATFORM_HARDWARE_MYRIAD2
 *    -  Other:
 *       -  PLATFORM_POSIX_ERROR
 *       -  PLATFORM_POSIX_SUCCESS
 *
 *  http://stackoverflow.com/questions/11053960/
 *      how-are-the-cplusplus-directive-defined-in-various-compilers
 *
 *    The 199711L stands for Year=1997, Month = 11 (i.e., November of 1997) --
 *    the date when the committee approved the standard that the rest of the
 *    ISO approved in early 1998.
 *
 *    For the 2003 standard, there were few enough changes that the committee
 *    (apparently) decided to leave that value unchanged.
 *
 *    For the 2011 standard, it's defined as 201103L, (year=2011, month = 03),
 *    meaning that the committee approved the standard as finalized in March
 *    of 2011.
 *
 *    For the 2014 standard, it's defined as 201402L, interpreted the same way
 *    as above (February 2014).
 *
 *    For the 2017 standard, it's defined as 201703L, interpreted the same way
 *    as above (March 2017).
 *
 *    For the 2020 standard, it's defined as 202002L.
 *
 *    Before the original standard was approved, quite a few compilers
 *    normally defined it as 0 (or just an empty definition like #define
 *    __cplusplus) to signify "not-conforming". When asked for their strictest
 *    conformance, many defined it to 1.  Ancient news!
 *
 * To do:
 *
 *  -   Memory models such as __LP64__
 *  -   OSes:
 *  -       __ros__ (Akaros)
 *  -       __Fuchsia__ (Fuchsia)
 *  -   Compilers:
 *  -       __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__
 *          PLATFORM_GCC_ONLY (defined __GNUC__ && ! defined __clang__
 *  -       __clang__, __clang_major__, __clang_minor__, __clang_patchlevel__
 *  -       _MSC_FULL_VER
 *
 */

#undef PLATFORM_32_BIT
#undef PLATFORM_64_BIT
#undef PLATFORM_DEBUG
#undef PLATFORM_GLOB
#undef PLATFORM_RELEASE

/**
 *  Provides a PLATFORM_WINDOWS macro plus a few more.
 *
 *  Provides a "Windows" macro, in case the environment doesn't provide
 *  it.  This macro is defined if not already defined and _WIN32 or WIN32
 *  are encountered.
 */

#include "platform_windows.h"
#include "platform_posix.h"
#include "platform_compilers.h"
#include "platform_hardware.h"

/**
 *  Set if the platform supports an implementation of glob(3)
 */

#if defined PLATFORM_UNIX || defined PLATFORM_MINGW
#define PLATFORM_GLOB 1
#endif

/*
 * Tie up some loose ends and define some "universal" macros.
 */

/**
 *  Provides macros that mean 64-bit, and only 64-bit.
 *
 *      -  PLATFORM_64_BIT is defined on all platforms.
 *      -  WIN64 is defined on Windows platforms.
 *
 *  Prefer the former macro.  The second is defined only for legacy
 *  purposes for Windows builds, and might eventually disappear.
 *
 *  DO THIS 32/64 bit detection after all the other settings.
 *
 */

#if defined PLATFORM_WINDOWS_32
#define PLATFORM_32_BIT 1
#endif

#if defined PLATFORM_WINDOWS_64
#define PLATFORM_64_BIT 1
#endif

#if defined PLATFORM_POSIX_API
#define PLATFORM_PTHREADS 1
#define POSIX 1                        /* defined for legacy code purposes  */
#endif

/**
 *  Provides macros that mean "debugging enabled".
 *
 *      -  PLATFORM_DEBUG or PLATFORM_RELEASE
 *      -  DEBUG or NDEBUG for legacy usage
 *
 * Prefer the former macro.  The second is defined only for legacy
 * purposes for Windows builds, and might eventually disappear.
 */

#if ! defined PLATFORM_DEBUG
#if defined DEBUG || defined _DEBUG || defined _DEBUG_ || \
 defined __DEBUG || defined __DEBUG__
#define PLATFORM_DEBUG 1
#endif
#endif

#if ! defined PLATFORM_DEBUG && ! defined PLATFORM_RELEASE
#define PLATFORM_RELEASE 1
#endif

#endif                  /* LIB66_PLATFORM_MACROS_H */

/*
 * platform_macros.h
 *
 * vim: ts=4 sw=4 wm=4 et ft=c
 */
