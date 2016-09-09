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

#include "gcrypt_mac.h"

namespace nebula { namespace crypt { namespace detail { namespace gcrypt {
//------------------------------------------------------------------------------
mac::mac(const int algo, const int flags)
: h(nullptr)
{
    const gcry_error_t err = gcry_mac_open(&h, algo, flags, nullptr /* ctx */);
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_mac_open() failed")
        << ei_gcry_error(err);
    }
}
//------------------------------------------------------------------------------
void mac::set_key(const char *buf, const size_t n)
{
    n_assert(h);
    
    if(!buf)
        n_throw(logic_error);
    if(0 == n)
        n_throw(logic_error);
    
    const gcry_error_t err = gcry_mac_setkey(h, buf, n);
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_mac_setkey() failed")
        << ei_gcry_error(err);
    }
}
//------------------------------------------------------------------------------
void mac::set_iv(const char *buf, const size_t n)
{
    n_assert(h);
    
    if(!buf)
        n_throw(logic_error);
    if(0 == n)
        n_throw(logic_error);
    
    const gcry_error_t err = gcry_mac_setiv(h, buf, n);
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_mac_setiv() failed")
        << ei_gcry_error(err);
    }
}
//------------------------------------------------------------------------------
void mac::write(const char *buf, const size_t n)
{
    n_assert(h);
    
    if(0 == n)
        return;
    if(!buf)
        n_throw(logic_error);
    
    const gcry_error_t err = gcry_mac_write(h, buf, n);
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_mac_write() failed")
        << ei_gcry_error(err);
    }
}
//------------------------------------------------------------------------------
void mac::result(char *buf, const size_t n)
{
    n_assert(h);
    
    if(!buf || 0 == n)
        n_throw(logic_error);
    
    size_t m = n;
    const gcry_error_t err = gcry_mac_read(h, buf, &m);
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_mac_read() failed")
        << ei_gcry_error(err);
    }
    
    if(m != n)
        n_throw(logic_error);
}
//------------------------------------------------------------------------------
bool mac::verify(const char *buf, const size_t n)
{
    n_assert(h);
    
    if(!buf || 0 == n)
        n_throw(logic_error);
    
    const gcry_error_t err = gcry_mac_verify(h, buf, n);
    if(GPG_ERR_CHECKSUM == gcry_err_code(err))
        return false;
    else if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_mac_verify() failed")
        << ei_gcry_error(err);
    }
    
    return true;
}
//------------------------------------------------------------------------------
void mac::reset()
{
    n_assert(h);
    
    const gcry_error_t err = gcry_mac_reset(h);
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_mac_reset() failed")
        << ei_gcry_error(err);
    }
}
//------------------------------------------------------------------------------
void mac::kill() noexcept
{
    if(h)
    {
        gcry_mac_close(h);
        h = nullptr;
    }
}

}}}} // namespaces

#endif // N_CRYPT_GCRYPT

