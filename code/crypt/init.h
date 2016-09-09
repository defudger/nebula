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
#ifndef NIC_0B0684B15EEDD924_NIC
#define NIC_0B0684B15EEDD924_NIC

#include "config.h"

#ifdef N_CRYPT_GCRYPT
#   include "gcrypt/gcrypt_init.h"
#endif

namespace nebula { namespace crypt { namespace detail {
/** @ingroup Crypt
 * @{
 * */
//------------------------------------------------------------------------------
constexpr static fnd::bitmask_t skip_libgcrypt = 1;
//------------------------------------------------------------------------------
inline void init(const config &cfg, const fnd::bitmask_t x = 0)
{
    if(cfg.secure_memory == 0 && cfg.secure_random_pool)
        n_throw(fnd::logic_error);
    
    #ifdef N_CRYPT_GCRYPT
    if(x & skip_libgcrypt)
        gcrypt::init(false, cfg);
    else
        gcrypt::init(true, cfg);
    #endif // N_CRYPT_GCRYPT
}
//------------------------------------------------------------------------------
inline void shutdown() noexcept
{
    // empty
}

/** @} */

}}} // namespaces

#endif // NIC_0B0684B15EEDD924_NIC

