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
#ifndef NIC_E697B4D83C20C2C3_NIC
#define NIC_E697B4D83C20C2C3_NIC

#include "stream.h"
#include "../../dll_interface.h"

namespace nebula { namespace foundation { namespace io {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
class nullsink : public stream_base
{
public:
    using stream_size = streamsize;
    using stream_offset = streamoff;
    using stream_position = streampos;
    using stream_category = tag<out_tag, flush_tag>;
    
    inline void write(const char *x, stream_size n) noexcept final {}
    inline void put(char) noexcept final {}
    inline void flush() noexcept final {}
};

/** @} */

}}} // namespaces

#endif // NIC_E697B4D83C20C2C3_NIC
