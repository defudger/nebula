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
#ifndef NIC_4E5E354659ECF4FC_NIC
#define NIC_4E5E354659ECF4FC_NIC

#include "initial.h"

namespace nebula { namespace foundation { namespace ctraits {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
/** 
 * */
template <
    class T,
    // Cond == true -> pass by const value, otherwise by const reference.
    bool Cond = 
        is_pod<typename initial<T>::type>::value 
        && sizeof(typename initial<T>::type) < 16 // reasonably small?
>
struct param 
{
    using type = 
        typename add_lvalue_reference<
            typename add_const<
                typename initial<T>::type
            >::type
        >::type;
};
template <class T>
struct param<T, true>
{
    using type =
        typename add_const<
            typename initial<T>::type
        >::type;
};

n_meta_alias(param);

/** @} */

}}} // namespaces

#endif // NIC_4E5E354659ECF4FC_NIC
