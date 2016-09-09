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
#include "../config.h"
#ifdef N_CRYPT_GCRYPT

#include "gcrypt_error.h"

namespace nebula { namespace crypt { namespace detail { namespace gcrypt {
//------------------------------------------------------------------------------
void init(bool do_init, const config &cfg)
{
    gcry_error_t err = GPG_ERR_NO_ERROR;
    
    if(!do_init)
    {
        if(!gcry_control(GCRYCTL_INITIALIZATION_FINISHED_P))
        {
            n_throw(crypt_error)
            << fnd::ei_msg_c("libgcrypt is not initialized.");
        }
    }
    
    if(!gcry_check_version("1.6.3"))
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("Outdated libgcrypt");
    }
    
    if(do_init)
    {
        if(cfg.secure_random_pool)
        {
            err = gcry_control(GCRYCTL_USE_SECURE_RNDPOOL, 0);
            if(GPG_ERR_NO_ERROR != err)
            {
                n_throw(crypt_error)
                << fnd::ei_msg_c("gcry_control() failed")
                << ei_gcry_error(err);
            }
        }
        
        if(cfg.secure_memory > 0)
        {
            math::require_exact_cast<int>(cfg.secure_memory);
            const int n = cfg.secure_memory;
            err = gcry_control(GCRYCTL_INIT_SECMEM, n, 0);
            if(GPG_ERR_NO_ERROR != err)
            {
                n_throw(crypt_error)
                << fnd::ei_msg_c("gcry_control() failed")
                << ei_gcry_error(err);
            }
        }
        else
        {
            err = gcry_control(GCRYCTL_DISABLE_SECMEM, 0);
            if(GPG_ERR_NO_ERROR != err)
            {
                n_throw(crypt_error)
                << fnd::ei_msg_c("gcry_control() failed")
                << ei_gcry_error(err);
            }
        }
        
        #ifdef N_OS_LINUX
            err = gcry_control(GCRYCTL_SET_PREFERRED_RNG_TYPE,
                GCRY_RNG_TYPE_SYSTEM, 0);
            if(GPG_ERR_NO_ERROR != err)
            {
                n_throw(crypt_error)
                << fnd::ei_msg_c("gcry_control() failed")
                << ei_gcry_error(err);
            }
        #else
            err = gcry_control(GCRYCTL_SET_PREFERRED_RNG_TYPE,
                GCRY_RNG_TYPE_STANDARD, 0);
            if(GPG_ERR_NO_ERROR != err)
            {
                n_throw(crypt_error)
                << fnd::ei_msg_c("gcry_control() failed")
                << ei_gcry_error(err);
            }
        #endif // N_OS_LINUX
        
        if(cfg.quick_random)
        {
            err = gcry_control(GCRYCTL_ENABLE_QUICK_RANDOM, 0);
            if(GPG_ERR_NO_ERROR != err)
            {
                n_throw(crypt_error)
                << fnd::ei_msg_c("gcry_control() failed")
                << ei_gcry_error(err);
            }
        }
        
        err = gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);
        if(GPG_ERR_NO_ERROR != err)
        {
            n_throw(crypt_error)
            << fnd::ei_msg_c("gcry_control() failed")
            << ei_gcry_error(err);
        }
    }
}

}}}} // namespaces

#endif // N_CRYPT_GCRYPT

