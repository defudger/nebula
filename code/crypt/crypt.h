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
#ifndef NIC_278E6EAD0FF66864_NIC
#define NIC_278E6EAD0FF66864_NIC

#include "block_cipher.h"
#include "error.h"
#include "hash.h"
#include "hmac.h"
#include "init.h"
#include "io_adaptor.h"
#include "random.h"
#include "rsa.h"
#include "secure_allocator.h"

namespace nebula {
/** @ingroup Crypt
 * @{
 * */
//------------------------------------------------------------------------------
/** 
 * */
namespace crypt {
//------------------------------------------------------------------------------
using detail::crypt_error_category;
using detail::errc;
using detail::crypt_error;

//------------------------------------------------------------------------------
using detail::config;
using detail::skip_libgcrypt;
using detail::init;
using detail::shutdown;

//------------------------------------------------------------------------------
using detail::block_cipher_algorithm;
using detail::block_cipher_mode;

using detail::block_cipher;

//------------------------------------------------------------------------------
using detail::hash_algorithm;

using detail::hash;

//------------------------------------------------------------------------------
using detail::hmac_algorithm;

using detail::hmac;

//------------------------------------------------------------------------------
using detail::pseudo_random_device;
using detail::random_device;

//---------------------------------------------------------------------------
namespace rsa = detail::rsa;

//------------------------------------------------------------------------------
using detail::secure_allocator;

//------------------------------------------------------------------------------
using detail::stream_encrypt;
using detail::stream_decrypt;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
using aes128_cbc_cipher = block_cipher<
    block_cipher_algorithm::aes128,
    block_cipher_mode::cbc,
    false>;
using aes256_cbc_cipher = block_cipher<
    block_cipher_algorithm::aes256,
    block_cipher_mode::cbc,
    false>;
using twofish128_cbc_cipher = block_cipher<
    block_cipher_algorithm::twofish128,
    block_cipher_mode::cbc,
    false>;
using twofish256_cbc_cipher = block_cipher<
    block_cipher_algorithm::twofish256,
    block_cipher_mode::cbc,
    false>;
using camellia128_cbc_cipher = block_cipher<
    block_cipher_algorithm::camellia128,
    block_cipher_mode::cbc,
    false>;
using camellia192_cbc_cipher = block_cipher<
    block_cipher_algorithm::camellia192,
    block_cipher_mode::cbc,
    false>;
using camellia256_cbc_cipher = block_cipher<
    block_cipher_algorithm::camellia256,
    block_cipher_mode::cbc,
    false>;
using serpent128_cbc_cipher = block_cipher<
    block_cipher_algorithm::serpent128,
    block_cipher_mode::cbc,
    false>;
using serpent192_cbc_cipher = block_cipher<
    block_cipher_algorithm::serpent192,
    block_cipher_mode::cbc,
    false>;
using serpent256_cbc_cipher = block_cipher<
    block_cipher_algorithm::serpent256,
    block_cipher_mode::cbc,
    false>;
    
using aes128_cfb_cipher = block_cipher<
    block_cipher_algorithm::aes128,
    block_cipher_mode::cfb,
    false>;
using aes256_cfb_cipher = block_cipher<
    block_cipher_algorithm::aes256,
    block_cipher_mode::cfb,
    false>;
using twofish128_cfb_cipher = block_cipher<
    block_cipher_algorithm::twofish128,
    block_cipher_mode::cfb,
    false>;
using twofish256_cfb_cipher = block_cipher<
    block_cipher_algorithm::twofish256,
    block_cipher_mode::cfb,
    false>;
using camellia128_cfb_cipher = block_cipher<
    block_cipher_algorithm::camellia128,
    block_cipher_mode::cfb,
    false>;
using camellia192_cfb_cipher = block_cipher<
    block_cipher_algorithm::camellia192,
    block_cipher_mode::cfb,
    false>;
using camellia256_cfb_cipher = block_cipher<
    block_cipher_algorithm::camellia256,
    block_cipher_mode::cfb,
    false>;
using serpent128_cfb_cipher = block_cipher<
    block_cipher_algorithm::serpent128,
    block_cipher_mode::cfb,
    false>;
using serpent192_cfb_cipher = block_cipher<
    block_cipher_algorithm::serpent192,
    block_cipher_mode::cfb,
    false>;
using serpent256_cfb_cipher = block_cipher<
    block_cipher_algorithm::serpent256,
    block_cipher_mode::cfb,
    false>;

using aes128_ofb_cipher = block_cipher<
    block_cipher_algorithm::aes128,
    block_cipher_mode::ofb,
    false>;
using aes256_ofb_cipher = block_cipher<
    block_cipher_algorithm::aes256,
    block_cipher_mode::ofb,
    false>;
using twofish128_ofb_cipher = block_cipher<
    block_cipher_algorithm::twofish128,
    block_cipher_mode::ofb,
    false>;
using twofish256_ofb_cipher = block_cipher<
    block_cipher_algorithm::twofish256,
    block_cipher_mode::ofb,
    false>;
using camellia128_ofb_cipher = block_cipher<
    block_cipher_algorithm::camellia128,
    block_cipher_mode::ofb,
    false>;
using camellia192_ofb_cipher = block_cipher<
    block_cipher_algorithm::camellia192,
    block_cipher_mode::ofb,
    false>;
using camellia256_ofb_cipher = block_cipher<
    block_cipher_algorithm::camellia256,
    block_cipher_mode::ofb,
    false>;
using serpent128_ofb_cipher = block_cipher<
    block_cipher_algorithm::serpent128,
    block_cipher_mode::ofb,
    false>;
using serpent192_ofb_cipher = block_cipher<
    block_cipher_algorithm::serpent192,
    block_cipher_mode::ofb,
    false>;
using serpent256_ofb_cipher = block_cipher<
    block_cipher_algorithm::serpent256,
    block_cipher_mode::ofb,
    false>;

using aes128_ecb_cipher = block_cipher<
    block_cipher_algorithm::aes128,
    block_cipher_mode::ecb,
    false>;
using aes256_ecb_cipher = block_cipher<
    block_cipher_algorithm::aes256,
    block_cipher_mode::ecb,
    false>;
using twofish128_ecb_cipher = block_cipher<
    block_cipher_algorithm::twofish128,
    block_cipher_mode::ecb,
    false>;
using twofish256_ecb_cipher = block_cipher<
    block_cipher_algorithm::twofish256,
    block_cipher_mode::ecb,
    false>;
using camellia128_ecb_cipher = block_cipher<
    block_cipher_algorithm::camellia128,
    block_cipher_mode::ecb,
    false>;
using camellia192_ecb_cipher = block_cipher<
    block_cipher_algorithm::camellia192,
    block_cipher_mode::ecb,
    false>;
using camellia256_ecb_cipher = block_cipher<
    block_cipher_algorithm::camellia256,
    block_cipher_mode::ecb,
    false>;
using serpent128_ecb_cipher = block_cipher<
    block_cipher_algorithm::serpent128,
    block_cipher_mode::ecb,
    false>;
using serpent192_ecb_cipher = block_cipher<
    block_cipher_algorithm::serpent192,
    block_cipher_mode::ecb,
    false>;
using serpent256_ecb_cipher = block_cipher<
    block_cipher_algorithm::serpent256,
    block_cipher_mode::ecb,
    false>;
    
using aes128_ctr_cipher = block_cipher<
    block_cipher_algorithm::aes128,
    block_cipher_mode::ctr,
    false>;
using aes256_ctr_cipher = block_cipher<
    block_cipher_algorithm::aes256,
    block_cipher_mode::ctr,
    false>;
using twofish128_ctr_cipher = block_cipher<
    block_cipher_algorithm::twofish128,
    block_cipher_mode::ctr,
    false>;
using twofish256_ctr_cipher = block_cipher<
    block_cipher_algorithm::twofish256,
    block_cipher_mode::ctr,
    false>;
using camellia128_ctr_cipher = block_cipher<
    block_cipher_algorithm::camellia128,
    block_cipher_mode::ctr,
    false>;
using camellia192_ctr_cipher = block_cipher<
    block_cipher_algorithm::camellia192,
    block_cipher_mode::ctr,
    false>;
using camellia256_ctr_cipher = block_cipher<
    block_cipher_algorithm::camellia256,
    block_cipher_mode::ctr,
    false>;
using serpent128_ctr_cipher = block_cipher<
    block_cipher_algorithm::serpent128,
    block_cipher_mode::ctr,
    false>;
using serpent192_ctr_cipher = block_cipher<
    block_cipher_algorithm::serpent192,
    block_cipher_mode::ctr,
    false>;
using serpent256_ctr_cipher = block_cipher<
    block_cipher_algorithm::serpent256,
    block_cipher_mode::ctr,
    false>;

//------------------------------------------------------------------------------
using secure_aes128_cbc_cipher = block_cipher<
    block_cipher_algorithm::aes128,
    block_cipher_mode::cbc,
    true>;
using secure_aes256_cbc_cipher = block_cipher<
    block_cipher_algorithm::aes256,
    block_cipher_mode::cbc,
    true>;
using secure_twofish128_cbc_cipher = block_cipher<
    block_cipher_algorithm::twofish128,
    block_cipher_mode::cbc,
    true>;
using secure_twofish256_cbc_cipher = block_cipher<
    block_cipher_algorithm::twofish256,
    block_cipher_mode::cbc,
    true>;
using secure_camellia128_cbc_cipher = block_cipher<
    block_cipher_algorithm::camellia128,
    block_cipher_mode::cbc,
    true>;
using secure_camellia192_cbc_cipher = block_cipher<
    block_cipher_algorithm::camellia192,
    block_cipher_mode::cbc,
    true>;
using secure_camellia256_cbc_cipher = block_cipher<
    block_cipher_algorithm::camellia256,
    block_cipher_mode::cbc,
    true>;
using secure_serpent128_cbc_cipher = block_cipher<
    block_cipher_algorithm::serpent128,
    block_cipher_mode::cbc,
    true>;
using secure_serpent192_cbc_cipher = block_cipher<
    block_cipher_algorithm::serpent192,
    block_cipher_mode::cbc,
    true>;
using secure_serpent256_cbc_cipher = block_cipher<
    block_cipher_algorithm::serpent256,
    block_cipher_mode::cbc,
    true>;
    
using secure_aes128_cfb_cipher = block_cipher<
    block_cipher_algorithm::aes128,
    block_cipher_mode::cfb,
    true>;
using secure_aes256_cfb_cipher = block_cipher<
    block_cipher_algorithm::aes256,
    block_cipher_mode::cfb,
    true>;
using secure_twofish128_cfb_cipher = block_cipher<
    block_cipher_algorithm::twofish128,
    block_cipher_mode::cfb,
    true>;
using secure_twofish256_cfb_cipher = block_cipher<
    block_cipher_algorithm::twofish256,
    block_cipher_mode::cfb,
    true>;
using secure_camellia128_cfb_cipher = block_cipher<
    block_cipher_algorithm::camellia128,
    block_cipher_mode::cfb,
    true>;
using secure_camellia192_cfb_cipher = block_cipher<
    block_cipher_algorithm::camellia192,
    block_cipher_mode::cfb,
    true>;
using secure_camellia256_cfb_cipher = block_cipher<
    block_cipher_algorithm::camellia256,
    block_cipher_mode::cfb,
    true>;
using secure_serpent128_cfb_cipher = block_cipher<
    block_cipher_algorithm::serpent128,
    block_cipher_mode::cfb,
    true>;
using secure_serpent192_cfb_cipher = block_cipher<
    block_cipher_algorithm::serpent192,
    block_cipher_mode::cfb,
    true>;
using secure_serpent256_cfb_cipher = block_cipher<
    block_cipher_algorithm::serpent256,
    block_cipher_mode::cfb,
    true>;

using secure_aes128_ofb_cipher = block_cipher<
    block_cipher_algorithm::aes128,
    block_cipher_mode::ofb,
    true>;
using secure_aes256_ofb_cipher = block_cipher<
    block_cipher_algorithm::aes256,
    block_cipher_mode::ofb,
    true>;
using secure_twofish128_ofb_cipher = block_cipher<
    block_cipher_algorithm::twofish128,
    block_cipher_mode::ofb,
    true>;
using secure_twofish256_ofb_cipher = block_cipher<
    block_cipher_algorithm::twofish256,
    block_cipher_mode::ofb,
    true>;
using secure_camellia128_ofb_cipher = block_cipher<
    block_cipher_algorithm::camellia128,
    block_cipher_mode::ofb,
    true>;
using secure_camellia192_ofb_cipher = block_cipher<
    block_cipher_algorithm::camellia192,
    block_cipher_mode::ofb,
    true>;
using secure_camellia256_ofb_cipher = block_cipher<
    block_cipher_algorithm::camellia256,
    block_cipher_mode::ofb,
    true>;
using secure_serpent128_ofb_cipher = block_cipher<
    block_cipher_algorithm::serpent128,
    block_cipher_mode::ofb,
    true>;
using secure_serpent192_ofb_cipher = block_cipher<
    block_cipher_algorithm::serpent192,
    block_cipher_mode::ofb,
    true>;
using secure_serpent256_ofb_cipher = block_cipher<
    block_cipher_algorithm::serpent256,
    block_cipher_mode::ofb,
    true>;

using secure_aes128_ecb_cipher = block_cipher<
    block_cipher_algorithm::aes128,
    block_cipher_mode::ecb,
    true>;
using secure_aes256_ecb_cipher = block_cipher<
    block_cipher_algorithm::aes256,
    block_cipher_mode::ecb,
    true>;
using secure_twofish128_ecb_cipher = block_cipher<
    block_cipher_algorithm::twofish128,
    block_cipher_mode::ecb,
    true>;
using secure_twofish256_ecb_cipher = block_cipher<
    block_cipher_algorithm::twofish256,
    block_cipher_mode::ecb,
    true>;
using secure_camellia128_ecb_cipher = block_cipher<
    block_cipher_algorithm::camellia128,
    block_cipher_mode::ecb,
    true>;
using secure_camellia192_ecb_cipher = block_cipher<
    block_cipher_algorithm::camellia192,
    block_cipher_mode::ecb,
    true>;
using secure_camellia256_ecb_cipher = block_cipher<
    block_cipher_algorithm::camellia256,
    block_cipher_mode::ecb,
    true>;
using secure_serpent128_ecb_cipher = block_cipher<
    block_cipher_algorithm::serpent128,
    block_cipher_mode::ecb,
    true>;
using secure_serpent192_ecb_cipher = block_cipher<
    block_cipher_algorithm::serpent192,
    block_cipher_mode::ecb,
    true>;
using secure_serpent256_ecb_cipher = block_cipher<
    block_cipher_algorithm::serpent256,
    block_cipher_mode::ecb,
    true>;

using secure_aes128_ctr_cipher = block_cipher<
    block_cipher_algorithm::aes128,
    block_cipher_mode::ctr,
    true>;
using secure_aes256_ctr_cipher = block_cipher<
    block_cipher_algorithm::aes256,
    block_cipher_mode::ctr,
    true>;
using secure_twofish128_ctr_cipher = block_cipher<
    block_cipher_algorithm::twofish128,
    block_cipher_mode::ctr,
    true>;
using secure_twofish256_ctr_cipher = block_cipher<
    block_cipher_algorithm::twofish256,
    block_cipher_mode::ctr,
    true>;
using secure_camellia128_ctr_cipher = block_cipher<
    block_cipher_algorithm::camellia128,
    block_cipher_mode::ctr,
    true>;
using secure_camellia192_ctr_cipher = block_cipher<
    block_cipher_algorithm::camellia192,
    block_cipher_mode::ctr,
    true>;
using secure_camellia256_ctr_cipher = block_cipher<
    block_cipher_algorithm::camellia256,
    block_cipher_mode::ctr,
    true>;
using secure_serpent128_ctr_cipher = block_cipher<
    block_cipher_algorithm::serpent128,
    block_cipher_mode::ctr,
    true>;
using secure_serpent192_ctr_cipher = block_cipher<
    block_cipher_algorithm::serpent192,
    block_cipher_mode::ctr,
    true>;
using secure_serpent256_ctr_cipher = block_cipher<
    block_cipher_algorithm::serpent256,
    block_cipher_mode::ctr,
    true>;

//------------------------------------------------------------------------------
using sha1_hash = hash<hash_algorithm::sha1, false>;
using sha224_hash = hash<hash_algorithm::sha224, false>;
using sha256_hash = hash<hash_algorithm::sha256, false>;
using sha384_hash = hash<hash_algorithm::sha384, false>;
using sha512_hash = hash<hash_algorithm::sha512, false>;

//------------------------------------------------------------------------------
using secure_sha1_hash = hash<hash_algorithm::sha1, true>;
using secure_sha224_hash = hash<hash_algorithm::sha224, true>;
using secure_sha256_hash = hash<hash_algorithm::sha256, true>;
using secure_sha384_hash = hash<hash_algorithm::sha384, true>;
using secure_sha512_hash = hash<hash_algorithm::sha512, true>;
    
//------------------------------------------------------------------------------
using sha1_hmac = hmac<hmac_algorithm::sha1, false>;
using sha224_hmac = hmac<hmac_algorithm::sha224, false>;
using sha256_hmac = hmac<hmac_algorithm::sha256, false>;
using sha384_hmac = hmac<hmac_algorithm::sha384, false>;
using sha512_hmac = hmac<hmac_algorithm::sha512, false>;

//------------------------------------------------------------------------------
using secure_sha1_hmac = hmac<hmac_algorithm::sha1, true>;
using secure_sha224_hmac = hmac<hmac_algorithm::sha224, true>;
using secure_sha256_hmac = hmac<hmac_algorithm::sha256, true>;
using secure_sha384_hmac = hmac<hmac_algorithm::sha384, true>;
using secure_sha512_hmac = hmac<hmac_algorithm::sha512, true>;

} // crypt

/** @} */

} // namespaces

#endif // NIC_278E6EAD0FF66864_NIC

