#if ! defined LIB66_EXCEPTIONS_HPP
#define LIB66_EXCEPTIONS_HPP

/*
 *  This file is part of lib66.
 *
 *  lib66 is free software; you can redistribute it and/or modify it under
 *  the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 2 of the License, or (at your option)
 *  any later version.
 *
 *  lib66 is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 *  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 *  details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with lib66; if not, write to the Free Software Foundation, Inc., 59
 *  Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/**
 * \file          exceptions.hpp
 *
 *    This module provides informative exceptions that can be thrown.
 *
 * \library       Any application or library
 * \author        Chris Ahlstrom
 * \date          2026-03-03
 * \updates       2026-03-03
 * \license       GNU GPL v2 or above
 *
 *  This file defines these execptions:
 */

#include "cpp_types.hpp"                /* util::CSTR(), not_nullptr() etc. */

#if defined __cplusplus

#include <exception>                    /* std::exception class             */
#include <string>                       /* std::string class                */

/*
 *  Helps to hide our definitions.
 */

namespace lib66
{

/**
 *  Defines a generic exception, lib66::exception.
 */

class exception : public std::exception
{
private:

    std::string m_message { "lib66 exception" };

public:

    exception () = default;
    exception (const std::string & msg) : m_message { msg }
    {
        // no other code
    }

    exception (const exception &) = default;
    exception (exception &&) = default;
    ~exception () = default;

    virtual const char * what () const noexcept override
    {
        return CSTR(message());
    }

    const std::string & message () const
    {
        return m_message;
    }

protected:

    void message (const std::string & msg)
    {
        m_message = msg;
    }

};

/**
 * Defines a failed-construction exception.
 */

class failed_constructor final : public lib66::exception
{

public:

    failed_constructor () : lib66::exception ("failed constructor")
    {
        // no code
    }

    /**
     * The msg parameter would be a class's name.
     */

    failed_constructor (const std::string & msg) : lib66::exception { }
    {
        std::string old { message() };              /* "lib66 exception"    */
        old += ": failed constructor '";
        old += msg;
        old += "'";
        message(old);                               /* the new message :-D  */
    }

    failed_constructor (const failed_constructor &) = default;
    failed_constructor (failed_constructor &&) = default;
    ~failed_constructor () = default;

};              // class lib66::exception

}               // namespace lib66

#endif          // __cplusplus

#endif          // LIB66_EXCEPTIONS_HPP

/*
 * exceptions.hpp
 *
 * vim: sw=4 ts=4 wm=4 et ft=cpp
 */

