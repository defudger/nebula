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

#include "gcrypt_cipher.h"

namespace nebula { namespace crypt { namespace detail { namespace gcrypt {
//------------------------------------------------------------------------------
cipher::cipher(const int algo, const int mode, const int flags)
: h(nullptr)
{
    const gcry_error_t err = gcry_cipher_open(&h, algo, mode, flags);
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_cipher_open() failed")
        << ei_gcry_error(err);
    }
}
//------------------------------------------------------------------------------
void cipher::set_key(const char *buf, const size_t n)
{
    n_assert(h);
    
    if(!buf)
        n_throw(logic_error);
    if(0 == n)
        n_throw(logic_error);
    
    const gcry_error_t err = gcry_cipher_setkey(h, buf, n);
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_cipher_setkey() failed")
        << ei_gcry_error(err);
    }
}
//------------------------------------------------------------------------------
void cipher::set_iv(const char *buf, const size_t n)
{
    n_assert(h);
    
    if(!buf)
        n_throw(logic_error);
    if(0 == n)
        n_throw(logic_error);
    
    const gcry_error_t err = gcry_cipher_setiv(h, buf, n);
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_cipher_setiv() failed")
        << ei_gcry_error(err);
    }
}
//------------------------------------------------------------------------------
void cipher::set_ctr(const char *buf, const size_t n)
{
    n_assert(h);
    
    if(!buf)
        n_throw(logic_error);
    if(0 == n)
        n_throw(logic_error);
    
    const gcry_error_t err = gcry_cipher_setctr(h, buf, n);
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_cipher_setctr() failed")
        << ei_gcry_error(err);
    }
}
//------------------------------------------------------------------------------
size_t cipher::encrypt(const char *in, const size_t n_in,
        char *out, const size_t n_out)
{
    n_assert(h);
    
    if(n_in == 0)
        return 0;
    if(!in || !out || !n_out)
        n_throw(logic_error);
    
    const gcry_error_t err = gcry_cipher_encrypt(h,
        static_cast<unsigned char *>(static_cast<void *>(out)),
        n_out,
        static_cast<const unsigned char *>(static_cast<const void *>(in)),
        n_in);
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_cipher_encrypt() failed")
        << ei_gcry_error(err);
    }
    
    return n_in;
}
//------------------------------------------------------------------------------
void cipher::encrypt(char *inout, const size_t n)
{
    n_assert(h);
    
    if(0 == n)
        return;
    if(!inout)
        n_throw(logic_error);
    
    const gcry_error_t err = gcry_cipher_encrypt(h,
        static_cast<unsigned char *>(static_cast<void *>(inout)),
        n,
        nullptr,
        0);
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_cipher_encrypt() failed")
        << ei_gcry_error(err);
    }
}
//------------------------------------------------------------------------------
size_t cipher::decrypt(const char *in, const size_t n_in,
        char *out, const size_t n_out)
{
    n_assert(h);
    
    if(n_in == 0)
        return 0;
    if(!in || !out || !n_out)
        n_throw(logic_error);
    
    const gcry_error_t err = gcry_cipher_decrypt(h,
        static_cast<unsigned char *>(static_cast<void *>(out)),
        n_out,
        static_cast<const unsigned char *>(static_cast<const void *>(in)),
        n_in);
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_cipher_decrypt() failed")
        << ei_gcry_error(err);
    }
    
    return n_in;
}
//------------------------------------------------------------------------------
void cipher::decrypt(char *inout, const size_t n)
{
    n_assert(h);
    
    if(0 == n)
        return;
    if(!inout)
        n_throw(logic_error);
    
    const gcry_error_t err = gcry_cipher_decrypt(h,
        static_cast<unsigned char *>(static_cast<void *>(inout)),
        n,
        nullptr,
        0);
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_cipher_decrypt() failed")
        << ei_gcry_error(err);
    }
}
//------------------------------------------------------------------------------
void cipher::reset()
{
    n_assert(h);
    
    const gcry_error_t err = gcry_cipher_reset(h);
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_cipher_setctr() failed")
        << ei_gcry_error(err);
    }
}
//------------------------------------------------------------------------------
void cipher::kill() noexcept
{
    if(h)
    {
        gcry_cipher_close(h);
        h = nullptr;
    }
}

}}}} // namespaces

#endif // N_CRYPT_GCRYPT

