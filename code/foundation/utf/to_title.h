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
#ifndef NIC_48F165AA21636BDD_NIC
#define NIC_48F165AA21636BDD_NIC

#include "config.h"
#include "types.h"
#include "../range.h"

#ifdef N_UTF_unistring
#   include "unistring/case.h"
#endif

namespace nebula { namespace foundation { namespace utf {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class String>
struct to_title_impl
{
    template <class OutString>
    inline static void apply(
        const String &s,
        const char *iso639_lang,
        const normal_form nf,
        OutString &out)
    {
        #ifdef N_UTF_unistring
        unistring::to_title(s.data(), range::size(s), iso639_lang, nf, out);
        #endif
    }
};
//------------------------------------------------------------------------------
template <class InString, class OutString>
inline void to_title(
    const InString &s,
    const char *iso639_lang,
    const normal_form nf,
    OutString &out)
{
    return to_title_impl<InString>::apply(s, iso639_lang, nf, out);
}

/** @} */

}}} // namespaces

#endif // NIC_48F165AA21636BDD_NIC

