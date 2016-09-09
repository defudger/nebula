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
#ifndef NIC_93AF5196DDDDC6DE_NIC
#define NIC_93AF5196DDDDC6DE_NIC

#include "../config.h"
#include "../defs.h"

#ifdef N_CRYPT_GCRYPT
#   include <gcrypt.h>
#endif

namespace nebula { namespace crypt { namespace detail { namespace gcrypt {
/** @ingroup Crypt
 * @{
 * */
//------------------------------------------------------------------------------
inline int to_gcrypt_hash_algorithm(const hash_algorithm x)
{
    switch(x)
    {
    case hash_algorithm::sha1: return GCRY_MD_SHA1;
    case hash_algorithm::sha224: return GCRY_MD_SHA224;
    case hash_algorithm::sha256: return GCRY_MD_SHA256;
    case hash_algorithm::sha384: return GCRY_MD_SHA384;
    case hash_algorithm::sha512: return GCRY_MD_SHA512;
    default:
        n_throw(logic_error);
    }
}
//------------------------------------------------------------------------------
inline hash_algorithm to_hash_algorithm(const int x)
{
    switch(x)
    {
    case GCRY_MD_SHA1: return hash_algorithm::sha1;
    case GCRY_MD_SHA224: return hash_algorithm::sha224;
    case GCRY_MD_SHA256: return hash_algorithm::sha256;
    case GCRY_MD_SHA384: return hash_algorithm::sha384;
    case GCRY_MD_SHA512: return hash_algorithm::sha512;
    default:
        n_throw(logic_error);
    }
}

//------------------------------------------------------------------------------
inline int to_gcrypt_mac_algorithm(const hmac_algorithm x)
{
    switch(x)
    {
    case hmac_algorithm::sha1: return GCRY_MAC_HMAC_SHA1;
    case hmac_algorithm::sha224: return GCRY_MAC_HMAC_SHA224;
    case hmac_algorithm::sha256: return GCRY_MAC_HMAC_SHA256;
    case hmac_algorithm::sha384: return GCRY_MAC_HMAC_SHA384;
    case hmac_algorithm::sha512: return GCRY_MAC_HMAC_SHA512;
    default:
        n_throw(logic_error);
    }
}
//------------------------------------------------------------------------------
inline hmac_algorithm to_hmac_algorithm(const int x)
{
    switch(x)
    {
    case GCRY_MAC_HMAC_SHA1: return hmac_algorithm::sha1;
    case GCRY_MAC_HMAC_SHA224: return hmac_algorithm::sha224;
    case GCRY_MAC_HMAC_SHA256: return hmac_algorithm::sha256;
    case GCRY_MAC_HMAC_SHA384: return hmac_algorithm::sha384;
    case GCRY_MAC_HMAC_SHA512: return hmac_algorithm::sha512;
    default:
        n_throw(logic_error);
    }
}

//------------------------------------------------------------------------------
inline int to_gcrypt_block_cipher_algorithm(const block_cipher_algorithm x)
{
    switch(x)
    {
    case block_cipher_algorithm::aes128:
        return GCRY_CIPHER_AES128;
    case block_cipher_algorithm::aes256:
        return GCRY_CIPHER_AES256;
    case block_cipher_algorithm::twofish128:
        return GCRY_CIPHER_TWOFISH128;
    case block_cipher_algorithm::twofish256:
        return GCRY_CIPHER_TWOFISH;
    case block_cipher_algorithm::camellia128:
        return GCRY_CIPHER_CAMELLIA128;
    case block_cipher_algorithm::camellia192:
        return GCRY_CIPHER_CAMELLIA192;
    case block_cipher_algorithm::camellia256:
        return GCRY_CIPHER_CAMELLIA256;
    case block_cipher_algorithm::serpent128:
        return GCRY_CIPHER_SERPENT128;
    case block_cipher_algorithm::serpent192:
        return GCRY_CIPHER_SERPENT192;
    case block_cipher_algorithm::serpent256:
        return GCRY_CIPHER_SERPENT256;
    default:
        n_throw(logic_error);
    }
}
//------------------------------------------------------------------------------
inline block_cipher_algorithm to_block_cipher_algorithm(const int x)
{
    switch(x)
    {
    case GCRY_CIPHER_AES128:
        return block_cipher_algorithm::aes128;
    case GCRY_CIPHER_AES256:
        return block_cipher_algorithm::aes256;
    case GCRY_CIPHER_TWOFISH128:
        return block_cipher_algorithm::twofish128;
    case GCRY_CIPHER_TWOFISH:
        return block_cipher_algorithm::twofish256;
    case GCRY_CIPHER_CAMELLIA128:
        return block_cipher_algorithm::camellia128;
    case GCRY_CIPHER_CAMELLIA192:
        return block_cipher_algorithm::camellia192;
    case GCRY_CIPHER_CAMELLIA256:
        return block_cipher_algorithm::camellia256;
    case GCRY_CIPHER_SERPENT128:
        return block_cipher_algorithm::serpent128;
    case GCRY_CIPHER_SERPENT192:
        return block_cipher_algorithm::serpent192;
    case GCRY_CIPHER_SERPENT256:
        return block_cipher_algorithm::serpent256;
    default:
        n_throw(logic_error);
    }
}

//------------------------------------------------------------------------------
inline int to_gcrypt_block_cipher_mode(const block_cipher_mode x)
{
    switch(x)
    {
    case block_cipher_mode::ecb: return GCRY_CIPHER_MODE_ECB;
    case block_cipher_mode::cbc: return GCRY_CIPHER_MODE_CBC;
    case block_cipher_mode::cfb: return GCRY_CIPHER_MODE_CFB;
    case block_cipher_mode::ofb: return GCRY_CIPHER_MODE_OFB;
    case block_cipher_mode::ctr: return GCRY_CIPHER_MODE_CTR;
    default:
        n_throw(logic_error);
    }
}
//------------------------------------------------------------------------------
inline block_cipher_mode to_block_cipher_mode(const int x)
{
    switch(x)
    {
    case GCRY_CIPHER_MODE_ECB: return block_cipher_mode::ecb;
    case GCRY_CIPHER_MODE_CBC: return block_cipher_mode::cbc;
    case GCRY_CIPHER_MODE_CFB: return block_cipher_mode::cfb;
    case GCRY_CIPHER_MODE_OFB: return block_cipher_mode::ofb;
    case GCRY_CIPHER_MODE_CTR: return block_cipher_mode::ctr;
    default:
        n_throw(logic_error);
    }
}

/** @} */

}}}} // namespaces

#endif // NIC_93AF5196DDDDC6DE_NIC

