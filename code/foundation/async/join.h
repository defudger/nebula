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
#ifndef NIC_C346DDCF3D76B6D5_NIC
#define NIC_C346DDCF3D76B6D5_NIC

#include "config.h"

namespace nebula { namespace foundation { namespace async {
//------------------------------------------------------------------------------
template <class T>
struct join_impl
{
    inline static void apply(T &x)
    {
        x.join();
    }
};
//------------------------------------------------------------------------------
/** If a thread is not detached it can be joined with the calling thread.
 *  
 *  This may throw if the thread in question is already waiting to be joined,
 *  or if it has been detached, or if a deadlock was detected.
 *  Otherwise this call will not fail.
 * */
template <class T>
inline void join(T &x)
{
    join_impl<T>::apply(x);
}

}}} // namespaces

#endif // NIC_C346DDCF3D76B6D5_NIC
