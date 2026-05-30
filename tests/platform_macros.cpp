 /*
 *  lib66 is free software; you can redistribute it and/or modify it under the
 *  terms of the GNU General Public License as published by the Free Software
 *  Foundation; either version 2 of the License, or (at your option) any later
 *  version.
 *
 *  lib66 is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 *  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 *  details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with lib66; if not, write to the Free Software Foundation, Inc., 59 Temple
 *  Place, Suite 330, Boston, MA  02111-1307  USA
 */

/**
 * \file          platform_macros.cpp
 *
 *      A test-file for the platform_macros header file.
 *
 * \library       lib66
 * \author        Chris Ahlstrom
 * \date          2025-01-30
 * \updates       2026-05-30
 * \license       See above.
 *
 *      This small program merely shows the PLATFORM_... macros actually
 *      selected for the build.
 *
 *      Results on various platforms are collected in test/macros.text.
 */

#include <cstdlib>                      /* EXIT_SUCCESS, EXIT_FAILURE       */
#include <iostream>                     /* std::cout, set::cerr             */

#include "lib66.hpp"                    /* lib66_version()                  */
#include "platform_macros.h"            /* Macros based on compile environ  */

/*
 *  main() routine.
 */

int
main (int /*argc*/, char * /*argv*/ [])
{
    std::cout
        << lib66_version() << " compiler & platform settings\n"
        << std::endl
        ;

    std::cout << "Compiler:\n" << std::endl;

#if defined __clang__
    std::cout
        << "   Clang (v. " << __clang_major__
        << "." << __clang_minor__
        << "." << __clang_patchlevel__
        << ")"
        << std::endl
        ;
#endif

#if defined __GNUC__
    std::cout
        << "   GnuC (v. " << __GNUC__
        << "." << __GNUC_MINOR__
        << "." << __GNUC_PATCHLEVEL__
        << ")"
#if defined __clang__
        << " extensions"
#endif
        << std::endl
        ;
#endif

#if defined __MINGW32__
    std::cout << "   __MINGW32__ defined" << std::endl;
#endif

#if defined __MINGW64__
    std::cout << "   __MINGW64__ defined" << std::endl;
#endif

#if defined _MSC_VER
    std::cout << "   _MSC_VER defined" << std::endl;
#endif

#if defined _WIN32
    std::cout << "   _WIN32 defined" << std::endl;
#endif

#if defined _WIN32_WINNT
    std::cout
        << "   _WIN32_WINNT = 0x" << std::hex << _WIN32_WINNT
        << std::endl
        ;
#endif

#if defined WIN32
    std::cout << "   WIN32 defined" << std::endl;
#endif

#if defined _WIN64
    std::cout << "   _WIN64 defined" << std::endl;
#endif

#if defined WIN64
    std::cout << "   WIN64 defined" << std::endl;
#endif

    std::cout << "\nPLATFORM macros:\n" << std::endl;

#if defined PLATFORM_32_BIT
    std::cout << "   32-bit" << std::endl;
#endif

#if defined PLATFORM_64_BIT
    std::cout << "   64-bit" << std::endl;
#endif

#if defined PLATFORM_CLANG
    std::cout << "   Clang compiler" << std::endl;
#endif

#if defined PLATFORM_CPP_98
    std::cout << "   C++98 compiler" << std::endl;
#endif

#if defined PLATFORM_CPP_11
    std::cout << "   C++11 compiler" << std::endl;
#endif

#if defined PLATFORM_CPP_14
    std::cout << "   C++14 compiler" << std::endl;
#endif

#if defined PLATFORM_CPP_17
    std::cout << "   C++17 compiler" << std::endl;
#endif

#if defined PLATFORM_CPP_20
    std::cout << "   C++20 compiler" << std::endl;
#endif

#if defined PLATFORM_CPP_26
    std::cout << "   C++26 compiler" << std::endl;
#endif

#if defined PLATFORM_CYGWIN
    std::cout << "   CYGWIN" << std::endl;
#endif

#if defined PLATFORM_FREEBSD
    std::cout << "   FreeBSD" << std::endl;
#endif

#if defined PLATFORM_GNU
    std::cout << "   GNU" << std::endl;
#endif

#if defined PLATFORM_UNIX
    std::cout << "   UNIX" << std::endl;
#endif

#if defined PLATFORM_LINUX
    std::cout << "   Linux" << std::endl;
#endif

#if defined PLATFORM_MACOSX
    std::cout << "   Mac OSX" << std::endl;
#endif

#if defined PLATFORM_IPHONE_OS
    std::cout << "   iPhone" << std::endl;
#endif

#if defined PLATFORM_MINGW
    std::cout << "   Mingw" << std::endl;
#endif


#if defined PLATFORM_MSVC
    std::cout << "   Microsoft Visual Studio" << std::endl;
#endif

#if defined PLATFORM_DEBUG
    std::cout << "   Debug build" << std::endl;
#endif

#if defined PLATFORM_RELEASE
    std::cout << "   Release build" << std::endl;
#endif

#if defined PLATFORM_WINDOWS
    std::cout << "   Windows" << std::endl;
#endif

#if defined PLATFORM_WINDOWS_32
    std::cout << "      Windows 32-bit" << std::endl;
#endif

#if defined PLATFORM_WINDOWS_64
    std::cout << "      Windows 64-bit" << std::endl;
#endif

#if defined PLATFORM_WINDOWS_UNICODE
    std::cout << "      Windows UNICODE" << std::endl;
#endif

#if defined PLATFORM_XSI
    std::cout << "   XSI" << std::endl;
#endif

#if defined PLATFORM_POSIX_API
    std::cout << "   POSIX API" << std::endl;
#endif

#if defined PLATFORM_POSIX_ERROR
    std::cout
        << "   POSIX error code " << std::dec << PLATFORM_POSIX_ERROR
        << std::endl
        ;
#endif

#if defined PLATFORM_POSIX_SUCCESS
    std::cout << "   POSIX success code " << PLATFORM_POSIX_SUCCESS << std::endl;
#endif

#if defined PLATFORM_GLOB
    std::cout << "   glob(3) supported" << std::endl;
#endif

    return EXIT_SUCCESS;
}

/*
 * platform_macros.cpp
 *
 * vim: sw=4 ts=4 wm=4 et ft=cpp
 */
