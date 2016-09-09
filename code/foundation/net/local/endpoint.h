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
#ifndef NIC_C66BDB933A548FD5_NIC
#define NIC_C66BDB933A548FD5_NIC

#include "../../string.h"
#include "../../format.h"
#include "../defs.h"

namespace nebula { namespace foundation { namespace net { namespace local {
/** @ingroup Foundation
 * @{
 */  
//------------------------------------------------------------------------------
class endpoint
{
public:
    constexpr static net::address_family address_family
        = net::address_family::local;
    
    endpoint() = default;
    endpoint(endpoint &) = default;
    endpoint(const endpoint &) = default;
    endpoint(endpoint &&) = default;
    
    template <class S>
    inline endpoint(S &&s)
    : v(foundation::forward<S>(s))
    {}
    
    endpoint &operator = (endpoint &) = default;
    endpoint &operator = (const endpoint &) = default;
    endpoint &operator = (endpoint &&) = default;
    
    inline void swap(endpoint &other) noexcept {
        foundation::swap(v, other.v);
    }
    
    inline const_cstring get() const noexcept {
        return {v.begin(), v.end()};
    }
    
    template <class Stream>
    inline void operator () (Stream &s, fmt::fout_tag) const
    {
        fmt::fwrite(s, v);
    }

private:
    string v;
};

//------------------------------------------------------------------------------
using address = endpoint;

/** @} */

}}}} // namespaces

#endif // NIC_C66BDB933A548FD5_NIC
