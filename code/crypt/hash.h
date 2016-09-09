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
#ifndef NIC_2A123654512D3FB3_NIC
#define NIC_2A123654512D3FB3_NIC

#include "buffer.h"

#ifdef N_CRYPT_GCRYPT
#   include "gcrypt/gcrypt_hash.h"
#endif

namespace nebula { namespace crypt { namespace detail {
/** @ingroup Crypt
 * @{
 * */
//------------------------------------------------------------------------------
#ifdef N_CRYPT_GCRYPT
//------------------------------------------------------------------------------
template <hash_algorithm Algo, bool Secure>
class hash : public gcrypt::hash
{
public:
    using algorithm = fnd::integral_constant<hash_algorithm, Algo>;
    using secure = meta::bool_<Secure>;
    using result_size = hash_result_size_c<Algo>;
    using result_type = buffer<result_size::value, secure, hash>;
    
    inline hash()
    : gcrypt::hash(gcrypt::to_gcrypt_hash_algorithm(Algo), Secure)
    {}
    hash(hash &) = delete;
    hash(const hash &) = delete;
    hash(hash &&) = default;
    
    hash &operator = (hash &) = delete;
    hash &operator = (const hash &) = delete;
    hash &operator = (hash &&) = default;
    
    inline void swap(hash &other) noexcept {
        gcrypt::hash::swap(other);
    }
    
    inline void result(char *buf, const size_t n) {
        gcrypt::hash::result(buf, n);
    }
    inline void result(result_type &x) {
        result(x.data(), x.size());
    }
    inline result_type result() {
        result_type res;
        result(res.data(), res.size());
        return res;
    }
};

#endif

/** @} */

}}} // namespaces

#endif // NIC_2A123654512D3FB3_NIC

