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
 * \file          exceptions_test.cpp
 *
 *      A test-file for the exceptions header file.
 *
 * \library       lib66
 * \author        Chris Ahlstrom
 * \date          2026-03-03
 * \updates       2026-05-30
 * \license       See above.
 *
 *      This small program tests the small lib66 exceptions classes.
 */

#include <cstdlib>                      /* EXIT_SUCCESS, EXIT_FAILURE       */
#include <iostream>                     /* std::cout, set::cerr             */

#include "lib66.hpp"                    /* lib66_version()                  */
#include "exceptions.hpp"               /* lib66::exception, etc.        n  */

class krufty
{

private:

    std::string m_message { };

    char * m_array { nullptr };

public:

    krufty () = default;
    krufty (const std::string & msg);
    krufty (bool throw_it_up);

    krufty (const krufty &) = delete;
    krufty & operator = (const krufty &) = default;

    krufty (krufty &&) = delete;
    krufty & operator = (krufty &&) = default;

    ~krufty ()
    {
        std::cout << "Calling ~kruft()" << std::endl;
        remove_array();
    }

    bool create_array ()
    {
        static std::string s_data { "ABCDEFG" };            /* 7 characters */
        std::size_t sz { s_data.size() };
        remove_array();
        m_array = new (std::nothrow) char [ sz  + 1 ];      /* 8 characters */

        bool result { not_nullptr(m_array) };
        if (result)
        {
            for (std::size_t i { 0 }; i < sz; ++i)
                m_array[i] = s_data[i];

            m_array[sz] = '\0';
        }
        return result;
    }

    void remove_array ()
    {
        if (not_nullptr(m_array))
        {
            delete [] m_array;
            m_array = nullptr;
        }
    }

    const char * array () const
    {
        return m_array;
    }

    void throw_up ()
    {
        throw lib66::failed_constructor("krufty");
    }

};

krufty::krufty (const std::string & msg) : m_message { msg }
{
    (void) create_array();
}

krufty::krufty (bool throw_it_up) : m_message { "Leakage check" }
{
    (void) create_array();
    if (throw_it_up)
        throw_up();
}

/*
 *  main() routine.
 */

int
main (int /*argc*/, char * /*argv*/ [])
{
    int rcode { EXIT_FAILURE };

    /*
     * We cannot pass this string literal to krufty(), because that
     * causes the krufty(bool) overload to be called.
     *
     * The reason the boolean converting-constructor is chosen over the
     * one for std::string is because the conversion from char const *
     * to bool is a standard conversion, while the one to std::string
     * is a user-defined conversion.
     *
     * Standard conversions have a greater rank than user-defined
     * conversions.
     */

    std::string name { "Test of try/catch" };
    krufty k(name);
    try
    {
        /*
         * Here, we throw the exception after the kruft object is
         * constructed. It is caught below, so the program does not
         * abort. Instead, ~kruft() is called at the end of
         * main, so there is no leakage for this test.
         */

        std::cout << "Now calling krufty::throw_up()" << std::endl;
        k.throw_up();
    }
    catch (lib66::failed_constructor & e)
    {
        rcode = EXIT_SUCCESS;
        std::cout
            << "Caught deliberate error \"" << e.message() << "\""
            << std::endl
            ;
    }
    if (rcode == EXIT_SUCCESS)
    {
        /*
         * This tests construction abort after the array is created.
         * ~kruft() does not get called here, so valgrind will detect
         * that eight bytes, allocated in the create_array() calls
         * inf the krufty(bool) constructor, line #110, are lost.
         *
         * 2026-05-30. Actually, no bytes are lost. Valgrind reports only
         *
         * Conditional jump or move depends on uninitialised value(s)
         * free() (in /home/me/.../lib66/build/cc/tests/exceptions_test)
         */

        rcode = EXIT_FAILURE;
        try
        {
            std::cout << "Now calling krufty(throwup = true)" << std::endl;
            krufty k(true);
        }
        catch (lib66::failed_constructor & e)
        {
            rcode = EXIT_SUCCESS;
            std::cout
                << "Caught error; check for no leaks with valgrind."
                << std::endl;
                ;
        }
    }
    if (rcode == EXIT_SUCCESS)
        std::cout << "lib66::failed_contructor test succeeded" << std::endl;
    else
        std::cerr << "lib66::failed_contructor test failed" << std::endl;

    return rcode;
}

/*
 * exceptions_test.cpp
 *
 * vim: sw=4 ts=4 wm=4 et ft=cpp
 */
