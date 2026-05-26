#if ! defined LIB66_PLATFORM_HARDWARE_H
#define LIB66_PLATFORM_HARDWARE_H

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
 * \file          platform_hardware.h
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
 *  To do: the Apple M chips
 *
 */

#undef PLATFORM_HARDWARE_AMD64
#undef PLATFORM_HARDWARE_ARM
#undef PLATFORM_HARDWARE_ARM64
#undef PLATFORM_HARDWARE_INTEL86
#undef PLATFORM_HARDWARE_ITANIUM                /* Intel Itanium (IA-64)    */
#undef PLATFORM_HARDWARE_POWERPC
#undef PLATFORM_HARDWARE_MIPS
#undef PLATFORM_HARDWARE_MYRIAD2                /* Intel Movidius           */

/*
 *  The first two are defined by GNU and Clang/LLVM, and the third
 *  by Visual Studio.
 */

#if defined __x86_64 || defined __x86_64__ || defined _M_X64
#define PLATFORM_HARDWARE_AMD64 1
#elif defined __amd64 || defined __arm64__      /* Clang and GNU            */
#define PLATFORM_HARDWARE_AMD64 1
#endif

/*
 *  32-bit compilers and Visual Studio. Not defined unless running on
 *  an ARM platform, apparently.
 */

#if defined __arm__ || defined _M_ARM
#define PLATFORM_HARDWARE_ARM 1
#endif

/*
 *  64-bit compilers and Visual Studio.
 */

#if defined __aarch64__ || defined _M_ARM64
#define PLATFORM_HARDWARE_ARM64 1
#endif

/*
 *  Intel x86.
 */

#if defined __i386__ || defined _M_IX86
#define PLATFORM_HARDWARE_INTEL86 1
#endif

/*
 * Intel Itanium (IA-64)
 */

#if defined __ia64__ || defined _M_IA64
#define PLATFORM_HARDWARE_ITANIUM 1
#endif

/*
 * Power PC
 */

#if defined __ppc__ || defined __PPC__
#define PLATFORM_HARDWARE_POWERPC 1
#endif

#if defined __ppc64__ || defined __PPC64__
#define PLATFORM_HARDWARE_POWERPC 1
#endif

#if defined PowerPC || defined _M_PPC
#define PLATFORM_HARDWARE_POWERPC 1
#endif

/*
 * MIPS
 */

#if defined __mips__
#define PLATFORM_HARDWARE_MIPS 1
#endif

/*
 * Myriad2.  Myriad Development Kit (Intel Movidius).
 */

#if defined __myriad2__
#define PLATFORM_HARDWARE_MIPS 1
#endif

#endif                  /* LIB66_PLATFORM_HARDWARE_H */

/*
 * platform_hardware.h
 *
 * vim: ts=4 sw=4 wm=4 et ft=c
 */
