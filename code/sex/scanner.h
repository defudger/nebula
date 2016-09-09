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
#ifndef INC_59CFB48924B2F365_INC
#define INC_59CFB48924B2F365_INC

#include "exception.h"
#include "error.h"

namespace nebula { namespace sex { namespace detail {
/** @ingroup Sex
 * @{
 * */
//------------------------------------------------------------------------------
enum class token_id
{
    lbracket,
    rbracket,
    quoted_string,
    string,
    data,
    eof,
    invalid
};
//------------------------------------------------------------------------------
inline const char *to_cstr(const token_id x) noexcept
{
    switch(x)
    {
    case token_id::lbracket: return "lbracket";
    case token_id::rbracket: return "rbracket";
    case token_id::string: return "string";
    case token_id::data: return "data";
    case token_id::quoted_string: return "quoted_string";
    case token_id::eof: return "eof";
    case token_id::invalid: return "invalid";
    default: return "unknown";
    }
}
//------------------------------------------------------------------------------
class token
{
public:
    inline token() noexcept
    : id_(token_id::invalid)
    {}
    token(token &) = default;
    token(const token &) = default;
    token(token &&) = default;
    
    inline token(const token_id id__, const fnd::const_cstring v_)
    :   id_(id__), v(v_)
    {}
    
    token &operator = (token &) = default;
    token &operator = (const token &) = default;
    token &operator = (token &&) = default;
    
    inline void swap(token &other) noexcept {
        fnd::swap(id_, other.id_);
        fnd::swap(v, other.v);
    }
    
    inline token_id id() const noexcept {
        return id_;
    }
    inline fnd::const_cstring value() const noexcept {
        return v;
    }
    
    inline operator bool () const noexcept {
        return token_id::invalid != id_
            && token_id::eof != id_;
    }
    
private:
    token_id id_;
    fnd::const_cstring v;
};

//------------------------------------------------------------------------------
extern fnd::tuple<token, fnd::const_cstring> n_sex_dll
scan(fnd::const_cstring s);

/** @} */

}}} // namespaces

#endif // INC_59CFB48924B2F365_INC

