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
#ifndef NIC_2E2BA7F13B97D28C_NIC
#define NIC_2E2BA7F13B97D28C_NIC

#include "../type_traits.h"

namespace nebula { namespace foundation {

/** @ingroup Foundation
 * @{
 * */

namespace system {
//------------------------------------------------------------------------------
/** Compile-time check. */
template< class T >
struct is_error_code_enum : public false_type {};
//------------------------------------------------------------------------------
/** Compile-time check. */
template< class T >
struct is_error_condition_enum : public false_type {};

//------------------------------------------------------------------------------
n_meta_alias(is_error_code_enum);
n_meta_alias(is_error_condition_enum);

} // system
//------------------------------------------------------------------------------
/** Helper to register an error code enum.
 * @attention Must be called at global namespace.
 * */
#define n_register_error_code_enum(x, cat) \
    namespace nebula { namespace foundation { namespace system { \
    template <> \
    struct is_error_code_enum<x> : public true_type {}; \
    template <> \
    struct make_error_code_impl<x> { \
        inline static error_code apply(const x y) noexcept { \
            return error_code(static_cast<int>(y), cat); \
        }}; \
    }}} // namespaces
//------------------------------------------------------------------------------
/** Helper to register an error condition enum.
 * @attention Must be called at global namespace.
 * */
#define n_register_error_condition_enum(x, cat) \
    namespace nebula { namespace foundation { namespace system { \
    template <> \
    struct is_error_condition_enum<x> : public true_type {}; \
    template <> \
    struct make_error_condition_impl<x> { \
        inline static error_condition apply(const x y) noexcept { \
            return error_condition(static_cast<int>(y), cat); \
        }}; \
    }}} // namespaces

/** @} */

}} // namespaces

#endif // NIC_2E2BA7F13B97D28C_NIC
