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
#ifndef NIC_D633921D5EB37CAE_NIC
#define NIC_D633921D5EB37CAE_NIC

#include "../../../../array.h"
#include "../../../../assert.h"

namespace nebula { namespace foundation { namespace io { namespace adaptor {
namespace base64_detail {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
inline char decode_digit(const char x) noexcept
{
    switch(x)
    {
    case 'A': return 0;
    case 'B': return 1;
    case 'C': return 2;
    case 'D': return 3;
    case 'E': return 4;
    case 'F': return 5;
    case 'G': return 6;
    case 'H': return 7;
    case 'I': return 8;
    case 'J': return 9;
    case 'K': return 10;
    case 'L': return 11;
    case 'M': return 12;
    case 'N': return 13;
    case 'O': return 14;
    case 'P': return 15;
    case 'Q': return 16;
    case 'R': return 17;
    case 'S': return 18;
    case 'T': return 19;
    case 'U': return 20;
    case 'V': return 21;
    case 'W': return 22;
    case 'X': return 23;
    case 'Y': return 24;
    case 'Z': return 25;
    case 'a': return 26;
    case 'b': return 27;
    case 'c': return 28;
    case 'd': return 29;
    case 'e': return 30;
    case 'f': return 31;
    case 'g': return 32;
    case 'h': return 33;
    case 'i': return 34;
    case 'j': return 35;
    case 'k': return 36;
    case 'l': return 37;
    case 'm': return 38;
    case 'n': return 39;
    case 'o': return 40;
    case 'p': return 41;
    case 'q': return 42;
    case 'r': return 43;
    case 's': return 44;
    case 't': return 45;
    case 'u': return 46;
    case 'v': return 47;
    case 'w': return 48;
    case 'x': return 49;
    case 'y': return 50;
    case 'z': return 51;
    case '0': return 52;
    case '1': return 53;
    case '2': return 54;
    case '3': return 55;
    case '4': return 56;
    case '5': return 57;
    case '6': return 58;
    case '7': return 59;
    case '8': return 60;
    case '9': return 61;
    case '-':
    case '+': return 62;
    case '_':
    case '/': return 63;
    default:
        return -1;
    }
}
//------------------------------------------------------------------------------
struct base64_digit_codec
{
    inline static char encode(unsigned x) noexcept {
        static constexpr const char *digits =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789"
            "+/";
        n_assert(x < 64);
        return digits[x];
    }
};
//------------------------------------------------------------------------------
struct base64url_digit_codec
{
    inline static char encode(unsigned x) noexcept {
        static constexpr const char *digits =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789"
            "-_";
        n_assert(x < 64);
        return digits[x];
    }
};
//------------------------------------------------------------------------------
template <class Codec>
inline array<char, 4> encode(
    const unsigned char a,
    const unsigned char b,
    const unsigned char c) noexcept
{
    array<char, 4> r;
                
    r[0] = Codec::encode(a >> 2);
    r[1] = Codec::encode(((a & 0b11) << 4) | (b >> 4));
    r[2] = Codec::encode(((b & 0b1111) << 2) | (c >> 6));
    r[3] = Codec::encode(c & 0b111111);
    
    return r;
}
//------------------------------------------------------------------------------
template <class Codec>
inline array<char, 3> encode(
    const unsigned char a,
    const unsigned char b) noexcept
{
    array<char, 3> r;
                
    r[0] = Codec::encode(a >> 2);
    r[1] = Codec::encode(((a & 0b11) << 4) | (b >> 4));
    r[2] = Codec::encode((b & 0b1111) << 2);
    
    return r;
}
//------------------------------------------------------------------------------
template <class Codec>
inline array<char, 2> encode(const unsigned char a) noexcept
{
    array<char, 2> r;
                
    r[0] = Codec::encode(a >> 2);
    r[1] = Codec::encode((a & 0b11) << 4);
    
    return r;
}

//------------------------------------------------------------------------------
inline array<char, 3> decode(
    const char a,
    const char b,
    const char c,
    const char d) noexcept
{
    array<char, 3> r;
    
    r[0] = (a << 2) | (b >> 4);
    r[1] = (b << 4) | (c >> 2);
    r[2] = (c << 6) | d;
        
    return r;
}
//------------------------------------------------------------------------------
inline array<char, 2> decode(
    const char a,
    const char b,
    const char c) noexcept
{
    array<char, 2> r;
    
    r[0] = (a << 2) | (b >> 4);
    r[1] = (b << 4) | (c >> 2);
        
    return r;
}
//------------------------------------------------------------------------------
inline char decode(const char a, const char b) noexcept
{
    return a << 2 | (b >> 4);
}

/** @} */

}}}}} // namespaces

#endif // NIC_D633921D5EB37CAE_NIC
