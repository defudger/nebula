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
#ifndef NIC_4A622F654605549B_NIC
#define NIC_4A622F654605549B_NIC

#include "config.h"

namespace nebula { namespace crypt { namespace detail {
/** @ingroup Crypt
 * @{
 * */
//------------------------------------------------------------------------------
struct runtime_error : public virtual foundation::runtime_error {};
struct logic_error : public virtual foundation::logic_error {};
struct crypt_error : public virtual runtime_error {};
struct out_of_range :
    public virtual runtime_error,
    public virtual fnd::out_of_range {};

/** @} */

}}} // namespaces

#endif // NIC_4A622F654605549B_NIC

