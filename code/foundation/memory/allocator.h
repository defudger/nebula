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
#ifndef NIC_313C1671BC53B212_NIC
#define NIC_313C1671BC53B212_NIC

#include "../exception/exception.h"
#include "../type_traits.h"
#include "../enable_if.h"
#include "../assert.h"

namespace nebula { namespace foundation { namespace memory {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
/** The default general purpose allocator template. This allocator might hold a
 * state.
 * */
template <class T>
struct allocator
{
    using value_type = T;
    using is_always_equal = true_type;
    
    template <class X>
    struct rebind {
        using type = allocator<X>;
    };
    
    allocator() = default;
    allocator(allocator &) = default;
    allocator(const allocator &) = default;
    allocator(allocator &&) = default;
    template <class X>
    constexpr allocator(allocator<X>) {}
    
    allocator &operator = (const allocator &) = default;
    allocator &operator = (allocator &&) = default;
    
    inline T* allocate(const size_t n, const void * = nullptr) {
        n_assert(n > 0);
        
        T *ptr = static_cast<T*>(
            ::operator new [] (n * sizeof(T), std::nothrow_t()));
        if(n_expect(!ptr, false))
            throw bad_alloc();
        return ptr;
    }
    inline T* reallocate(T *ptr, const size_t old_size, const size_t new_size) {
        n_assert(new_size > 0);
        n_assert(old_size > 0);
        n_assert(ptr);
        
        return allocate(new_size);
    }
    inline void deallocate(T *ptr, const size_t n) noexcept {
        n_assert(ptr);
        n_assert(n > 0);
        
        ::operator delete [] (
            static_cast<void *>(ptr),
            std::nothrow_t());
    }
    
    template <class X>
    inline bool operator == (const allocator<X> &) const noexcept {
        return true;
    }
    template <class X>
    inline bool operator != (const allocator<X> &) const noexcept {
        return false;
    }
};

/** @} */

}}} // namespaces

#endif // NIC_313C1671BC53B212_NIC
