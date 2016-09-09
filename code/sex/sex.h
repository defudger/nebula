/*--!>
This file is part of Nebula, a multi-purpose library mainly written in C++.

Copyright 2016 outshined (outshined@riseup.net)
    (PGP: 0x8A80C12396A4836F82A93FA79CA3D0F7E8FBCED6)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
--------------------------------------------------------------------------<!--*/
#ifndef INC_770DA098A43F26A8_INC
#define INC_770DA098A43F26A8_INC

#include "simple_tree.h"

namespace nebula {
/** @ingroup Sex
 * @{
 * */
/** Very simple s-expressions parser.
 * */
namespace sex {
//------------------------------------------------------------------------------
using detail::runtime_error;
using detail::logic_error;
using detail::parsing_error;

using detail::errc;
using detail::sex_error_category;

using detail::token;
using detail::token_id;
using detail::scan;
using detail::parse;
using detail::iterative_parser;
using detail::simple_tree;

//------------------------------------------------------------------------------
/** A listener for the parser that does nothing.
 *
 *  Every function is allowed to throw.
 *  Functions with a boolean return value can return false to stop parsing.
 * */
struct null_listener
{
    /** Beginning of a new list. */
    inline bool push(size_t pos) {
        return true;
    }
    /** Ending of a list. */
    inline bool pop(size_t pos) {
        return true;
    }
    /** A strings like in: (foo 123). */
    inline bool string(foundation::const_cstring, size_t pos) {
        return true;
    }
    /** Quoted strings like: ("foo" "123").
     *
     *  @note Escape sequences are not resolved. You have to do that on
     *  your own.
     * */
    inline bool quoted_string(foundation::const_cstring, size_t pos) {
        return true;
    }
    /** Data string like: (3:foo3:123) */
    inline bool data(foundation::const_cstring, size_t pos) {
        return true;
    }
    /** Error callback.
     *
     *  @param pos The offset (in bytes) where parsing failed.
     * */
    inline void error(errc e, size_t pos) {}
};

} // sex

/** @} */

} // nebula

#endif // INC_770DA098A43F26A8_INC

