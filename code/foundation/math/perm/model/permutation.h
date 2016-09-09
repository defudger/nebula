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
#ifndef NIC_B349254B02515D1D_NIC
#define NIC_B349254B02515D1D_NIC

#include "../traits.h"

#include "../../../array.h"

namespace nebula { namespace foundation { namespace math { namespace perm {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <size_t N>
class permutation
{
    n_static_assert(N > 0, "");
    
public:
    permutation() = default;
    permutation(permutation &) = default;
    permutation(const permutation &) = default;
    permutation(permutation &&) = default;
    
    template <class ... X>
    inline permutation(X && ... x)
    : v{foundation::forward<X>(x)...}
    {}
    
    permutation &operator = (const permutation&) = default;
    permutation &operator = (permutation &&) = default;
    
    inline void swap(permutation &other) noexcept {
        v.swap(other);
    }
    
    inline size_t &operator [] (const size_t n) noexcept {
        return v[n];
    }
    inline const size_t &operator [] (const size_t n) const noexcept {
        return v[n];
    }
    
    inline bool operator == (const permutation &other) const noexcept {
        return v == other;
    }
    inline bool operator != (const permutation &other) const noexcept {
        return v != other;
    }
    
    template <class Other>
    inline permutation operator * (const Other &other)
    {
        permutation r;
        for(size_t i = 0; i < N; ++i)
            r[i] = v[other[i]];
        return r;
    }
    
    inline friend bool operator == (
        const permutation &lhs,
        const permutation &rhs)
    {
        return lhs.v == rhs.v;
    }
    inline friend bool operator != (
        const permutation &lhs,
        const permutation &rhs)
    {
        return lhs.v != rhs.v;
    }
    
private:
    array<size_t, N> v;
};

//------------------------------------------------------------------------------
template <size_t N>
struct size<permutation<N>> : public meta::size_t_<N> {};

/** @} */

}}}} // namespaces

#endif // NIC_B349254B02515D1D_NIC

