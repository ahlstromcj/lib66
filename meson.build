#*****************************************************************************
# meson.build (lib66)
#-----------------------------------------------------------------------------
##
# \file        meson.build
# \library     lib66
# \author      Chris Ahlstrom
# \date        2025-01-30
# \updates     2025-01-30
# \license     $XPC_SUITE_GPL_LICENSE$
#
#  This file is part of the "lib66" library. It was part of the libs66
#  collection of libraries, but is now separate and stands alone. It
#  provides only some common header files.
#
#  The "lib66" library is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by the
#  Free Software Foundation, either version 3 of the License, or (at your
#  option) any later version.
#
#  The "lib66" library is distributed in the hope that it will be useful, but
#  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
#  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
#  more details.
#
#  You should have received a copy of the GNU General Public License along with
#  the "lib66" library. If not, see <https://www.gnu.org/licenses/>.
#
#  This project is meant to provide common header files for all of the
#  "xxx66" libraries projects (except for "seq66" version 1).
#
#-----------------------------------------------------------------------------

project('lib66',
   [ 'c', 'cpp' ],
   version : '1.0',
   license : 'GPLv3',
   meson_version : '>=1.1.0',
   default_options : [
      'c_std=c11', 'cpp_std=c++14', 'warning_level=3',
      'default_library=both'
      ]
   )

#-----------------------------------------------------------------------------
# Information for this sub-project.
#-----------------------------------------------------------------------------
#
#  Tricky: the *.pc file must have a base name matching the name of the
#  subproject *.wrap file.
#
#-----------------------------------------------------------------------------

lib66_pkg_description = 'Common "66" header files.'
lib66_pkg_version = meson.project_version()
lib66_api_version = '1.0'
lib66_info_date = '2025-01-30'
lib66_info_build_type = get_option('buildtype')
lib66_info_build_root = meson.project_build_root()
lib66_info_lib_type = get_option('default_library')
lib66_info_project_root = meson.project_source_root()
lib66_debug = get_option('buildtype').contains('debug')
lib66_project_base = 'lib66-@0@'.format(lib66_api_version)
lib66_pkgconfig_name = 'liblib66'
lib66_subproj = meson.is_subproject()

if lib66_debug
   if not lib66_subproj
      add_project_arguments(
         [ '-DDEBUG' ],
         language : 'cpp'
         )
   endif
endif

#-----------------------------------------------------------------------------
# Easy access to directory options. Commented out the unnecessary ones.
# Many of these definitions are simply informative.
#-----------------------------------------------------------------------------

lib66_dir = 'lib66-@0@'.format(lib66_api_version)
lib66_prefix = get_option('prefix')
lib66_bindir = join_paths(lib66_prefix, get_option('bindir'))
lib66_includedir = join_paths(lib66_prefix, get_option('includedir'), lib66_dir)
lib66_libdir = join_paths(lib66_prefix, get_option('libdir'), lib66_dir)
lib66_datadir = join_paths(lib66_prefix, get_option('datadir'), lib66_dir)
lib66_docdir = join_paths(lib66_prefix, lib66_datadir, 'doc', lib66_dir)
libraries_top = meson.project_source_root()
liblib66_include_top = join_paths(libraries_top, 'include')

#-----------------------------------------------------------------------------
# The *.pc file goes into $libdir/lib66-0.x/pkgconfig instead of
# $libdir/pkgconfig as the meson documentation asserts.  Not sure why, but
# wiring the expected directory here works.
#-----------------------------------------------------------------------------

alt_pkgconfig_libdir = join_paths(
   lib66_prefix, get_option('libdir'), 'pkgconfig'
   )

#-----------------------------------------------------------------------------
# liblib66_headers provides the list of all headers in the project. These are
# currently all installable, public headers. They are set in
# include/meson.build.
#
# liblib66_sources provides the source-code files. There are none, except
# in the tests directory.
# src/meson.build.
#-----------------------------------------------------------------------------

liblib66_headers = []
liblib66_sources = []
build_args = []

#-----------------------------------------------------------------------------
# Each include file directory is added to the list passed to the compiler.
# We prefer to use the style '#include "lib/header.hpp".
#-----------------------------------------------------------------------------

liblib66_includes = include_directories('.', 'include')

#-----------------------------------------------------------------------------
# Used by the lib66_version() function.
#-----------------------------------------------------------------------------

build_args += [
   '-DLIB66_NAME=' + '"' + meson.project_name() + '"',
   '-DLIB66_VERSION=' + '"' + meson.project_version() + '"'
   ]

#-----------------------------------------------------------------------------
# Set up some "HAVE" macros.  By default the header file is generated in the
# "build" directory. If configure_file() is moved to include/meson.build,
# the the header goes into "build/include", which is what we want.
#-----------------------------------------------------------------------------

cc = meson.get_compiler('cpp')
cdata = configuration_data()
cdata.set('limits_h', cc.has_header('limits.h'))

#-----------------------------------------------------------------------------
# Sub-directories. 'tests' has to be descended into later.
#-----------------------------------------------------------------------------

subdir('include')
subdir('src')

#-----------------------------------------------------------------------------
# Dependencies on Linux
#-----------------------------------------------------------------------------
#
# None, yet.
#
#-----------------------------------------------------------------------------

empty_depends = [ ]

#-----------------------------------------------------------------------------
# We recommemd using a recent version of meson by installing it outside the
# Linux distro's repository.  For example, meson on Ubuntu is pretty damn
# old.
#
# The choice of library type is of some import for debugging:
#
#     library:          Defaults to a shared library. The User setting is
#                       'default_library'.  See project() above.
#     shared_library:   Cannot see source files until stepped into.
#     static_library:   Can see the source files when debugging.
#
# This one causes the linker to not see the library functions, wotta pain:
#
#     gnu_symbol_visibility: 'hidden'
#
# Restore it later. Also see the https://gcc.gnu.org/wiki/Visibility site.
#
#-----------------------------------------------------------------------------

lib66_library_build = library(
   lib66_project_base,
   liblib66_sources,
   install : not lib66_subproj,
   install_dir : lib66_libdir,
   cpp_args : build_args,
   dependencies : empty_depends,
   include_directories : [ liblib66_includes ]
   )

#-----------------------------------------------------------------------------
# Make this library usable as a Meson subproject.  This allows a subproject to
# easily specify how it should be used. This makes it interchangeable with the
# same dependency that is provided externally (i.e. installed) by the system.
#-----------------------------------------------------------------------------

liblib66_dep = declare_dependency(
   include_directories : [ liblib66_includes ],
   link_with : [ lib66_library_build ]
   )

#-----------------------------------------------------------------------------
# Make this library usable from the system's package manager.
#-----------------------------------------------------------------------------

install_headers(liblib66_headers, subdir : lib66_dir, preserve_path : true)

#-----------------------------------------------------------------------------
# Package config
#-----------------------------------------------------------------------------
#  On Arch Linux, the .pc file is installed to /usr/local/lib/pkgconfig.
#  On Ubuntu, the .pc file is installed to
#     /usr/local/lib/x86_64-linux-gnu/pkgconfig.
#-----------------------------------------------------------------------------

if not lib66_subproj

   pkg_mod = import('pkgconfig')
   pkg_mod.generate(
      lib66_library_build,
      filebase : lib66_pkgconfig_name,
      version : lib66_pkg_version,
      name : lib66_project_base,
      description : lib66_pkg_description,
      install_dir : alt_pkgconfig_libdir,
      subdirs : lib66_dir,
      libraries : lib66_library_build,
      url : 'https://github.com/ahlstromcj/lib66',
      )

# TODO: figure out where to put and install the logo

   install_data(
      files(
         'ChangeLog',
         'LICENSE.md',
         'README.md'
         ),
      install_dir : get_option('docdir')
      )

   if get_option('enable-tests')
      subdir('tests')
   endif

endif

#-----------------------------------------------------------------------------
# Info
#-----------------------------------------------------------------------------

summary(
   {
      'Date' : lib66_info_date,
      'Filebase' : lib66_project_base,
      'Version' : lib66_pkg_version,
      'Base' : lib66_project_base,
      'Description' : lib66_pkg_description,
#     'Source Root' : lib66_info_project_root,
      'Headers Root' : liblib66_include_top,
      'Sub Dir' : lib66_project_base,
      'Build Type' : lib66_info_build_type,
      'Build Root' : lib66_info_build_root,
      'Library Type' : lib66_info_lib_type,
      'Subproject' : lib66_subproj
   },
   section : 'Lib66 Project'
   )

summary(
   {
      'prefix' : lib66_prefix,
      'includedir' : lib66_includedir,
      'bindir' : lib66_bindir,
      'libdir' : lib66_libdir,
      'datadir' : lib66_datadir,
      'docdir' : lib66_docdir
   },
   section : 'Lib66 Install Directories'
   )

#****************************************************************************
# meson.build (lib66)
#----------------------------------------------------------------------------
# vim: ts=3 sw=3 ft=meson
#----------------------------------------------------------------------------
