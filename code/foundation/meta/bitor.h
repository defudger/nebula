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
#ifndef NIC_F648E290C92BEDC9_NIC
#define NIC_F648E290C92BEDC9_NIC

#include "integral_constant.h"

namespace nebula { namespace foundation { namespace meta {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class First, class ... T>
struct bitor_ {
    using type = integral_constant<
        decltype(First::type::value | bitor_<T...>::type::value),
        First::type::value | bitor_<T...>::type::value
    >;
};

template <class T>
struct bitor_<T> {
    using type = integral_constant<
        typename T::type::value_type, T::type::value>;
};
//------------------------------------------------------------------------------
template <class ... T>
using _bitor = typename bitor_<T...>::type;

/** @} */

}}} // namespaces

#endif // NIC_F648E290C92BEDC9_NIC