#if ! defined LIB66_CONFIG_H
#define LIB66_CONFIG_H

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
 * \file          lib66-config.h (lib66-config.h.in)
 *
 *      This header file provide "HAVE" definitions based on detected C/C++
 *      system header files.
 *
 * \library       lib66
 * \author        Chris Ahlstrom
 * \date          2022-07-01
 * \updates       2024-04-28
 * \license       GNU GPL v2 or above
 *
 *  This file is used mainly for system files and specific build options.  The
 *  main build options are detected at build time via the platform_macros.h
 *  module.
 *
 *  For information on this file, see
 *
 *      https://mesonbuild.com/Configuration.html
 *
 *  These #defines will define the macro value as True or False.
 *  The proper way to test the macro is:
 *
 *      #if LIB66_HAVE_LIMITS_H
 *
 *  We had an error on Arch Linux with "True" apparently not being detected as
 *  a boolean, so we add setting up True/False below. We should perhaps
 *  update this file to better match the descriptions at the URL above.
 */

#if ! defined True
#define True    1
#endif

#if ! defined False
#define False   0
#endif

// Add "LIB66_" ???

#define HAVE_LIMITS_H           True
#define HAVE_LINUX_LIMITS_H     True

#endif          // LIB66_CONFIG_H

/*
 * lib66-config.h (lib66-config.h.in)
 *
 * vim: sw=4 ts=4 wm=4 et ft=c
 */
