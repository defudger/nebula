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
#ifndef NIC_33FF3C8CEBBEC5E3_NIC
#define NIC_33FF3C8CEBBEC5E3_NIC

#include "endian/convert.h"

namespace nebula { namespace foundation {
//------------------------------------------------------------------------------
/** @ingroup Foundation
 * Try to avoid this library, chances are you don't actually require endian
 * conversion at all. Rather stick with intrinsically portable solutions like
 * ascii/utf-8 based streams and so on.
 *
 * This library is by design kept simple. No exotic endian conversions will
 * be implemented besides the basic ones, little and big endian, and only for
 * data types int8_t, int16_t, int32_t and int64_t.
 * So no conversions for floating point data types will be provided. 
 * */
namespace endian {
}}} // namespaces

#endif // NIC_33FF3C8CEBBEC5E3_NIC