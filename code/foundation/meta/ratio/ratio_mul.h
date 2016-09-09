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
#ifndef NIC_9907844E2C0F7FAA_NIC
#define NIC_9907844E2C0F7FAA_NIC

#include "ratio.h"

namespace nebula { namespace foundation { namespace meta {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class First, class ... T>
struct ratio_mul_
: public ratio<
    First::type::num * ratio_mul_<T...>::type::num,
    First::type::den * ratio_mul_<T...>::type::den>
{};

template <class T>
struct ratio_mul_<T>
: public ratio<
    T::type::num,
    T::type::den>
{};

template <class ... T>
using _ratio_mul = typename ratio_mul_<T...>::type;

/** @} */

}}} // namespaces

#endif // NIC_9907844E2C0F7FAA_NIC