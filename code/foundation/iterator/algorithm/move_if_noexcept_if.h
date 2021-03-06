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
#ifndef NIC_9EEAECDBBD62A5FE_NIC
#define NIC_9EEAECDBBD62A5FE_NIC

#include "../../move.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class I, class O>
struct move_if_noexcept_if_impl
{
    template <class F_>
    inline static O apply(I first, I last, O dest, F_ &&f) {
        while(first != last)
            if(f(*first))
                *dest++ = foundation::move_assign_if_noexcept(*first++);
        return dest;
    }
};
//------------------------------------------------------------------------------
template <class I, class O, class F>
inline O move_if_noexcept_if(I first, I last, O dest, F &&f)
{
    return move_if_noexcept_if_impl<I, O>::apply(first, last, dest, f);
}

/** @} */

}}} // namespaces

#endif // NIC_9EEAECDBBD62A5FE_NIC
