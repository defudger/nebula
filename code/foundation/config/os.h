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
#ifndef NIC_1DD6CD3DF78CDCA6_NIC
#define NIC_1DD6CD3DF78CDCA6_NIC

#include "common.h"

/** @ingroup Foundation
 * @}
 */

//------------------------------------------------------------------------------
#if defined(linux) || defined(__linux) || defined(__linux__)
#    define N_OS_LINUX
#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#    define N_OS_WINDOWS
#else
#    error Unknown Operating System.
#endif

#ifdef NAUTO_HAVE_DEV_RANDOM
#   define N_OS_DEV_RANDOM
#endif

#ifdef NAUTO_HAVE_DEV_URANDOM
#   define N_OS_DEV_URANDOM
#endif

/** @} */

#endif // NIC_1DD6CD3DF78CDCA6_NIC