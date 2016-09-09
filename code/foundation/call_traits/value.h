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
#ifndef NIC_2D676E377ADB7CBF_NIC
#define NIC_2D676E377ADB7CBF_NIC

#include "initial.h"

namespace nebula { namespace foundation { namespace ctraits {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
/** 
 * */
template <
    class T
>
struct value 
{
private:
    using I = typename initial<T>::type;
    using S = 
    typename conditional<
        is_array<I>::type::value,
        typename add_pointer<typename remove_all_extents<I>::type>::type,
        I>::type;
    
public:
    using type =
    typename conditional<
        is_pointer<S>::type::value,
        typename remove_const<S>::type,
        typename remove_cv<S>::type
    >::type;
};

n_meta_alias(value);

/** @} */

}}} // namespaces

#endif // NIC_2D676E377ADB7CBF_NIC
