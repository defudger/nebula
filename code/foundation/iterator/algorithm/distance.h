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
#ifndef NIC_3F7A2F1D9EC9299F_NIC
#define NIC_3F7A2F1D9EC9299F_NIC

#include "../traits.h"

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
namespace iterator_detail {
//------------------------------------------------------------------------------
template <class I, class Trav = typename iterator_traversal<I>::type>
struct distance_impl_ {};
//------------------------------------------------------------------------------
template <class I>
struct distance_impl_<I, forward_traversal_tag>
{
    inline static typename iterator_difference<I>::type 
    apply(I a, const I b) {
        typename iterator_difference<I>::type n 
            = typename iterator_difference<I>::type();
        while(a != b)
        {
            a++;
            n++;
        }
        return n;
    }
};
//------------------------------------------------------------------------------
template <class I>
struct distance_impl_<I, bidirectional_traversal_tag>
: public distance_impl_<I, forward_traversal_tag>
{};
//------------------------------------------------------------------------------
template <class I>
struct distance_impl_<I, random_access_traversal_tag>
{
    inline static typename iterator_difference<I>::type 
    apply(const I a, const I b) {
        return b - a;
    }
};
//------------------------------------------------------------------------------
} // iterator_detail
//------------------------------------------------------------------------------
template <class I>
struct distance_impl
: public iterator_detail::distance_impl_<I> 
{};
//------------------------------------------------------------------------------
template <class I>
inline typename iterator_difference<I>::type distance(I a, I b) {
    return distance_impl<I>::apply(a, b);
}

/** @} */

}}} // namespaces

#endif // NIC_3F7A2F1D9EC9299F_NIC