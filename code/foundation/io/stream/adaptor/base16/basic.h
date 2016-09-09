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
#ifndef NIC_190E61538BDDDA17_NIC
#define NIC_190E61538BDDDA17_NIC

#include "../../../../array.h"
#include "../../../../assert.h"

namespace nebula { namespace foundation { namespace io { namespace adaptor {
namespace base16_detail {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
inline char decode_digit(const char x) noexcept
{
    switch(x)
    {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'a':
    case 'A': return 10;
    case 'b':
    case 'B': return 11;
    case 'c':
    case 'C': return 12;
    case 'd':
    case 'D': return 13;
    case 'e':
    case 'E': return 14;
    case 'f':
    case 'F': return 15;
    default:
        return -1;
    }
}
//------------------------------------------------------------------------------
struct base16_digit_codec
{
    inline static char encode(unsigned x) noexcept {
        static constexpr const char *digits = "0123456789ABCDEF";
        n_assert(x < 16);
        return digits[x];
    }
};
//------------------------------------------------------------------------------
template <class Codec>
inline array<char, 2> encode(const uchar x) noexcept
{
    array<char, 2> r;
                
    r[0] = Codec::encode(x >> 4); // high
    r[1] = Codec::encode(x & 0b1111); // low
    
    return r;
}
//------------------------------------------------------------------------------
inline char decode(const char h, const char l) noexcept
{
    return (h << 4) | l;
}

/** @} */

}}}}} // namespaces

#endif // NIC_190E61538BDDDA17_NIC
