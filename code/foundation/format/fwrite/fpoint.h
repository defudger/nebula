/*--!>
This file is part of Nebula, a multi-purpose library mainly written in C++.

Copyright 2015-2016 outshined (outshined@riseup.net)
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
#ifndef NIC_56EF9CD75D8064CB_NIC
#define NIC_56EF9CD75D8064CB_NIC

#include "fwrite_impl_fwd.h"
#include "../writer/dec.h"

namespace nebula { namespace foundation { namespace fmt {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <>
struct fwrite_impl<float>
{
    template <class Sink>
    inline static void apply (Sink &sink, const float x)
    {
        fmt::dec(x)(sink, fout_tag());
    }
};
//------------------------------------------------------------------------------
template <>
struct fwrite_impl<double>
{
    template <class Sink>
    inline static void apply (Sink &sink, const double x)
    {
        fmt::dec(x)(sink, fout_tag());
    }
};
//------------------------------------------------------------------------------
template <>
struct fwrite_impl<long double>
{
    template <class Sink>
    inline static void apply (Sink &sink, const long double x)
    {
        fmt::dec(x)(sink, fout_tag());
    }
};


/** @} */

}}} // namespaces

#endif // NIC_56EF9CD75D8064CB_NIC