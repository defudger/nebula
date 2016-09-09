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
#ifndef NIC_4FF640C112334B9C_NIC
#define NIC_4FF640C112334B9C_NIC

#include "ceil.h"
#include "floor.h"
#include "../classification/isnegative.h"

namespace nebula { namespace foundation { namespace math {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class T>
struct round0_impl
{
    template <class X>
    inline static T apply(X &&x)
    {
        return math::isnegative(x) 
            ? math::ceil(foundation::forward<X>(x))
            : math::floor(foundation::forward<X>(x));
    }
};

//------------------------------------------------------------------------------
template <class T>
inline ctraits::_value<T> round0(T &&x)
{
    n_static_assert(!is_integer<ctraits::_value<T>>::type::value,
        "Floating point type required.");
    return round0_impl<ctraits::_value<T>>::apply(foundation::forward<T>(x));
}

/** @} */

}}} // namespaces

#endif // NIC_4FF640C112334B9C_NIC
