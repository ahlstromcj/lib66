#if ! defined LIB66_BUILD_MACROS_H
#define LIB66_BUILD_MACROS_H

/*
 *  This file is part of lib66.
 *
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
 * \file          lib_build_macros.h
 *
 *  Macros that depend upon the build platform.
 *
 * \library       lib66
 * \author        Chris Ahlstrom
 * \date          2025-01-30
 * \updates       2025-01-30
 * \license       See above.
 *
 * Introduction:
 *
 *      We have two ways of configuring the build for the "lib66" set of
 *      libraries.  This file presents declarations that depend upon the
 *      build platform, and build options that might be considered permanent.
 *
 *      We need to consolidate, somehow, all of the platform-based settings
 *      files for the "Xxx66" projects.
 */

#include "platform_macros.h"            /* generic detecting of OS platform */

/**
 *  To do: improve the naming
 */

#if defined LIB66_EXPORT                /* exporting code                   */

#if defined PLATFORM_WINDOWS || defined PLATFORM_CYGWIN

#define LIB66_DLL_PUBLIC   __declspec(dllexport)
#define LIB66_API          __declspec(dllexport)

#else

#if PLATFORM_GNUC >= 4
#define LIB66_DLL_PUBLIC   __attribute__((visibility("default")))
#define LIB66_API          __attribute__((visibility("default")))
#else
#define LIB66_API
#define LIB66_DLL_PUBLIC
#endif

#endif

#else                                   /* not exporting code               */

#define LIB66_API
#define LIB66_DLL_PUBLIC

#endif

#endif          // LIB66_BUILD_MACROS_H

/*
 * lib_build_macros.h
 *
 * vim: sw=4 ts=4 wm=4 et ft=c
 */

