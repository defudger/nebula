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
#ifndef NIC_967A5C4506501E2D_NIC
#define NIC_967A5C4506501E2D_NIC

#include "../common.h"

namespace nebula { namespace foundation { namespace range {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class InputRange, class OutputIter>
struct copy_if_impl
{
    template <class F>
    inline static OutputIter apply(
        const InputRange &src,
        OutputIter trg,
        F &&f)
    {
        return ins_::copy(
            range::begin(src),
            range::end(src),
            trg,
            f);
    }
};
//------------------------------------------------------------------------------
/**
 * */
template <class InputRange, class OutputIter, class F>
inline OutputIter copy_if(const InputRange &src, OutputIter trg, F &&f)
{
    return copy_if_impl<InputRange, OutputIter>::apply(src, trg, f);
}

/** @} */

}}} // namespaces

#endif // NIC_967A5C4506501E2D_NIC
