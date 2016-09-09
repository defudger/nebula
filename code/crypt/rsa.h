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
#ifndef NIC_46E541897D6DBBC5_NIC
#define NIC_46E541897D6DBBC5_NIC

#include "hash.h"
#include "error.h"

#ifdef N_CRYPT_GCRYPT
#   include "gcrypt/gcrypt_rsa.h"
#endif

namespace nebula { namespace crypt { namespace detail { namespace rsa {
/** @ingroup Crypt
 * @{
 * */
//------------------------------------------------------------------------------
enum class padding
{
    oaep,
    pkcs1,
    pss
};
//------------------------------------------------------------------------------
inline const char *to_cstr(const padding x) noexcept
{
    switch(x)
    {
    case padding::oaep: return "oaep";
    case padding::pkcs1: return "pkcs1";
    case padding::pss: return "pss";
    default: return "unknown";
    }
}

#ifdef N_CRYPT_GCRYPT
//------------------------------------------------------------------------------
template <size_t NBits,
    padding EncryptionPadding = padding::oaep,
    padding SignaturePadding = padding::pss>
class public_key
{
    static constexpr padding enc_pad = EncryptionPadding;
    static constexpr padding sig_pad = SignaturePadding;
    
public:
    using secure = meta::false_;
    using stream_able = meta::false_;
    using key_size = meta::size_t_<NBits / n_char_bit>;
    
    public_key() = default;
    public_key(public_key &) = delete;
    public_key(const public_key &) = delete;
    public_key(public_key &&) = default;
    
    template <class Buffer>
    inline public_key(Buffer &&buf)
    {
        io::msink<fnd::vector<char, secure_allocator<char>>> strm;
        fmt::fwrite(strm, fmt::base64_d(buf.data(), buf.size()));
        key_ = gcrypt::rsa_private_key(
            strm.container().data(), strm.container().size());
    }
    
    inline public_key(gcrypt::rsa_public_key &&x) noexcept
    : key_(fnd::move(x))
    {}
    
    public_key &operator = (public_key &) = delete;
    public_key &operator = (const public_key &) = delete;
    public_key &operator = (public_key &&) = default;
    
    void swap(public_key &other) noexcept {
        fnd::swap(key_, other.key_);
    }
    
    inline size_t encrypt(const char *in, const size_t n_in,
        char *out, const size_t n_out) const
    {
        return gcrypt::rsa_encrypt(key_, to_cstr(enc_pad),
            in, n_in,
            out, n_out);
    }
    template <class Hash>
    inline bool verify(
        Hash &&h,
        const char *sig, const size_t n_sig,
        const char *in, const size_t n_in) const
    {
        io::write(h, in, n_in);
        traits::_hash_result<ctraits::_value<Hash>> hr = h.result();
        
        return gcrypt::rsa_verify(key_,
            to_cstr(sig_pad),
            to_cstr(traits::_algorithm<ctraits::_value<Hash>>::value),
            sig, n_sig, hr.data(), hr.size());
    }
    
    template <class Stream>
    inline void save(Stream &&strm) const
    {
        auto x = gcrypt::export_rsa_key(key_);
        math::require_exact_cast<uint16_t>(x.size());
        io::put(strm, 1);
        uint16_t n = x.size();
        n = endian::htole(n);
        io::write(strm,
            static_cast<const char *>(static_cast<const void *>(&n)), 2);
        io::write(strm,
            x.data(), x.size());
    }
    template <class Stream>
    inline errc load(Stream &&strm)
    {
        io::ceof ver = io::get(strm);
        if(ver.eof())
            return errc::eof;
        if(ver.get() != 1)
            return errc::invalid_version;
        uint16_t n = 0;
        auto nr = io::read(strm,
            static_cast<char *>(static_cast<void *>(&n)), 2);
        if(nr < 2)
            return errc::eof;
        fnd::vector<char> buf;
        buf.resize(n);
        nr = io::read(strm, buf.data(), buf.size());
        if(nr < n)
            return errc::eof;
        if(!key_.parse(buf))
            return errc::general_error;
        return errc::success;
    }
    
private:
    gcrypt::rsa_public_key key_;
};
//------------------------------------------------------------------------------
template <size_t NBits,
    padding EncryptionPadding = padding::oaep,
    padding SignaturePadding = padding::pss>
class private_key
{
    static constexpr padding enc_pad = EncryptionPadding;
    static constexpr padding sig_pad = SignaturePadding;
    
public:
    using secure = meta::true_;
    using stream_able = meta::false_;
    
    private_key() = default;
    private_key(private_key &) = delete;
    private_key(const private_key &) = delete;
    private_key(private_key &&) = default;
    
    inline private_key(gcrypt::rsa_private_key &&x) noexcept
    : key_(fnd::move(x))
    {}
    
    private_key &operator = (private_key &) = delete;
    private_key &operator = (const private_key &) = delete;
    private_key &operator = (private_key &&) = default;
    
    void swap(private_key &other) noexcept {
        fnd::swap(key_, other.key_);
    }
    
    inline size_t decrypt(const char *in, const size_t n_in,
        char *out, const size_t n_out) const
    {
        return gcrypt::rsa_decrypt(key_, to_cstr(enc_pad),
            in, n_in,
            out, n_out);
    }
    template <class Hash>
    inline size_t sign(
        Hash &&h,
        const char *in, const size_t n_in,
        char *out, const size_t n_out) const
    {
        io::write(h, in, n_in);
        traits::_hash_result<ctraits::_value<Hash>> hr = h.result();
        
        return gcrypt::rsa_sign(key_,
            to_cstr(sig_pad),
            to_cstr(traits::_algorithm<ctraits::_value<Hash>>::value),
            hr.data(), hr.size(), out, n_out);
    }
    
    template <class Stream>
    inline void save(Stream &&strm) const
    {
        auto x = gcrypt::export_rsa_key(key_);
        math::require_exact_cast<uint16_t>(x.size());
        io::put(strm, 1);
        uint16_t n = x.size();
        n = endian::htole(n);
        io::write(strm,
            static_cast<const char *>(static_cast<const void *>(&n)), 2);
        io::write(strm,
            x.data(), x.size());
    }
    template <class Stream>
    inline errc load(Stream &&strm)
    {
        io::ceof ver = io::get(strm);
        if(ver.eof())
            return errc::eof;
        if(ver.get() != 1)
            return errc::invalid_version;
        uint16_t n = 0;
        auto nr = io::read(strm,
            static_cast<char *>(static_cast<void *>(&n)), 2);
        if(nr < 2)
            return errc::eof;
        fnd::vector<char, secure_allocator<char>> buf;
        buf.resize(n);
        nr = io::read(strm, buf.data(), buf.size());
        if(nr < n)
            return errc::eof;
        if(!key_.parse(buf))
            return errc::general_error;
        return errc::success;
    }
    
private:
    gcrypt::rsa_private_key key_;
};

//------------------------------------------------------------------------------
template <size_t NBits, padding EncryptionPadding, padding SignaturePadding>
void generate_key_pair(
    public_key<NBits, EncryptionPadding, SignaturePadding> &pub_k,
    private_key<NBits, EncryptionPadding, SignaturePadding> &priv_k,
    const unsigned long e = 0)
{
    gcrypt::rsa_key_pair kp = gcrypt::generate_rsa_key_pair(NBits, e);
    pub_k = fnd::move(kp.public_key);
    priv_k = fnd::move(kp.private_key);
}

#endif // N_CRYPT_GCRYPT

/** @} */

}}}} // namespaces

#endif // NIC_46E541897D6DBBC5_NIC

