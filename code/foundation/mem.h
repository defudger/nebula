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
#ifndef NIC_8D3875903819BA91_NIC
#define NIC_8D3875903819BA91_NIC

#include "config.h"
#include <cstring>

namespace nebula { namespace foundation {
//------------------------------------------------------------------------------
using std::memchr;
using std::memcmp;
using std::memcpy;
using std::memmove;
using std::memset;

//------------------------------------------------------------------------------
/** Tries to zero out a block of memory containing sensitive data.
 *
 *  @attention This is not a reliable solution to scrub sensitive data from
 *  memory, which only the OS could provide. Every non-ancient kernel should
 *  be doing this by default. But this function could still be handy from
 *  a defensive programming standpoint.
 *
 *  @see https://gcc.gnu.org/bugzilla/show_bug.cgi?id=8537
 * */
inline void scrub_s(void *buf, const size_t n) noexcept
{
    if(!buf)
        return;
    #ifdef __STDC_LIB_EXT1__
    memset_s(buf, n, 0, n);
    #else
    memset(buf, 0, n);
    volatile char *no_dead_code_rem = static_cast<volatile char *>(buf);
    #endif // __STDC_LIB_EXT1__
}

}} // namespaces

#endif // NIC_8D3875903819BA91_NIC
