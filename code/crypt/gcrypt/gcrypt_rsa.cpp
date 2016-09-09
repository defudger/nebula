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

#include "gcrypt_rsa.h"

namespace nebula { namespace crypt { namespace detail { namespace gcrypt {
//------------------------------------------------------------------------------
bool sexp::parse(const char *s, const size_t n)
{
    if(0 == n)
        n_throw(logic_error);
    if(!s)
        n_throw(logic_error);
    
    gcry_sexp_t new_h = nullptr;
    const gcry_error_t err = gcry_sexp_new(&new_h, s, n, 1);
    if(GPG_ERR_NO_ERROR != err)
        return false;
    kill();
    h = new_h;
    return true;
}
//------------------------------------------------------------------------------
void sexp::kill() noexcept
{
    if(h)
    {
        gcry_sexp_release(h);
        h = nullptr;
    }
}

//------------------------------------------------------------------------------
rsa_key_pair generate_rsa_key_pair(const size_t nbits, const unsigned long e)
{
    if(nbits == 0 || nbits > 1024*16 || nbits % 8 != 0)
        n_throw(logic_error);
    
    const fnd::string nbits_s = fmt::to_string(fmt::dec(nbits));
    const fnd::string e_s = fmt::to_string(fmt::dec(e));
    const fnd::string params_s = fmt::to_string(
        "(genkey (rsa ",
            "(nbits ", nbits_s.size(), ':', nbits_s, ')',
            "(rsa-use-e ", e_s.size(), ':', e_s, ')',
            "))");
    sexp params(params_s.data(), params_s.size());
    
    gcry_sexp_t key = nullptr;
    gcry_error_t err = gcry_pk_genkey(&key, params.native_handle());
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_pk_genkey() failed")
        << ei_gcry_error(err);
    }
    
    n_scope_exit(&) {
        gcry_sexp_release(key);
    };
    
    gcry_sexp_t pubk_ = gcry_sexp_find_token(key, "public-key", 0);
    if(!pubk_)
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_sexp_find_token() failed");
    sexp pubk(pubk_);
    
    gcry_sexp_t privk_ = gcry_sexp_find_token(key, "private-key", 0);
    if(!privk_)
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_sexp_find_token() failed");
    sexp privk(privk_);
    
    err = gcry_pk_testkey(privk.native_handle());
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_pk_testkey() says private key is insane.")
        << ei_gcry_error(err);
    }
    
    return rsa_key_pair {
        rsa_private_key(fnd::move(privk)),
        rsa_public_key(fnd::move(pubk))
    };
}
//------------------------------------------------------------------------------
size_t rsa_encrypt(const rsa_public_key &key,
    const char *padding,
    const char *in, const size_t n_in,
    char *out, const size_t n_out)
{
    if(!padding || 0 == n_in || 0 == n_out || !in || !out)
        n_throw(logic_error);
    
    io::msink<fnd::vector<char>> dat;
    fmt::fwrite(dat, "(data (flags ", padding, ") (value ", n_in, ':');
    io::write(dat, in, n_in);
    fmt::fwrite(dat, "))");
    sexp data(dat.container().data(), dat.container().size());
    
    gcry_sexp_t res = nullptr;
    gcry_error_t err = gcry_pk_encrypt(
        &res, data.native_handle(), key.native_handle());
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_pk_encrypt() failed")
        << ei_gcry_error(err);
    }
    n_scope_exit(&) {
        gcry_sexp_release(res);
    };
    
    gcry_buffer_t buffer{0,0,0,nullptr};
    err = gcry_sexp_extract_param(
        res, nullptr, "&a", &buffer, nullptr);
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_sexp_extract_param() failed")
        << ei_gcry_error(err);
    }
    n_scope_exit(&) {
        gcry_free(buffer.data);
    };
    
    math::require_exact_cast<size_t>(buffer.size);
    
    if(n_out < buffer.size)
        n_throw(crypt_error)
        << fnd::ei_msg_c("Buffer too small");
    
    fnd::memcpy(out, buffer.data, buffer.size);
    
    return buffer.size;
}
//------------------------------------------------------------------------------
size_t rsa_decrypt(const rsa_private_key &key,
    const char *padding,
    const char *in, const size_t n_in,
    char *out, const size_t n_out)
{
    if(!padding || 0 == n_in || 0 == n_out || !in || !out)
        n_throw(logic_error);
    
    io::msink<fnd::vector<char>> dat;
    fmt::fwrite(dat, "(enc-val (flags ", padding, ") (rsa (a ", n_in, ':');
    io::write(dat, in, n_in);
    fmt::fwrite(dat, ")))");
    
    sexp data(dat.container().data(), dat.container().size());
    gcry_sexp_t res = nullptr;
    gcry_error_t err = gcry_pk_decrypt(
        &res, data.native_handle(), key.native_handle());
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_pk_decrypt() failed")
        << ei_gcry_error(err);
    }
    n_scope_exit(&) {
        gcry_sexp_release(res);
    };
    
    gcry_buffer_t buffer{0,0,0,nullptr};
    err = gcry_sexp_extract_param(
        res, nullptr, "&'value'", &buffer, nullptr);
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_sexp_extract_param() failed")
        << ei_gcry_error(err);
    }
    n_scope_exit(&) {
        gcry_free(buffer.data);
    };
    
    math::require_exact_cast<size_t>(buffer.size);
    
    if(n_out < buffer.size)
        n_throw(crypt_error)
        << fnd::ei_msg_c("Buffer too small");
    
    fnd::memcpy(out, buffer.data, buffer.size);
    
    return buffer.size;
}
//------------------------------------------------------------------------------
size_t rsa_sign(const rsa_private_key &key,
    const char *padding,
    const char *hash_algo,
    const char *in, const size_t n_in,
    char *out, const size_t n_out)
{
    if(!padding || !hash_algo || 0 == n_in || 0 == n_out || !in || !out)
        n_throw(logic_error);
    
    io::msink<fnd::vector<char>> dat;
    fmt::fwrite(dat, "(data (flags ", padding,
        ") (hash ", hash_algo, ' ', n_in, ':');
    io::write(dat, in, n_in);
    fmt::fwrite(dat, "))");
    
    sexp data(dat.container().data(), dat.container().size());
    gcry_sexp_t res = nullptr;
    gcry_error_t err = gcry_pk_sign(
        &res, data.native_handle(), key.native_handle());
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_pk_sign() failed")
        << ei_gcry_error(err);
    }
    n_scope_exit(&) {
        gcry_sexp_release(res);
    };
    
    gcry_buffer_t buffer{0,0,0,nullptr};
    err = gcry_sexp_extract_param(
        res, nullptr, "&'s'", &buffer, nullptr);
    if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_sexp_extract_param() failed")
        << ei_gcry_error(err);
    }
    n_scope_exit(&) {
        gcry_free(buffer.data);
    };
    
    math::require_exact_cast<size_t>(buffer.size);
    
    if(n_out < buffer.size)
        n_throw(crypt_error)
        << fnd::ei_msg_c("Buffer too small");
    
    fnd::memcpy(out, buffer.data, buffer.size);
    
    return buffer.size;
}
//------------------------------------------------------------------------------
bool rsa_verify(const rsa_public_key &key,
    const char *padding,
    const char *hash_algo,
    const char *sig, const size_t n_sig,
    const char *in, const size_t n_in)
{
    if(!padding || !hash_algo || 0 == n_in || 0 == n_sig || !in || !sig)
        n_throw(logic_error);
    
    io::msink<fnd::vector<char>> dat;
    fmt::fwrite(dat, "(data (flags ", padding,
        ") (hash ", hash_algo, ' ', n_in, ':');
    io::write(dat, in, n_in);
    fmt::fwrite(dat, "))");
    
    sexp data(dat.container().data(), dat.container().size());
    
    io::msink<fnd::vector<char>> sg_;
    fmt::fwrite(sg_, "(sig-val (rsa (s ", n_sig, ':');
    io::write(sg_, sig, n_sig);
    fmt::fwrite(sg_, ")))");
    
    sexp sg(sg_.container().data(), sg_.container().size());
    
    gcry_error_t err = gcry_pk_verify(
        sg.native_handle(), data.native_handle(), key.native_handle());
    
    if(GPG_ERR_BAD_SIGNATURE == gcry_err_code(err))
        return false;
    else if(GPG_ERR_NO_ERROR != err)
    {
        n_throw(crypt_error)
        << fnd::ei_msg_c("gcry_pk_verify() failed")
        << ei_gcry_error(err);
    }
    
    return true;
}

//------------------------------------------------------------------------------
fnd::vector<char> export_rsa_key(const rsa_public_key &key)
{
    size_t n = gcry_sexp_sprint(key.native_handle(), GCRYSEXP_FMT_CANON,
        nullptr, 0);
    fnd::vector<char> s;
    s.resize(n, 0);
    n = gcry_sexp_sprint(key.native_handle(), GCRYSEXP_FMT_CANON,
        s.data(), s.size());
    if(s.size() != n+1)
        n_throw(logic_error);
    return s;
}
//------------------------------------------------------------------------------
fnd::vector<char, secure_allocator<char>> export_rsa_key(
    const rsa_private_key &key)
{
    size_t n = gcry_sexp_sprint(key.native_handle(), GCRYSEXP_FMT_CANON,
        nullptr, 0);
    fnd::vector<char, secure_allocator<char>> s;
    s.resize(n, 0);
    n = gcry_sexp_sprint(key.native_handle(), GCRYSEXP_FMT_CANON,
        s.data(), s.size());
    if(s.size() != n+1)
        n_throw(logic_error);
    return s;
}

}}}} // namespaces

#endif // N_CRYPT_GCRYPT

