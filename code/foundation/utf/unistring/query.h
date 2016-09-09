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
#ifndef NIC_409000D6739D7EB1_NIC
#define NIC_409000D6739D7EB1_NIC

#include "utils.h"

namespace nebula { namespace foundation { namespace utf {
namespace unistring {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
bool query(const char32_t c, const property p)
{
    return ::uc_is_property(::ucs4_t(c), to_uc_property_t(p));
}

/** @} */

}}}} // namespaces

#endif // NIC_409000D6739D7EB1_NIC

