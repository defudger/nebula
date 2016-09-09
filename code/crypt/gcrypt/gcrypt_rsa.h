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
#ifndef NIC_B668EF8DD8BE5BCD_NIC
#define NIC_B668EF8DD8BE5BCD_NIC

#include "../secure_allocator.h"

namespace nebula { namespace crypt { namespace detail { namespace gcrypt {
/** @ingroup Crypt
 * @{
 * */
//------------------------------------------------------------------------------
class n_crypt_dll sexp
{
public:
    sexp(gcry_sexp_t x = nullptr) noexcept
    : h(x)
    {}
    inline sexp(const char *s, const size_t n)
    : h(nullptr)
    {
        if(!parse(s, n))
            n_throw(crypt_error);
    }
    sexp(sexp &) = delete;
    sexp(const sexp &) = delete;
    sexp(sexp &&other) noexcept
    : h(other.h)
    {
        other.h = nullptr;
    }
    inline ~sexp() noexcept {
        kill();
    }
    
    sexp &operator = (sexp &) = delete;
    sexp &operator = (const sexp &) = delete;
    sexp &operator = (sexp &&other) noexcept {
        kill();
        h = other.h;
        other.h = nullptr;
        return *this;
    }
    
    bool parse(const char *s, const size_t n);
    
    inline void swap(sexp &other) noexcept {
        fnd::swap(h, other.h);
    }
    
    inline gcry_sexp_t native_handle() const noexcept {
        return h;
    }
    inline gcry_sexp_t dismiss() noexcept {
        gcry_sexp_t tmp = h;
        h = nullptr;
        return tmp;
    }
    
private:
    void kill() noexcept;

    gcry_sexp_t h;
};

//------------------------------------------------------------------------------
class rsa_private_key
{
    using container_t = fnd::vector<char, secure_allocator<char>>;
    
public:
    rsa_private_key() = default;
    
    inline rsa_private_key(sexp &&y) noexcept
    : x(fnd::move(y))
    {}
    inline rsa_private_key(const char *buf, const size_t n_buf)
    : x(buf, n_buf)
    {}
    
    inline void swap(rsa_private_key &other) noexcept {
        fnd::swap(x, other.x);
    }
    
    template <class Buffer>
    inline bool parse(const Buffer &buf) {
        return x.parse(buf.data(), buf.size());
    }
    
    inline gcry_sexp_t native_handle() const noexcept {
        return x.native_handle();
    }
    inline gcry_sexp_t dismiss() noexcept {
        return x.dismiss();
    }

private:
    sexp x;
};
//------------------------------------------------------------------------------
class rsa_public_key
{
public:
    rsa_public_key() = default;

    inline rsa_public_key(sexp &&y) noexcept
    : x(fnd::move(y))
    {}
    inline rsa_public_key(const char *buf, const size_t n_buf)
    : x(buf, n_buf)
    {}
    
    inline void swap(rsa_public_key &other) noexcept {
        fnd::swap(x, other.x);
    }
    
    template <class Buffer>
    inline bool parse(const Buffer &buf) {
        return x.parse(buf.data(), buf.size());
    }
    
    inline gcry_sexp_t native_handle() const noexcept {
        return x.native_handle();
    }
    inline gcry_sexp_t dismiss() noexcept {
        return x.dismiss();
    }
    
private:
    sexp x;
};

//------------------------------------------------------------------------------
struct rsa_key_pair {
    rsa_private_key private_key;
    rsa_public_key public_key;
};
//------------------------------------------------------------------------------
extern rsa_key_pair n_crypt_dll generate_rsa_key_pair(
    const size_t nbits,
    const unsigned long e = 0);
//------------------------------------------------------------------------------
extern size_t n_crypt_dll rsa_encrypt(const rsa_public_key &k,
    const char *padding,
    const char *in, const size_t n_in,
    char *out, const size_t n_out);
//------------------------------------------------------------------------------
extern size_t n_crypt_dll rsa_decrypt(const rsa_private_key &k,
    const char *padding,
    const char *in, const size_t n_in,
    char *out, const size_t n_out);
//------------------------------------------------------------------------------
extern size_t n_crypt_dll rsa_sign(const rsa_private_key &k,
    const char *padding,
    const char *hash_algo,
    const char *in, const size_t n_in,
    char *out, const size_t n_out);
//------------------------------------------------------------------------------
extern bool n_crypt_dll rsa_verify(const rsa_public_key &k,
    const char *padding,
    const char *hash_algo,
    const char *sig, const size_t n_sig,
    const char *in, const size_t n_in);

//------------------------------------------------------------------------------
extern fnd::vector<char> n_crypt_dll export_rsa_key(const rsa_public_key &key);
//------------------------------------------------------------------------------
extern fnd::vector<char, secure_allocator<char>> n_crypt_dll
export_rsa_key(const rsa_private_key &key);

/** @} */

}}}} // namespaces

#endif // NIC_B668EF8DD8BE5BCD_NIC

