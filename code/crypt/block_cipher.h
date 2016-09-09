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
#ifndef NIC_0E483170FB5D2FAE_NIC
#define NIC_0E483170FB5D2FAE_NIC

#include "buffer.h"

#ifdef N_CRYPT_GCRYPT
#   include "gcrypt/gcrypt_cipher.h"
#endif

namespace nebula { namespace crypt { namespace detail {
/** @ingroup Crypt
 * @{
 * */
#ifdef N_CRYPT_GCRYPT
//------------------------------------------------------------------------------
template <
    block_cipher_algorithm Algo,
    block_cipher_mode Mode,
    bool Secure>
class block_cipher : public gcrypt::cipher
{
    struct key_tag_ {};
    struct block_tag_ {};
    
public:
    using algorithm = fnd::integral_constant<block_cipher_algorithm, Algo>;
    using mode = fnd::integral_constant<block_cipher_mode, Mode>;
    using secure = meta::bool_<Secure>;
    using stream_able = meta::bool_<
        Mode == block_cipher_mode::cfb
        || Mode == block_cipher_mode::ofb
        || Mode == block_cipher_mode::ctr>;
    using block_size = block_cipher_algorithm_block_size_c<Algo>;
    using block_type = buffer<
        block_size::value, meta::false_, block_tag_>;
    using key_size = block_cipher_algorithm_key_size_c<Algo>;
    using key_type = buffer<
        key_size::value, secure, key_tag_>;
    
    inline block_cipher()
    : gcrypt::cipher(
        gcrypt::to_gcrypt_block_cipher_algorithm(Algo),
        gcrypt::to_gcrypt_block_cipher_mode(Mode),
        Secure ? GCRY_CIPHER_SECURE : 0)
    {}
    block_cipher(block_cipher &) = delete;
    block_cipher(const block_cipher &) = delete;
    block_cipher(block_cipher &&) = default;
    
    block_cipher &operator = (block_cipher &) = delete;
    block_cipher &operator = (const block_cipher &) = delete;
    block_cipher &operator = (block_cipher &&) = default;
    
    inline void swap(block_cipher &other) noexcept {
        gcrypt::cipher::swap(other);
    }
    
    inline void key(const char *buf, const size_t n) {
        gcrypt::cipher::set_key(buf, n);
    }
    inline void key(const key_type &x) {
        gcrypt::cipher::set_key(x.data(), x.size());
    }
    template <class C = mode,
        fnd::_disable_if_c<C::value == block_cipher_mode::ctr>* = nullptr>
    inline void iv(const char *buf, const size_t n) {
        gcrypt::cipher::set_iv(buf, n);
    }
    template <class C = mode,
        fnd::_disable_if_c<C::value == block_cipher_mode::ctr>* = nullptr>
    inline void iv(const block_type &x) {
        gcrypt::cipher::set_iv(x.data(), x.size());
    }
    template <class C = mode,
        fnd::_enable_if_c<C::value == block_cipher_mode::ctr>* = nullptr>
    inline void ctr(const char *buf, const size_t n) {
        gcrypt::cipher::set_ctr(buf, n);
    }
    template <class C = mode,
        fnd::_enable_if_c<C::value == block_cipher_mode::ctr>* = nullptr>
    inline void ctr(const block_type &x) {
        gcrypt::cipher::set_ctr(x.data(), x.size());
    }
};

#endif

/** @} */

}}} // namespaces

#endif // NIC_0E483170FB5D2FAE_NIC

