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
#ifndef NIC_4C6832BC92DBB11D_NIC
#define NIC_4C6832BC92DBB11D_NIC

#include "move.h"
#include "type_traits.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
namespace swap_detail {
//------------------------------------------------------------------------------
template <class T>
inline constexpr bool has_swap_(
    decltype(std::declval<T>().swap(std::declval<T>())) *) noexcept
{
    return true;
}
//------------------------------------------------------------------------------
template <class ...>
inline constexpr bool has_swap_(...) noexcept { return false; }
//------------------------------------------------------------------------------
template <class T, bool HasMember = has_swap_<T>(nullptr)>
struct swap_ 
{
    inline static void apply(T &x, T &y)
    noexcept(noexcept(is_nothrow_move_assignable<T>::value
        && is_nothrow_move_constructible<T>::value))
    {
        T tmp = foundation::move(x);
        x = foundation::move(y);
        y = foundation::move(tmp);
    }
};
template <class T>
struct swap_<T, true> 
{
    inline static void apply(T &x, T &y)
    noexcept(noexcept(x.swap(y)))
    {
        x.swap(y);
    }
};
} // swap_detail
//------------------------------------------------------------------------------
template <class T>
struct swap_impl 
{
    inline static void apply(T &x, T &y)
    noexcept(noexcept(is_nothrow_move_assignable<T>::value
        && is_nothrow_move_constructible<T>::value))
    {
        swap_detail::swap_<T>::apply(x, y);
    }
};
//------------------------------------------------------------------------------
template <class T>
inline void swap(T &x, T &y)
noexcept(noexcept(swap_impl<T>::apply(x, y)))
{
    swap_impl<T>::apply(x, y);
}

/** @} */

}} // namespaces

#endif // NIC_4C6832BC92DBB11D_NIC