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
#ifndef NIC_F46086D6E6813B67_NIC
#define NIC_F46086D6E6813B67_NIC

#include "integer.h"

namespace nebula { namespace foundation { namespace fmt {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class T,
    typename enable_if<math::is_integer<T>>::type* = nullptr>
inline auto oct(const T &x)
{
    return fmt::integer(x, 8);
}
//------------------------------------------------------------------------------
template <class T,
    typename disable_if<math::is_integer<T>>::type* = nullptr>
inline auto oct(const T &x)
{
    return fmt::real(
        x,
        N_FORMAT_DEFAULT_PRECISION,
        N_FORMAT_DEFAULT_ROUNDING_STYLE,
        true,
        8);
}

/** @} */

}}} // namespaces

#endif // NIC_F46086D6E6813B67_NIC