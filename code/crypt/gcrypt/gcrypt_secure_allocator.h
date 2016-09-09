/*--!>
This file is part of Nebula, a multi-purpose library mainly written in C++.

Copyright 2016 outshined (outshined@riseup.net)
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
#ifndef NIC_B0D2FBFFF08B5CEB_NIC
#define NIC_B0D2FBFFF08B5CEB_NIC

#include "gcrypt_error.h"

namespace nebula { namespace crypt { namespace detail { namespace gcrypt {
/** @ingroup Crypt
 * @{
 * */
//------------------------------------------------------------------------------
/**
 * */
template <class T>
struct secure_allocator
{
    using value_type = T;
    using is_always_equal = fnd::true_type;
    
    template <class X>
    struct rebind {
        using type = secure_allocator<X>;
    };
    
    secure_allocator() = default;
    secure_allocator(secure_allocator &) = default;
    secure_allocator(const secure_allocator &) = default;
    secure_allocator(secure_allocator &&) = default;
    template <class X>
    constexpr secure_allocator(secure_allocator<X>) {}
    
    secure_allocator &operator = (secure_allocator &) = default;
    secure_allocator &operator = (const secure_allocator &) = default;
    secure_allocator &operator = (secure_allocator &&) = default;
    
    inline T* allocate(const size_t n, const T * = nullptr) {
        n_assert(n > 0);
        
        T *ptr = static_cast<T *>(gcry_malloc_secure(n * sizeof(T)));
        if(n_expect(!ptr, false))
            throw fnd::bad_alloc();
        return ptr;
    }
    inline T* reallocate(T *ptr, const size_t old_size, const size_t new_size)
    {
        return allocate(new_size);
    }
    inline void deallocate(const T *ptr, const size_t n) noexcept {
        n_assert(ptr);
        n_assert(n > 0);
        
        gcry_free(const_cast<T *>(ptr)); // this wipes the memory
    }
    
    template <class X>
    inline bool operator == (const secure_allocator<X> &) const noexcept {
        return true;
    }
    template <class X>
    inline bool operator != (const secure_allocator<X> &) const noexcept {
        return false;
    }
};

/** @} */

}}}} // namespaces

#endif // NIC_B0D2FBFFF08B5CEB_NIC

