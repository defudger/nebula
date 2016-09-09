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
#ifndef NIC_33B40E8D8CC9FA13_NIC
#define NIC_33B40E8D8CC9FA13_NIC

#include "gcrypt_error.h"

namespace nebula { namespace crypt { namespace detail { namespace gcrypt {
/** @ingroup Crypt
 * @{
 * */
//------------------------------------------------------------------------------
class n_crypt_dll cipher
{
public:
    inline cipher() noexcept
    : h(nullptr)
    {}
    inline cipher(cipher &other) = delete;
    inline cipher(const cipher &other) = delete;
    inline cipher(cipher &&other) noexcept
    : h(other.h)
    {
        other.h = nullptr;
    }
    
    cipher(const int algo, const int mode, const int flags);
    
    inline ~cipher() noexcept {
        kill();
    }
    
    inline cipher &operator = (cipher &other)  = delete;
    inline cipher &operator = (const cipher &other) = delete;
    inline cipher &operator = (cipher &&other) noexcept {
        kill();
        h = other.h;
        other.h = nullptr;
        return *this;
    }
    
    inline void swap(cipher &other) noexcept {
        fnd::swap(h, other.h);
    }

    inline gcry_cipher_hd_t native_handle() const noexcept {
        return h;
    }
    inline gcry_cipher_hd_t dismiss() noexcept {
        gcry_cipher_hd_t tmp = h;
        h = nullptr;
        return tmp;
    }
    
    void set_key(const char *buf, const size_t n);
    void set_iv(const char *buf, const size_t n);
    void set_ctr(const char *buf, const size_t n);
    
    size_t encrypt(const char *in, const size_t n_in,
        char *out, const size_t n_out);
    void encrypt(char *inout, const size_t n);
    size_t decrypt(const char *in, const size_t n_in,
        char *out, const size_t n_out);
    void decrypt(char *inout, const size_t n);
    
    void reset();
    
private:
    void kill() noexcept;
    
    gcry_cipher_hd_t h;
};

/** @} */

}}}} // namespaces

#endif // NIC_33B40E8D8CC9FA13_NIC

