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
#ifndef NIC_BED6A05A8ACB792B_NIC
#define NIC_BED6A05A8ACB792B_NIC

#include "../common.h"

namespace nebula { namespace foundation { namespace range {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class R>
struct prev_permutation_impl
{
    template <class F_>
    inline static bool apply(R &r, F_ &&f)
    {
        return ins_::prev_permutation(range::begin(r), range::end(r), f);
    }
};
//------------------------------------------------------------------------------
/**
 * */
template <class R, class F = less<>>
inline bool prev_permutation(R &&r, F &&f = F())
{
    return prev_permutation_impl<
        typename ctraits::value<R>::type
    >::apply(r, f);
}

/** @} */

}}} // namespaces

#endif // NIC_BED6A05A8ACB792B_NIC
