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
#ifndef NIC_1A0C1CB274D37B74_NIC
#define NIC_1A0C1CB274D37B74_NIC

#include "../tags.h"
#include "../../io.h"
#include "../../utils/demangle_type_info_name.h"

namespace nebula { namespace foundation { namespace fmt {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class T>
struct type
{
    template <class S>
    inline void operator () (S &s, fmt::fout_tag) const
    {
        const string name = foundation::demangle_type_info_name(
            typeid(T).name());
        fmt::fwrite(s,
            is_const<T>::type::value ? "const " : "",
            name,
            is_lvalue_reference<T>::type::value ? " &"
                : (is_lvalue_reference<T>::type::value ? " &&" : ""));
    }
};

/** @} */

}}} // namespaces

#endif // NIC_1A0C1CB274D37B74_NIC
