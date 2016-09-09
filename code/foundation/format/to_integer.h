/*--!>
This file is part of Nebula, a multi-purpose library mainly written in C++.

Copyright 2015-2016 outshined (outshined@riseup.net)
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
#ifndef NIC_B2C7A2E17FE0831B_NIC
#define NIC_B2C7A2E17FE0831B_NIC

#include "digit_codec.h"
#include "../exception.h"
#include "../str.h"
#include "../string.h"
#include "../cstring.h"
#include "../optional.h"

namespace nebula { namespace foundation { namespace fmt {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class T>
struct to_integer_impl
{
    template <class D>
    inline static optional<T> apply(
        const_cstring str,
        const unsigned base)
    {
        const char *beg = str.begin();
        const char *end = str.end();
        
        const char *x = beg;
        
        const bool neg = (*x == '-');

        if(neg) {
            if(_is_unsigned<T>::value)
                return optional<T>();
            ++x;
            if(x == end)
                return optional<T>();
        }
        
        unsigned dig = D::decode(*x++, nothrow_tag());
        if(unsigned(-1) == dig || dig >= base)
            return optional<T>();
        if(0 == dig) {
            if(end-beg > 1) {
                return optional<T>();
            }
        }
        
        if(neg)
        {
            T res(-T(dig));
            for( ; x < end; ++x)
            {
                if(res < math::minimum<T>() / base)
                    return optional<T>();
                res *= T(base);
                dig = D::decode(*x, nothrow_tag());
                if(unsigned(-1) == dig || dig >= base)
                    return optional<T>();
                if(res < math::minimum<T>() + T(dig))
                    return optional<T>();
                res -= T(dig);
            }
            return res;
        }
        else
        {
            T res(dig);
            for( ; x < end; ++x)
            {
                if(res > math::maximum<T>() / base)
                    return optional<T>();
                res *= T(base);
                dig = D::decode(*x, nothrow_tag());
                if(unsigned(-1) == dig || dig >= base)
                    return optional<T>();
                if(res > math::maximum<T>() - T(dig))
                    return optional<T>();
                res += T(dig);
            }
            return res;
        }
    }
};

//------------------------------------------------------------------------------
template <class T, class D = fmt::digit_codec>
inline optional<T> to_integer(
    const basic_cstring<const char> str,
    const unsigned base,
    nothrow_tag)
{
    return to_integer_impl<T>::template apply<D>(str, base);
}
//------------------------------------------------------------------------------
template <class T, class D = fmt::digit_codec>
inline T to_integer(
    const basic_cstring<const char> str,
    const unsigned base = 10)
{
    auto r = fmt::to_integer<T, D>(str, base, nothrow_tag());
    if(!r.valid())
        n_throw(runtime_error);
    return r;
}

/** @} */

}}} // namespaces

#endif // NIC_B2C7A2E17FE0831B_NIC
