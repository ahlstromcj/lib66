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
 * \file          lib66.cpp
 *
 *  This module defines an informational function.
 *
 * \library       lib66
 * \author        Chris Ahlstrom
 * \date          2025-01-30
 * \updates       2025-01-30
 * \license       GNU GPLv2 or above
 *
 */

#include "lib66.hpp"                   /* no-namespace function library    */

#if defined __cplusplus

/*
 * Version information string. These are set in the main meson.build file.
 */

const std::string &
lib66_version () noexcept
{
    static std::string s_info = LIB66_NAME "-" LIB66_VERSION " " __DATE__ ;
    return s_info;
}

#endif          // defined __cplusplus

/*
 * lib66.cpp
 *
 * vim: sw=4 ts=4 wm=4 et ft=cpp
 */

