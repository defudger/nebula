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
#ifndef NIC_16FB3AE82B167448_NIC
#define NIC_16FB3AE82B167448_NIC

#include "gcrypt_common.h"

namespace nebula { namespace crypt { namespace detail { namespace gcrypt {
/** @ingroup Crypt
 * @{
 * */
//------------------------------------------------------------------------------
extern fnd::string n_crypt_dll dump_gcry_error_t(gcry_error_t err);

//------------------------------------------------------------------------------
struct wrapped_gcry_error_t
{
    inline wrapped_gcry_error_t(gcry_error_t x) noexcept
    : err(x)
    {}
    
    template <class Stream>
    inline void operator () (Stream &s, fmt::fout_tag) const
    {
        fmt::fwrite(s, dump_gcry_error_t(err));
    }
    
    /// exposed
    gcry_error_t err;
};

//------------------------------------------------------------------------------
using ei_gcry_error = fnd::error_info<
    struct gcry_error_, wrapped_gcry_error_t>;

/** @} */

}}}} // namespaces

#endif // NIC_16FB3AE82B167448_NIC

