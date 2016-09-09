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
#ifndef NIC_395695F51313B94B_NIC
#define NIC_395695F51313B94B_NIC

#include "traits.h"
#include "exception.h"
#include "../call_traits.h"
#include "../enable_if.h"

namespace nebula { namespace foundation { namespace io {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class Stream>
struct write_impl
{
    inline static void apply(Stream &s, const char *x, 
        typename stream_size<Stream>::type n)
    {
        s.write(x, n);
    }
};
//------------------------------------------------------------------------------
template <class Stream>
inline void write(Stream &&s, const char *x, 
    typename stream_size<typename ctraits::value<Stream>::type>::type n)
{
    typedef typename ctraits::value<Stream>::type stream_t;
    n_static_assert(n_arg(
        has_write<stream_t>::value), 
        "");
    
    write_impl<stream_t>::apply(s, x, n);
}

/** @} */

}}} // namespaces

#endif // NIC_395695F51313B94B_NIC