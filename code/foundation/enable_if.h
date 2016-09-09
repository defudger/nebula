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
#ifndef NIC_4605DABF9700B6CB_NIC
#define NIC_4605DABF9700B6CB_NIC

#include "meta.h"

namespace nebula { namespace foundation {
//------------------------------------------------------------------------------
namespace enable_if_detail {
//------------------------------------------------------------------------------
struct empty {};
//------------------------------------------------------------------------------
} // enable_if_detail
//------------------------------------------------------------------------------
template <class Cond, class T = void>
using enable_if = 
meta::_if<
    Cond, 
    meta::id_<T>,
    enable_if_detail::empty>;

template <class Cond, class T = void>
using enable_if_ = enable_if<Cond, T>;
template <class Cond, class T = void>
using _enable_if = typename enable_if<Cond, T>::type;
//------------------------------------------------------------------------------
template <class Cond, class T = void>
using disable_if = 
meta::_if<
    meta::_not<Cond>, 
    meta::id_<T>,
    enable_if_detail::empty>;
    
template <class Cond, class T = void>
using disable_if_ = disable_if<Cond, T>;
template <class Cond, class T = void>
using _disable_if = typename disable_if<Cond, T>::type;
//------------------------------------------------------------------------------
template <bool Cond, class T = void>
using enable_if_c = enable_if<meta::bool_<Cond>, T>;
template <bool Cond, class T = void>
using _enable_if_c = typename enable_if<meta::bool_<Cond>, T>::type;
//------------------------------------------------------------------------------
template <bool Cond, class T = void>
using disable_if_c = disable_if<meta::bool_<Cond>, T>;
template <bool Cond, class T = void>
using _disable_if_c = typename disable_if<meta::bool_<Cond>, T>::type;

}} // namespaces

#endif // NIC_4605DABF9700B6CB_NIC
