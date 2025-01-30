#*****************************************************************************
# meson.build (lib66/include)
#-----------------------------------------------------------------------------
##
# \file        include/meson.build
# \library     lib66
# \author      Chris Ahlstrom
# \date        2025-01-30
# \updates     2025-01-30
# \license     $XPC_SUITE_GPL_LICENSE$
#
#  This file is part of the "lib66" library. See the top-level meson.build
#  file for license information.
#
#  Here we locate the headers. The root of the header directory is 'include'.
#
#-----------------------------------------------------------------------------

liblib66_headers += files(
   'c_macros.h',
   'cpp_types.hpp',
   'platform_macros.h',
   'lib_build_macros.h',
   'lib66.hpp'
   )

configure_file(
   input : 'lib66-config.h.in',
   output : 'lib66-config.h',
   configuration : cdata
   )

#****************************************************************************
# meson.build (lib66/include)
#----------------------------------------------------------------------------
# vim: ts=3 sw=3 ft=meson
#----------------------------------------------------------------------------
