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
#ifndef NIC_C7951116D3E2F8F3_NIC
#define NIC_C7951116D3E2F8F3_NIC

#include "exception.h"
#include "swap.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
/** Thrown by optional<...>::get(). */
struct bad_optional_access : public virtual runtime_error {};

//------------------------------------------------------------------------------
template <class T>
class optional
{
public:
    using value_type = T;
    
    inline optional() noexcept
    : good(false)
    {}
    template <class X = T,
        _enable_if<is_copy_constructible<X>>* = nullptr>
    inline optional(const optional &other)
    : good(other.good)
    {
        if(good)
            new (buf) T(other.get_());
    }
    template <class X = T,
        _enable_if<is_move_constructible<X>>* = nullptr>
    inline optional(optional &&other)
    noexcept(is_nothrow_move_constructible<T>::type::value)
    : good(other.good)
    {
        if(good) {
            new (buf) T(foundation::move(other.get_()));
            other.good = false;
        }
    }
    template <class X>
    inline optional(X &&x)
    : good(true)
    {
        new (buf) T(foundation::forward<X>(x));
    }
    inline optional(nil_tag)
    : good(false)
    {}
    inline ~optional() noexcept
    {
        reset();
    }
    
    template <class X = T,
        _enable_if<is_copy_assignable<X>>* = nullptr>
    inline optional &operator = (const optional &other)
    {
        if(good && other.good)
            get_() = other.get_();
        else if(!good && other.good)
        {
            new (buf) T(other.get_());
            good = true;
        }
        else if(good && !other.good)
        {
            get_().~T();
            good = false;
        }
        return *this;
    }
    template <class X = T,
        _enable_if<is_move_assignable<X>>* = nullptr>
    inline optional &operator = (optional &&other)
    noexcept(is_nothrow_move_assignable<T>::type::value)
    {
        if(good && other.good)
        {
            get_() = foundation::move(other.get_());
            other.good = false;
        }
        else if(!good && other.good)
        {
            new (buf) T(foundation::move(other.get_()));
            good = true;
            other.good = false;
        }
        else if(good && !other.good)
        {
            get_().~T();
            good = false;
        }
        return *this;
    }
    template <class X>
    inline optional &operator = (X &&x)
    {
        if(good)
            get_() = foundation::forward<X>(x);
        else
        {
            new (buf) T(foundation::forward<X>(x));
            good = true;
        }
        return *this;
    }
    inline optional &operator = (nil_tag) noexcept {
        reset();
        return *this;
    }
    
    inline void swap(optional &other)
    noexcept(
        noexcept(foundation::swap(declval<T&>(), declval<T&>()))
        && is_nothrow_move_assignable<T>::type::value)
    {
        if(good && other.good)
            foundation::swap(get_(), other.get_());
        else if(!good && other.good)
        {
            new (buf) T(foundation::move(other.get_()));
            other.get_().~T();
            good = true;
            other.good = false;
        }
        else if(good && !other.good)
            other.swap(*this);
    }
    
    inline operator bool () const noexcept {
        return good;
    }
    inline bool valid() const noexcept {
        return good;
    }
    
    inline T &get() & {
        if(!good)
            n_throw(bad_optional_access);
        return get_();
    }
    inline const T &get() const & {
        if(!good)
            n_throw(bad_optional_access);
        return get_();
    }
    inline T get() && {
        if(!good)
            n_throw(bad_optional_access);
        return foundation::move(get_());
    }
    
    inline void reset() noexcept {
        if(good)
        {
            get_().~T();
        }
        good = false;
    }
    
private:
    inline T &get_() noexcept {
        return *reinterpret_cast<T *>(buf);
    }
    inline const T &get_() const noexcept {
        return *reinterpret_cast<T *>(buf);
    }
    bool good;
    char buf[sizeof(T)] alignas(alignof(T));
};

/** @} */

}} // namespaces

#endif // NIC_C7951116D3E2F8F3_NIC
