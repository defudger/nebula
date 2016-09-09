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
#ifndef NIC_BE1BFDB044B2E839_NIC
#define NIC_BE1BFDB044B2E839_NIC

#include "config.h"

namespace nebula { namespace foundation { namespace async {
//------------------------------------------------------------------------------
template <class T, class M>
struct wait_impl
{
    inline static void apply(T &x, M &m)
    {
        x.wait(m);
    }
};
//------------------------------------------------------------------------------
/** Wait for a condition variable.
 *
 *  Can only fail if
 *  - Different mutexes were supplied for concurrent wait_for()
 *  or wait() operations on the same condition variable.
 *  - The mutex was not owned by the calling thread.
 * */
template <class T, class M>
inline void wait(T &x, M &m)
{
    wait_impl<T, M>::apply(x, m);
}

}}} // namespaces

#endif // NIC_BE1BFDB044B2E839_NIC
