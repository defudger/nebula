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
#ifndef NIC_14DE65478B5040DD_NIC
#define NIC_14DE65478B5040DD_NIC

namespace nebula { namespace foundation { namespace iterator {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class I>
struct find_if_impl
{
    template <class F_>
    inline static I apply(I first, const I last, F_ &&f)
    {
        for( ; first != last; ++first)
        if(f(*first))
            return first;
        return last;
    }
};
//------------------------------------------------------------------------------
/** Find the first element in the range [first, last) that satisfies the unary
 * predicate f.
 * @param I Must be an incrementable iterator.
 * @param f A unary predicate to filter a certain element.
 * @note The supplied functor f is allowed to throw.
 * @note Strong exception guarantee.
 * */
template <class I, class F>
inline I find_if(I first, I last, F &&f)
{
    return find_if_impl<I>::apply(first, last, f);
}

/** @} */

}}} // namespaces

#endif // NIC_14DE65478B5040DD_NIC
