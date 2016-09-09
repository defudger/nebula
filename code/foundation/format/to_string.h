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
#ifndef NIC_225762E17FE08348_NIC
#define NIC_225762E17FE08348_NIC

#include "fwrite.h"
#include "../io/stream/msink.h"
#include "../string.h"

namespace nebula { namespace foundation { namespace fmt {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class ... X>
inline string to_string(const X & ... x)
{
    io::msink<string> ss;
    fmt::fwrite(ss, x...);
    return foundation::move(ss.container());
}

//------------------------------------------------------------------------------
inline string to_string(const string &s)
{
    return s;
}
inline string to_string(string &&s)
{
    return foundation::move(s);
}

/** @} */

}}} // namespaces

#endif // NIC_225762E17FE08348_NIC