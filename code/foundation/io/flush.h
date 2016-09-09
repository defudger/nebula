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
#ifndef NIC_6433119FB399C568_NIC
#define NIC_6433119FB399C568_NIC

#include "sync.h"

namespace nebula { namespace foundation { namespace io {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
template <class Stream>
struct flush_impl
{
    inline static void apply(Stream &s)
    {
        s.flush();
    }
};
//------------------------------------------------------------------------------
template <class Stream>
inline void flush(Stream &&s)
{
    typedef typename ctraits::value<Stream>::type stream_t;
    n_static_assert(n_arg(
        has_flush<stream_t>::value), 
        "");
    
    flush_impl<stream_t>::apply(s);
}

/** @} */

}}} // namespaces

#endif // NIC_6433119FB399C568_NIC