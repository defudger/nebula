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
#include "exception.h"

namespace nebula { namespace gpg { namespace detail {
//------------------------------------------------------------------------------
string dump_gpgme_error_t(gpgme_error_t err)
{
    string buf;
    size_t n = 1024;
    buf.resize(n);
    const int res = gpgme_strerror_r(err, buf.data(), n);
    if(res != 0)
        return "Failed to fetch error description";
    else
        buf.resize(strlen(buf.c_str()));
    
    return fmt::to_string(buf, " [", gpgme_strsource(err), ']');
}

}}} // namespaces

