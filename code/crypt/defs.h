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
#ifndef NIC_3FA4B9DA2B8D03D3_NIC
#define NIC_3FA4B9DA2B8D03D3_NIC

#include "config.h"
#include "exception.h"

namespace nebula { namespace crypt { namespace detail {
/** @ingroup Crypt
 * @{
 * */
//------------------------------------------------------------------------------
struct config
{
    inline config() noexcept
    : secure_memory(16384),
        secure_random_pool(true),
        quick_random(false)
    {}
    
    size_t secure_memory;
    bool secure_random_pool;
    bool quick_random;
};

//------------------------------------------------------------------------------
enum class hash_algorithm
{
    sha1,
    sha224,
    sha256,
    sha384,
    sha512
};
//------------------------------------------------------------------------------
inline const char *to_cstr(const hash_algorithm x) noexcept
{
    switch(x)
    {
    case hash_algorithm::sha1: return "sha1";
    case hash_algorithm::sha224: return "sha224";
    case hash_algorithm::sha256: return "sha256";
    case hash_algorithm::sha384: return "sha384";
    case hash_algorithm::sha512: return "sha512";
    default: return "unknown";
    }
}

//------------------------------------------------------------------------------
enum class hmac_algorithm
{
    sha1,
    sha224,
    sha256,
    sha384,
    sha512
};
//------------------------------------------------------------------------------
inline const char *to_cstr(const hmac_algorithm x) noexcept
{
    switch(x)
    {
    case hmac_algorithm::sha1: return "sha1";
    case hmac_algorithm::sha224: return "sha224";
    case hmac_algorithm::sha256: return "sha256";
    case hmac_algorithm::sha384: return "sha384";
    case hmac_algorithm::sha512: return "sha512";
    default: return "unknown";
    }
}

//------------------------------------------------------------------------------
enum class block_cipher_algorithm
{
    aes128,
    aes256,
    twofish128,
    twofish256,
    camellia128,
    camellia192,
    camellia256,
    serpent128,
    serpent192,
    serpent256
};
//------------------------------------------------------------------------------
inline const char *to_cstr(const block_cipher_algorithm x) noexcept
{
    switch(x)
    {
    case block_cipher_algorithm::aes128: return "aes128";
    case block_cipher_algorithm::aes256: return "aes256";
    case block_cipher_algorithm::twofish128: return "twofish128";
    case block_cipher_algorithm::twofish256: return "twofish256";
    case block_cipher_algorithm::camellia128: return "camellia128";
    case block_cipher_algorithm::camellia192: return "camellia192";
    case block_cipher_algorithm::camellia256: return "camellia256";
    case block_cipher_algorithm::serpent128: return "serpent128";
    case block_cipher_algorithm::serpent192: return "serpent192";
    case block_cipher_algorithm::serpent256: return "serpent256";
    default: return "unknown";
    }
}

//------------------------------------------------------------------------------
enum class block_cipher_mode
{
    ecb,
    cbc,
    cfb,
    ofb,
    ctr
};
//------------------------------------------------------------------------------
inline const char *to_cstr(const block_cipher_mode x) noexcept
{
    switch(x)
    {
    case block_cipher_mode::ecb: return "ecb";
    case block_cipher_mode::cbc: return "cbc";
    case block_cipher_mode::cfb: return "cfb";
    case block_cipher_mode::ofb: return "ofb";
    case block_cipher_mode::ctr: return "ctr";
    default: return "unknown";
    }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template <hash_algorithm>
struct hash_result_size_bits_c;

template <>
struct hash_result_size_bits_c<hash_algorithm::sha1>
: public meta::size_t_<160>
{};
template <>
struct hash_result_size_bits_c<hash_algorithm::sha224>
: public meta::size_t_<224>
{};
template <>
struct hash_result_size_bits_c<hash_algorithm::sha256>
: public meta::size_t_<256>
{};
template <>
struct hash_result_size_bits_c<hash_algorithm::sha384>
: public meta::size_t_<384>
{};
template <>
struct hash_result_size_bits_c<hash_algorithm::sha512>
: public meta::size_t_<512>
{};

//------------------------------------------------------------------------------
template <hash_algorithm X>
struct hash_result_size_c
: public meta::size_t_<hash_result_size_bits_c<X>::value/n_char_bit>
{};

//------------------------------------------------------------------------------
template <hmac_algorithm>
struct hmac_result_size_bits_c;

template <>
struct hmac_result_size_bits_c<hmac_algorithm::sha1>
: public meta::size_t_<160>
{};
template <>
struct hmac_result_size_bits_c<hmac_algorithm::sha224>
: public meta::size_t_<224>
{};
template <>
struct hmac_result_size_bits_c<hmac_algorithm::sha256>
: public meta::size_t_<256>
{};
template <>
struct hmac_result_size_bits_c<hmac_algorithm::sha384>
: public meta::size_t_<384>
{};
template <>
struct hmac_result_size_bits_c<hmac_algorithm::sha512>
: public meta::size_t_<512>
{};

//------------------------------------------------------------------------------
template <hmac_algorithm X>
struct hmac_result_size_c
: public meta::size_t_<hmac_result_size_bits_c<X>::value/n_char_bit>
{};

//------------------------------------------------------------------------------
template <block_cipher_algorithm>
struct block_cipher_algorithm_block_size_bits_c;

template <>
struct block_cipher_algorithm_block_size_bits_c<
    block_cipher_algorithm::aes128>
: public meta::size_t_<128>
{};
template <>
struct block_cipher_algorithm_block_size_bits_c<
    block_cipher_algorithm::aes256>
: public meta::size_t_<128>
{};
template <>
struct block_cipher_algorithm_block_size_bits_c<
    block_cipher_algorithm::twofish128>
: public meta::size_t_<128>
{};
template <>
struct block_cipher_algorithm_block_size_bits_c<
    block_cipher_algorithm::twofish256>
: public meta::size_t_<128>
{};
template <>
struct block_cipher_algorithm_block_size_bits_c<
    block_cipher_algorithm::camellia128>
: public meta::size_t_<128>
{};
template <>
struct block_cipher_algorithm_block_size_bits_c<
    block_cipher_algorithm::camellia192>
: public meta::size_t_<128>
{};
template <>
struct block_cipher_algorithm_block_size_bits_c<
    block_cipher_algorithm::camellia256>
: public meta::size_t_<128>
{};
template <>
struct block_cipher_algorithm_block_size_bits_c<
    block_cipher_algorithm::serpent128>
: public meta::size_t_<128>
{};
template <>
struct block_cipher_algorithm_block_size_bits_c<
    block_cipher_algorithm::serpent192>
: public meta::size_t_<128>
{};
template <>
struct block_cipher_algorithm_block_size_bits_c<
    block_cipher_algorithm::serpent256>
: public meta::size_t_<128>
{};

//------------------------------------------------------------------------------
template <block_cipher_algorithm X>
struct block_cipher_algorithm_block_size_c
: public meta::size_t_<
    block_cipher_algorithm_block_size_bits_c<X>::value/n_char_bit>
{};

//------------------------------------------------------------------------------
template <block_cipher_algorithm>
struct block_cipher_algorithm_key_size_bits_c;

template <>
struct block_cipher_algorithm_key_size_bits_c<
    block_cipher_algorithm::aes128>
: public meta::size_t_<128>
{};
template <>
struct block_cipher_algorithm_key_size_bits_c<
    block_cipher_algorithm::aes256>
: public meta::size_t_<256>
{};
template <>
struct block_cipher_algorithm_key_size_bits_c<
    block_cipher_algorithm::twofish128>
: public meta::size_t_<128>
{};
template <>
struct block_cipher_algorithm_key_size_bits_c<
    block_cipher_algorithm::twofish256>
: public meta::size_t_<256>
{};
template <>
struct block_cipher_algorithm_key_size_bits_c<
    block_cipher_algorithm::camellia128>
: public meta::size_t_<128>
{};
template <>
struct block_cipher_algorithm_key_size_bits_c<
    block_cipher_algorithm::camellia192>
: public meta::size_t_<192>
{};
template <>
struct block_cipher_algorithm_key_size_bits_c<
    block_cipher_algorithm::camellia256>
: public meta::size_t_<256>
{};
template <>
struct block_cipher_algorithm_key_size_bits_c<
    block_cipher_algorithm::serpent128>
: public meta::size_t_<128>
{};
template <>
struct block_cipher_algorithm_key_size_bits_c<
    block_cipher_algorithm::serpent192>
: public meta::size_t_<192>
{};
template <>
struct block_cipher_algorithm_key_size_bits_c<
    block_cipher_algorithm::serpent256>
: public meta::size_t_<256>
{};

//------------------------------------------------------------------------------
template <block_cipher_algorithm X>
struct block_cipher_algorithm_key_size_c
: public meta::size_t_<
    block_cipher_algorithm_key_size_bits_c<X>::value/n_char_bit>
{};

//------------------------------------------------------------------------------
template <block_cipher_algorithm X>
struct block_cipher_algorithm_initialization_vector_size_bits_c
: public block_cipher_algorithm_block_size_bits_c<X>
{};
//------------------------------------------------------------------------------
template <block_cipher_algorithm X>
struct block_cipher_algorithm_initialization_vector_size_c
: public meta::size_t_<
    block_cipher_algorithm_initialization_vector_size_bits_c<X>::value
        / n_char_bit>
{};

/** @} */

}}} // namespaces

#endif // NIC_3FA4B9DA2B8D03D3_NIC

