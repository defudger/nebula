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
#ifndef NIC_9CFC33DAB78AD325_NIC
#define NIC_9CFC33DAB78AD325_NIC

#include "type_traits.h"
#include "assert.h"
#include "move.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 */
namespace adaptor_detail {
//------------------------------------------------------------------------------
template <class T>
struct is_adaptor_helper {
private:
    typedef char yes[1];
    typedef char no[2];
    template <class X>
    static yes &_test(typename X::adaptor_id_ *);
    template <class X>
    static no &_test(...);

public:
    constexpr static bool value = sizeof(_test<T>(0)) == sizeof(yes);
};
} // adaptor_detail
//------------------------------------------------------------------------------
template <class T>
struct is_adaptor : public integral_constant<
    bool,
    adaptor_detail::is_adaptor_helper<typename remove_const<T>::type>::value
>
{};
//------------------------------------------------------------------------------
/** */
template <class T, class CRTP = void, bool IsAdaptor = is_adaptor<T>::value>
class adaptor_base
{
public:    
    struct adaptor_id_ {};
    
    using adaptee_type = typename remove_const<T>::type;
    
    adaptor_base(adaptor_base &) = default;
    adaptor_base(const adaptor_base &) = default;
    adaptor_base(adaptor_base &&) = default;
    
    inline adaptor_base(T *x) noexcept
    : subj(x)
    {}
    inline adaptor_base(T &x) noexcept
    : subj(&x)
    {}
    
    adaptor_base &operator = (const adaptor_base &rhs) = default;
    adaptor_base &operator = (adaptor_base &&rhs) = default;
    
    inline T &adaptee() noexcept {
        n_assert(subj);
        return *subj;
    }
    inline const T &adaptee() const noexcept {
        n_assert(subj);
        return *subj;
    }
    
    inline T &subject() noexcept {
        n_assert(subj);
        return *subj;
    }
    inline const T &subject() const noexcept {
        n_assert(subj);
        return *subj;
    }
    template <class C = CRTP, _enable_if<is_same<C, void>>* = nullptr>
    inline void subject(T &x) noexcept {
        subj = &x;
    }
    template <class C = CRTP, _disable_if<is_same<C, void>>* = nullptr>
    inline void subject(T &x) noexcept {
        subj = &x;
        static_cast<CRTP *>(this)->on_adaptor_reset();
    }
    
    inline bool nothrow_dtor() noexcept {
        return uncaught_exception();
    }
    
private:
    T *subj;
};
//------------------------------------------------------------------------------
template <class T>
struct adaptor_base<identity<T>, void, false>
    : public adaptor_base<T, void, false>
{
    inline adaptor_base(identity<T>)
    : adaptor_base<T, void, false>(nullptr)
    {}
};
//------------------------------------------------------------------------------
/** */
template <class T, class CRTP>
class adaptor_base<T, CRTP, true>
{   
public:    
    struct adaptor_id_ {};
    
    using adaptee_type = typename remove_const<T>::type;
    
    adaptor_base(adaptor_base &) = default;
    adaptor_base(const adaptor_base &) = default;
    adaptor_base(adaptor_base &&) = default;
    
    inline adaptor_base(T &x)
    : subj(x)
    {}
    inline adaptor_base(typename remove_const<T>::type &&x)
    : subj(foundation::move(x))
    {}
    
    adaptor_base &operator = (const adaptor_base &rhs) = default;
    adaptor_base &operator = (adaptor_base &&rhs) = default;
    
    inline T &adaptee() noexcept {
        return subj;
    }
    inline const T &adaptee() const noexcept {
        return subj;
    }
    
    inline auto &subject() noexcept {
        return subj.subject();
    }
    inline const auto &subject() const noexcept {
        return subj.subject();
    }
    template <class X,
        class C = CRTP, _enable_if<is_same<C, void>>* = nullptr>
    inline void subject(X &x) noexcept {
        subj.subject(x);
    }
    template <class X,
        class C = CRTP, _disable_if<is_same<C, void>>* = nullptr>
    inline void subject(X &x) noexcept {
        subj.subject(x);
        static_cast<CRTP *>(this)->on_adaptor_reset();
    }
    
    inline bool nothrow_dtor() noexcept {
        return subj.nothrow_dtor();
    }
    
private:
    adaptee_type subj;
};

//------------------------------------------------------------------------------
template <class T, class A,
    _enable_if<is_adaptor<_remove_reference<A>>>* = nullptr>
inline A operator | (T &t, A &&a)
{
    a.subject(t);
    return foundation::forward<A>(a);
}

/** @} */

}} // namespaces

#endif // NIC_9CFC33DAB78AD325_NIC
