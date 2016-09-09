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
#ifndef NIC_DB4D5C2D1A42103E_NIC
#define NIC_DB4D5C2D1A42103E_NIC

#include "traits.h"
#include "../call_traits.h"
#include "../move.h"
#include "../declval.h"

namespace nebula { namespace foundation { namespace memory {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
namespace memory_detail {
//------------------------------------------------------------------------------
template <class Alloc>
inline constexpr bool has_construct_(
    decltype(declval<Alloc>().construct(
        declval<_allocator_value<Alloc>*>(), nullptr)) *) noexcept
{
    return true;
}
//------------------------------------------------------------------------------
template <class>
inline constexpr bool has_construct_(...) noexcept
{
    return false;
}
//------------------------------------------------------------------------------
template <class Alloc, bool HasMember = has_construct_<Alloc>(nullptr)>
struct construct_impl_
{
    template <class ... Args>
    inline static void apply(Alloc &a, 
        typename allocator_value<Alloc>::type *ptr,
        Args && ... args)
    {
        a.construct(ptr, foundation::forward<Args>(args)...);
    }
};
//------------------------------------------------------------------------------
template <class Alloc>
struct construct_impl_<Alloc, false>
{
    using T = _allocator_value<Alloc>;
    
    template <class ... Args, class T_ = T,
        _disable_if_c<_is_pod<T_>::value 
            && (sizeof ... (Args) < 2)>* = nullptr>
    inline static void apply(Alloc &, T *ptr, Args && ... args)
    {
        n_assert(ptr);
        ::new (ptr) T(foundation::forward<Args>(args)...);
    }
    /** @internal
     *  Placement new is testing for nullptr,
     *  thus generating at least two extra instructions (test, je).
     *  This pretty much fucks algorithms (like copying) hard since
     *  the compiler can't do it's optimization magic.
     *  Therefore we provide a specialized construct() version for
     *  POD types, which simply bit-copies (POD = Trivial type).
     *  For small types this boils down to a simple mov instruction.
     * */
    template <class T_ = T,
        _enable_if<is_pod<T_>>* = nullptr>
    inline static void apply(Alloc &, T *ptr, const T x) noexcept
    {
        n_assert(ptr);
        *ptr = x;
    }
    template <class T_ = T,
        _enable_if<is_pod<T_>>* = nullptr>
    inline static void apply(Alloc &, T *ptr) noexcept
    {
        n_assert(ptr);
        // does nothing
    }
};

} // memory_detail

//------------------------------------------------------------------------------
template <class Alloc>
struct construct_impl : public memory_detail::construct_impl_<Alloc> {};
//------------------------------------------------------------------------------
/** In-place construction of an object.
 *
 *  This function calls alloc.construct() if available, otherwise it
 *  constructs the object using placement new.
 *  @param alloc The allocator used to for construction.
 *  @param ptr Pointer to the memory region to construct the object there.
 *  @param args Parameter list used for construction - typically the parameters
 *  just get forwarded to the actual constructor of the type being constructed.
 *  @note Strong exception guarantee.
 * */
template <class Alloc, class ... Args>
inline void construct(Alloc &&alloc, 
    typename allocator_value<typename ctraits::value<Alloc>::type>::type *ptr, 
    Args && ... args)
{
    construct_impl<
        typename ctraits::value<Alloc>::type
    >::apply(alloc, ptr,
        foundation::forward<Args>(args)...);
}

/** @} */

}}} // namespaces

#endif // NIC_DB4D5C2D1A42103E_NIC
