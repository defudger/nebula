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
#ifndef NIC_C4593ADDBB8A6202_NIC
#define NIC_C4593ADDBB8A6202_NIC

#include "common.h"

/** @ingroup Foundation
 * @}
 */

//------------------------------------------------------------------------------
#if defined(_M_X64) || defined(__x86_64__) || defined(__x86_64)
#   define N_ARCHITECTURE_X86_64
#elif defined(_M_IX86) || defined(_X86_)
#   define N_ARCHITECTURE_X86_32
#else
#   error Unknown Architecture.
#endif

/** @} */

#endif // NIC_C4593ADDBB8A6202_NIC