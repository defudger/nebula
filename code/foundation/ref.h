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
#ifndef NIC_4605DACF9700B6CB_NIC
#define NIC_4605DACF9700B6CB_NIC

#include "move.h"

namespace nebula { namespace foundation {
//------------------------------------------------------------------------------
template <class T>
class reference_wrapper
{
public:
    using type = T;

    reference_wrapper() = delete;
    reference_wrapper(reference_wrapper &) = default;
    reference_wrapper(const reference_wrapper &) = default;
    reference_wrapper(reference_wrapper &&) = default;
    
    reference_wrapper(T &ref) noexcept : ptr_(&ref) {}
    reference_wrapper(T &&) = delete;

    reference_wrapper& operator = (reference_wrapper& ) = default;
    reference_wrapper& operator = (const reference_wrapper& ) = default;
    reference_wrapper& operator = (reference_wrapper&& ) = default;
    
    inline operator T& () const noexcept { return *ptr_; }
    inline T& get() const noexcept { return *ptr_; }
    
    template <class ... X>
    inline auto operator () (X && ... x) const {
        return get()(foundation::forward<X>(x)...);
    }

private:
    T* ptr_;
};
//------------------------------------------------------------------------------
template <class T>
inline reference_wrapper<T> ref(T &x) noexcept {
    return x;
}
//------------------------------------------------------------------------------
template <class T>
inline reference_wrapper<T> ref(reference_wrapper<T> x) noexcept {
    return x;
}
//------------------------------------------------------------------------------
template <class T>
inline reference_wrapper<const T> cref(const T &x) noexcept {
    return x;
}
//------------------------------------------------------------------------------
template <class T>
inline reference_wrapper<const T> cref(reference_wrapper<const T> x) noexcept {
    return x;
}
//------------------------------------------------------------------------------
template <class T>
inline reference_wrapper<const T> cref(reference_wrapper<T> x) noexcept {
    return x.get();
}

}} // namespaces

#endif // NIC_4605DACF9700B6CB_NIC
