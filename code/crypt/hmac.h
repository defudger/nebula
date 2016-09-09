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
#ifndef NIC_98A27B3FBBD22E69_NIC
#define NIC_98A27B3FBBD22E69_NIC

#include "buffer.h"

#ifdef N_CRYPT_GCRYPT
#   include "gcrypt/gcrypt_mac.h"
#endif

namespace nebula { namespace crypt { namespace detail {
/** @ingroup Crypt
 * @{
 * */
//------------------------------------------------------------------------------
#ifdef N_CRYPT_GCRYPT
//------------------------------------------------------------------------------
template <hmac_algorithm Algo, bool Secure>
class hmac : public gcrypt::mac
{
public:
    using algorithm = fnd::integral_constant<hmac_algorithm, Algo>;
    using secure = meta::bool_<Secure>;
    using result_size = hmac_result_size_c<Algo>;
    using result_type = buffer<result_size::value, secure, hmac>;
    
    inline hmac()
    : gcrypt::mac(gcrypt::to_gcrypt_mac_algorithm(Algo), Secure)
    {}
    hmac(hmac &) = delete;
    hmac(const hmac &) = delete;
    hmac(hmac &&) = default;
    
    hmac &operator = (hmac &) = delete;
    hmac &operator = (const hmac &) = delete;
    hmac &operator = (hmac &&) = default;
    
    inline void swap(hmac &other) noexcept {
        gcrypt::mac::swap(other);
    }
    
    /** Finalize calculation and return the result. */
    inline void result(char *buf, const size_t n) {
        gcrypt::mac::result(buf, n);
    }
    /** Finalize calculation and return the result. */
    inline void result(result_type &x) {
        result(x.data(), x.size());
    }
    /** Finalize calculation and return the result. */
    inline result_type result() {
        result_type res;
        result(res.data(), res.size());
        return res;
    }
    
    /** Finalize calculation and compare result to the buffer supplied to
     *  this function.
     *
     *  @return true Iff the hashes are equal.
     * */
    inline bool verify(const char *buf, const size_t n) {
        return gcrypt::mac::verify(buf, n);
    }
    /** Finalize calculation and compare result to the buffer supplied to
     *  this function.
     *
     *  @return true Iff the hashes are equal.
     * */
    inline bool verify(const result_type &x) {
        return gcrypt::mac::verify(x.data(), x.size());
    }
    
private:
    using gcrypt::mac::set_iv;
};

#endif

/** @} */

}}} // namespaces

#endif // NIC_98A27B3FBBD22E69_NIC

