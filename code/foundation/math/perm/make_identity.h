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
#ifndef NIC_58BE98F1BD5239A6_NIC
#define NIC_58BE98F1BD5239A6_NIC

#include "traits.h"

namespace nebula { namespace foundation { namespace math { namespace perm {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class P>
struct make_identity_impl
{
    inline static P apply()
    {
        P p;
        for(size_t i = 0; i < perm::_size<P>::value; ++i)
            p[i] = i;
        return p;
    }
};
//------------------------------------------------------------------------------
template <class P>
inline P make_identity()
{
    return make_identity_impl<P>::apply();
}

/** @} */

}}}} // namespaces

#endif // NIC_58BE98F1BD5239A6_NIC

