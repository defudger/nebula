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
#ifndef NIC_80FD98B4F8086A13_NIC
#define NIC_80FD98B4F8086A13_NIC

#include "utils.h"
#include "../../scope_exit.h"

namespace nebula { namespace foundation { namespace utf {
namespace unistring {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class I, class F>
inline void word_breaks(I iter, const size_t n, F &&f)
{
    char *p = new char[n];
    n_scope_exit(&) {
        delete [] p;
    };
    
    const char *s = &*iter;
    
    ::u8_wordbreaks(to_ustr(s), n, p);
    
    for(size_t i = 0; i < n; ++i)
        if(p[i]==1)
            f(iter+i);
}

/** @} */

}}}} // namespaces

#endif // NIC_80FD98B4F8086A13_NIC

