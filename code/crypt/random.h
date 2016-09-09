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
#ifndef NIC_2773E0B3CBE39A01_NIC
#define NIC_2773E0B3CBE39A01_NIC

#include "config.h"

#ifdef N_CRYPT_GCRYPT
#   include "gcrypt/gcrypt_random.h"
#endif

namespace nebula { namespace crypt { namespace detail {
/** @ingroup Crypt
 * @{
 * */
//------------------------------------------------------------------------------
#ifdef N_CRYPT_GCRYPT
//------------------------------------------------------------------------------
template <int GCryRandomLevel>
class random_device_ final : public gcrypt::random_device
{
public:
    using result_type = unsigned long;
    
    inline random_device_()
    : gcrypt::random_device(static_cast<gcry_random_level>(GCryRandomLevel))
    {}
    random_device_(random_device_ &) = delete;
    random_device_(const random_device_ &) = delete;
    random_device_(random_device_ &&) = default;
    
    random_device_ &operator = (random_device_ &) = delete;
    random_device_ &operator = (const random_device_ &) = delete;
    random_device_ &operator = (random_device_ &&) = default;
    
    inline void swap(random_device_ &other) noexcept {
        gcrypt::random_device::swap(other);
    }
    
    inline result_type operator () () {
        result_type res;
        this->read(
            static_cast<char *>(static_cast<void *>(&res)), sizeof(res));
        return res;
    }
};
//------------------------------------------------------------------------------
using pseudo_random_device = random_device_<GCRY_STRONG_RANDOM>;
using random_device = random_device_<GCRY_VERY_STRONG_RANDOM>;

#endif

/** @} */

}}} // namespaces

#endif // NIC_2773E0B3CBE39A01_NIC

