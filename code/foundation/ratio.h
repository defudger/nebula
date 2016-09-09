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
#ifndef NIC_430E19B25FE85A09_NIC
#define NIC_430E19B25FE85A09_NIC

#include "meta/ratio.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
using meta::ratio;

template <class ... T>
using ratio_add = meta::ratio_add_<T...>;
template <class ... T>
using ratio_sub = meta::ratio_sub_<T...>;
template <class ... T>
using ratio_div = meta::ratio_div_<T...>;
template <class ... T>
using ratio_mul = meta::ratio_mul_<T...>;

template <class ... T>
using ratio_gcd = meta::ratio_gcd_<T...>;

//------------------------------------------------------------------------------
n_meta_alias(ratio_add);
n_meta_alias(ratio_sub);
n_meta_alias(ratio_div);
n_meta_alias(ratio_mul);
n_meta_alias(ratio_gcd);

//------------------------------------------------------------------------------
using meta::atto;
using meta::femto;
using meta::pico;
using meta::nano;
using meta::micro;
using meta::milli;
using meta::centi;
using meta::deci;

using meta::deca;
using meta::hecto;
using meta::kilo;
using meta::mega;
using meta::giga;
using meta::tera;
using meta::peta;
using meta::exa;

/** @} */

}} // namespaces

#endif // NIC_430E19B25FE85A09_NIC
