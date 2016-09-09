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
#ifndef NIC_FCA830128DAD47E9_NIC
#define NIC_FCA830128DAD47E9_NIC

#include "../algo_fwd.h"
#include "../seq_fwd.h"
#include "../iter_fwd.h"

namespace nebula { namespace foundation { namespace meta {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
namespace for_each_detail {
//------------------------------------------------------------------------------
template <
    class First,
    class Last, 
    template <class ...> class F,
    class State>
struct f_each_
{
    using type =
        typename f_each_<
            _next<First>,
            Last,
            F,
            typename F<State, _deref<First>>::type>::type;
};

template <
    class Last, 
    template <class ...> class F,
    class State>
struct f_each_<Last, Last, F, State>
{
    using type = State;
};
//------------------------------------------------------------------------------
} // for_each_detail
//------------------------------------------------------------------------------
template <
    class Range, 
    template <class ...> class F,
    class State>
struct for_each_
{
    using type =
        typename for_each_detail::f_each_<
            _begin<Range>,
            _end<Range>,
            F,
            State>::type;
};

/** @} */

}}} // namespaces

#endif // NIC_FCA830128DAD47E9_NIC