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

#include "gcrypt_hash.h"

namespace nebula { namespace crypt { namespace detail { namespace gcrypt {
//------------------------------------------------------------------------------
hash::hash(const int algo, const bool secure)
: h(nullptr)
{
    const gcry_error_t err = gcry_md_open(
        &h, algo, secure ? GCRY_MD_FLAG_SECURE : 0);
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_md_open() failed")
        << ei_gcry_error(err);
    }
}
//------------------------------------------------------------------------------
void hash::write(const char *buf, const io::streamsize n)
{
    n_assert(h);
    
    if(0 == n)
        return;
    if(!buf)
        n_throw(logic_error);
    
    gcry_md_write(h, buf, n);
}
//------------------------------------------------------------------------------
void hash::result(char *buf, const size_t n)
{
    n_assert(h);
    
    if(n == 0)
        n_throw(logic_error);
    if(!buf)
        n_throw(logic_error);
    
    const unsigned int n_ = gcry_md_get_algo_dlen(gcry_md_get_algo(h));
    const char *buf_ = static_cast<const char *>(static_cast<const void *>(
        gcry_md_read(h, 0)));
    if(!buf_)
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_md_read() failed");
    if(n_ != n)
        n_throw(logic_error);
    fnd::iterator::copy(buf_, buf_+n_, buf);
}
//------------------------------------------------------------------------------
void hash::reset() noexcept
{
    n_assert(h);
    gcry_md_reset(h);
}
//------------------------------------------------------------------------------
void hash::kill() noexcept
{
    if(h)
    {
        gcry_md_close(h);
        h = nullptr;
    }
}

}}}} // namespaces

#endif // N_CRYPT_GCRYPT

