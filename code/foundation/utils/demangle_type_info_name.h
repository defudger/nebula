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
#ifndef NIC_6B7D0B9597D2241C_NIC
#define NIC_6B7D0B9597D2241C_NIC

#include "../dll_interface.h"
#include "../string.h"

namespace nebula { namespace foundation {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
/** This function tries to demangle a name returned by std::type_info::name().
 * @param _in A string returned by std::type_info::name().
 * @return A possibly better readable version of _in.
 * @throw bad_alloc if memory allocation fails.
 * @throw logic_error if the input name is not valid.
 * @throw exception if the implementation fails for unknowen reasons.
 * @internal For more details take a look at
 * http://gcc.gnu.org/onlinedocs/libstdc++/manual/ext_demangling.html
 * */
extern string n_foundation_dll demangle_type_info_name(const char *_in);

/** @} */

}} // namespaces

#endif // NIC_6B7D0B9597D2241C_NIC