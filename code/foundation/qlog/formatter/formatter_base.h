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
#ifndef NIC_F9B323F4CA6FCFAC_NIC
#define NIC_F9B323F4CA6FCFAC_NIC

#include "../level.h"

#include "../../dll_interface.h"
#include "../../string.h"
#include "../../ptr.h"

namespace nebula { namespace foundation { namespace qlog { namespace formatter {
//------------------------------------------------------------------------------
struct n_foundation_dll formatter_base : public ref_counted
{
    inline virtual ~formatter_base() noexcept {}
    
    virtual void operator () (level, string &) = 0;
};

}}}} // namespaces

#endif // NIC_F9B323F4CA6FCFAC_NIC
