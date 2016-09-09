/*--!>
This file is part of Nebula, a multi-purpose library mainly written in C++.

Copyright 2016 outshined (outshined@riseup.net)
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
#include "../config.h"
#ifdef N_CRYPT_GCRYPT

#include "gcrypt_random.h"

namespace nebula { namespace crypt { namespace detail { namespace gcrypt {
//------------------------------------------------------------------------------
io::streamsize random_device::read(char *buf, const io::streamsize n)
{
    if(n != 0)
    {
        if(!buf)
            n_throw(logic_error);
        gcry_randomize(buf, n, lvl);
    }
    
    return n;
}

}}}} // namespaces

#endif // N_CRYPT_GCRYPT

