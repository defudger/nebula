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
#ifndef NIC_3406A3695D5443B0_NIC
#define NIC_3406A3695D5443B0_NIC

#include "../config.h"

#ifdef N_CHRONO_INLINE
#   define n_chrono_inline inline
#else
#   define n_chrono_inline
#endif

#ifdef N_HEADER_UNISTD_H
#   include <unistd.h>

#   ifdef _POSIX_TIMERS
#       define N_CHRONO_sc_clock_gettime
#       define N_CHRONO_hrc_clock_gettime
#   else
#       error "No _POSIX_TIMERS"
#   endif

#   ifdef _POSIX_MONOTONIC_CLOCK
#       define N_CHRONO_mc_clock_gettime
#   else
#       error "No _POSIX_MONOTONIC_CLOCK"
#   endif
#else
#   error "Help!"
#endif

#endif // NIC_3406A3695D5443B0_NIC