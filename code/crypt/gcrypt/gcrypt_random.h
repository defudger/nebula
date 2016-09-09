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
#ifndef NIC_92FF908AA375F114_NIC
#define NIC_92FF908AA375F114_NIC

#include "gcrypt_error.h"

namespace nebula { namespace crypt { namespace detail { namespace gcrypt {
/** @ingroup Crypt
 * @{
 * */
//------------------------------------------------------------------------------
class n_crypt_dll random_device : public io::stream_base
{
public:
    using stream_size = io::streamsize;
    using stream_offset = io::streamoff;
    using stream_position = io::streampos;
    using stream_category = fnd::tag<io::in_tag>;
    
    random_device(gcry_random_level x)
    : lvl(x)
    {
        switch(x)
        {
        case GCRY_STRONG_RANDOM:
        case GCRY_VERY_STRONG_RANDOM:
            break;
        default:
            n_throw(logic_error);
        }
    }
    
    inline void swap(random_device &other) noexcept {
        fnd::swap(lvl, other.lvl);
    }
    
    stream_size read(char *buf, const stream_size n);
    inline io::ceof get() {
        char res = 0;
        read(&res, 1);
        return res;
    }
    
private:
    gcry_random_level lvl;
};

/** @} */

}}}} // namespaces

#endif // NIC_92FF908AA375F114_NIC

