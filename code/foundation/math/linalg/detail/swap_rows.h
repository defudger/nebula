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
#ifndef NIC_FC4AA265950B2734_NIC
#define NIC_FC4AA265950B2734_NIC

#include "../../vector.h"

namespace nebula { namespace foundation { namespace math { namespace linalg {
namespace linalg_detail {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class Matrix>
inline void swap_rows(Matrix &m, const size_t i, const size_t j)
{
    for(size_t k = 0; k < vec::size_at<Matrix,1>::type::value; ++k)
        foundation::swap(m(i,k), m(j,k));
}

/** @} */

}}}}} // namespaces

#endif // NIC_FC4AA265950B2734_NIC

