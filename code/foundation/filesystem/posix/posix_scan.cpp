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
#include "../config.h"
#ifdef N_FILESYSTEM_posix_scandir

#include "../path.h"
#include "../exception.h"
#include "../../scope_exit.h"

#include <dirent.h>

namespace nebula { namespace foundation { namespace filesystem {
//------------------------------------------------------------------------------
vector<path> scan(const path &p)
{
    struct dirent64 **dirs;
    const int r = ::scandir64(p.c_str(), &dirs, nullptr, ::alphasort64);
    if(r == -1)
    {
        n_throw(system::system_error)
            << ei_msg_c("scandir() failed.")
            << ei_path(p)
            << system::ei_error_code(system::error_code(
                errno, system::system_category()));
    }
    
    n_scope_exit(&) {
        for(int i = 0; i < r; ++i)
            ::free(dirs[i]);
        ::free(dirs);
    };
    
    vector<path> v;
    v.reserve(r);
    
    for(int i = 0; i < r; ++i)
    {
        v.push_back(dirs[i]->d_name);
    }
    
    return v;
}

}}} // namespaces

#endif // N_FILESYSTEM_posix_stat
