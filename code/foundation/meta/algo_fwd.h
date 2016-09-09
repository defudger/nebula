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
#ifndef NIC_D30E09D2CDC9DC9E_NIC
#define NIC_D30E09D2CDC9DC9E_NIC

#include "../defs.h"

namespace nebula { namespace foundation { namespace meta {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <
    class Range,
    template <class ...> class F,
    class State> 
struct for_each_;

template <
    class Range,
    template <class ...> class F,
    class State>
using _for_each = typename for_each_<Range, F, State>::type;

//------------------------------------------------------------------------------
template <
    class Range,
    template <class ...> class F> 
struct find_;

template <
    class Range,
    template <class ...> class F>
using _find = typename find_<Range, F>::type;

//------------------------------------------------------------------------------
template <class ... S> 
struct merge_;

template <class ... S>
using _merge = typename merge_<S...>::type;

//------------------------------------------------------------------------------
template <class Seq, template <class ...> class F>
struct transform_;

template <class Seq, template <class ...> class F>
using _transform = typename transform_<Seq, F>::type;

//------------------------------------------------------------------------------
template <class Seq, template <class ...> class F>
struct erase_if_;

template <class Seq, template <class ...> class F>
using _erase_if = typename erase_if_<Seq, F>::type;

/** @} */

}}} // namespaces

#endif // NIC_D30E09D2CDC9DC9E_NIC